//
//  ConfigFile.cpp
//  Glowing Archer
//
//  Created by Michael Henderson on 1/26/13.
//
// This file is part of Glowing Archer (http://github.com/quoha/glowing-archer).
//
// Copyright (c) 2013 Michael D Henderson
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#include "ConfigFile.h"
#include "SymbolTable.h"
#include "Text.h"
#include <stdio.h>
#include <ctype.h>
#include <cstring>

// parser state
//
struct PSTATE {
    GlowingArcher::Text        *env;
    GlowingArcher::Text        *envGlob;
    GlowingArcher::InputStream *is;
    GlowingArcher::SymbolTable *symtab;
    bool                        validSection;
    void                       *data; // ?
};

// for reasons that i don't understand, there is a difference between
// an undefined variable, a variable with a value of null, and a
// variable with a value of the empty string.
//
// file       = (section)* EOF .
// section    = '[' '~'? SECTION_NAME ']' assignment* .
// assignment = NAME '=' ( 'null' | QUOTED_STRING ) ';' .
//
// think of the parser as
//    accepting literals
//    accepting terminals
//    parsing   non-terminals
//
//
static bool AcceptLiteral(struct PSTATE *ps, const char *literal);
static bool AcceptTerminal(struct PSTATE *ps, const char *terminal);
static bool AcceptWhiteSpace(struct PSTATE *ps);
static bool Expect(struct PSTATE *ps, const char *terminal);
static bool TranslateSection(struct PSTATE *ps);
static bool TranslateAssignment(struct PSTATE *ps);

bool GlowingArcher::ParseConfigFile(GlowingArcher::Text *env, GlowingArcher::SymbolTable *symtab, GlowingArcher::InputStream *is) {
    struct PSTATE pState;
    struct PSTATE *ps = &pState;
    std::memset(ps, 0, sizeof(*ps));
    ps->env          = env;
    ps->envGlob      = new Text("*", 1);
    ps->is           = is;
    ps->symtab       = symtab;
    ps->validSection = false;
    
    // while ch in first(section)
    //   translate(section)
    // if ch = EOF
    //   accept
    // else
    //   reject
    //
    AcceptWhiteSpace(ps);
    while (ps->is->CurrChar() == '[') {
        TranslateSection(ps);
        AcceptWhiteSpace(ps);
    }
    if (!AcceptTerminal(ps, "EOF")) {
        printf("parse:\terror - expected to find EOF on line %d\n", ps->is->Line());
        return 0;
    }
    return false;
}

bool AcceptLiteral(struct PSTATE *ps, const char *literal) {
    AcceptWhiteSpace(ps);
    int length = (int)std::strlen(literal);
    if (std::strncmp(ps->is->PCurr(), literal, length) == 0) {
        for (int idx = 0; idx < length; idx++) {
            ps->is->NextChar();
        }
        return true;
    }
    return false;
}

bool AcceptTerminal(struct PSTATE *ps, const char *terminal) {
    AcceptWhiteSpace(ps);
    if (std::strcmp(terminal, "EOF") == 0) {
        return ps->is->EndOfStream();
    } else if (std::strcmp(terminal, "name") == 0) {
        int length = 0;
        while (!ps->is->EndOfStream() && isalnum(ps->is->CurrChar())) {
            ps->is->NextChar();
            length++;
        }
        return (length > 0) ? true : false;
    } else if (std::strcmp(terminal, "sectionName") == 0) {
        int length = 0;
        if (ps->is->CurrChar() == '*') {
            ps->is->NextChar();
            length = 1;
        } else {
            while (!ps->is->EndOfStream() && isalnum(ps->is->CurrChar())) {
                ps->is->NextChar();
                length++;
            }
        }
        return (length > 0) ? true : false;
    } else if (std::strcmp(terminal, "value") == 0) {
        return ps->is->SkipWord();
    }
    printf("parse:\taccept doesn't understand terminal '%s'\n", terminal);
    return false;
}

bool AcceptWhiteSpace(struct PSTATE *ps) {
    while (true) {
        ps->is->SkipWhiteSpace();
        if (ps->is->CurrChar() == '/' && ps->is->PeekChar() == '/') {
            ps->is->SkipLine();
            continue;
        }
        break;
    }
    return true;
}


bool Expect(struct PSTATE *ps, const char *terminal) {
    if (AcceptTerminal(ps, terminal)) {
        return true;
    }
    printf("parse:\texpected '%s' on line %d\n", terminal, ps->is->Line());
    return false;
}

// if ch = [
//   accept
//   if ch = ~
//     accept
//   if ch = sectionName
//     accept
//     if ch = ]
//       accept
//       while ch in first(assignment)
//         translate(assignment)
//     else
//       reject
//   else
//     reject
// else
//   reject
//
bool TranslateSection(struct PSTATE *ps) {

    if (AcceptLiteral(ps, "[")) {
        bool isNot = AcceptLiteral(ps, "~");

        // pull out the section name
        const char *startSectionName = ps->is->PCurr();
        if (AcceptTerminal(ps, "sectionName")) {
            GlowingArcher::Text *sectionName = new GlowingArcher::Text(startSectionName, (int)(ps->is->PCurr() - startSectionName));
            printf("parse:\tsection %s on line %d\n", sectionName->CString(), ps->is->Line());
            if (AcceptLiteral(ps, "]")) {
                ps->validSection = (ps->envGlob->Equal(sectionName) || ps->env->Equal(sectionName));
                printf("parse:\tsection %s %s valid\n", sectionName->CString(), ps->validSection ? "is" : "is not");
                AcceptWhiteSpace(ps);
                while (!ps->is->EndOfStream() && isalpha(ps->is->CurrChar())) {
                    if (!TranslateAssignment(ps)) {
                        printf("parse:\tfailed to find optional assignment on line %d\n", ps->is->Line());
                        return false;
                    }
                    AcceptWhiteSpace(ps);
                }
                ps->validSection = false;
                // should do something with the section
                printf("parse:\tsuccessfully parsed section '%s'\n", sectionName->CString());
                return true;
            }
            printf("error:\tsection expected ']' but found '%c' on line %d\n", ps->is->CurrChar(), ps->is->Line());
            return false;
        }
        printf("error:\texpected section name on line %d\n", ps->is->Line());
        return false;
    }
    printf("error:\tsection expected '[' but found '%c' on line %d\n", ps->is->CurrChar(), ps->is->Line());
    return false;
}

// if ch = name
//   accept
//   if ch = =
//     accept
//     if ch = null
//       accept
//     else if ch = quotedString
//       accept
//     else
//       reject
//     if ch = ;
//       accept
//     else
//       reject
//   else
//     reject
// else
//   reject
//
bool TranslateAssignment(struct PSTATE *ps) {
    const char *startName = ps->is->PCurr();
    if (AcceptTerminal(ps, "name")) {
        GlowingArcher::Text *assignmentName  = new GlowingArcher::Text(startName, (int)(ps->is->PCurr() - startName));
        GlowingArcher::Text *assignmentValue = 0;
        printf("parse:\tassign %s on line %d\n", assignmentName->CString(), ps->is->Line());
        bool isNull = true;
        if (AcceptLiteral(ps, "=")) {
            AcceptWhiteSpace(ps);
            const char *startValue = ps->is->PCurr();
            if (!AcceptTerminal(ps, "value")) {
                printf("parse:\tassignment must be null or a quoted string on line %d\n", ps->is->Line());
                return false;
            }
            GlowingArcher::Text *value = new GlowingArcher::Text(startValue, (int)(ps->is->PCurr() - startValue));
            printf("parse:\t_value %s on line %d\n", value->CString(), ps->is->Line());
            isNull = std::strcmp(value->CString(), "null") == 0;
            if (!AcceptLiteral(ps, ";")) {
                printf("parse:\tassignment must be terminated on line %d\n", ps->is->Line());
                return false;
            }
            assignmentValue = isNull ? 0 : value;
        }
        if (assignmentValue) {
            printf("parse:\tsetting %s to %s\n", assignmentName->CString(), assignmentValue->CString());
        } else {
            // set variable to null
            printf("parse:\tsetting %s to null\n", assignmentName->CString());
        }
        ps->symtab->Add(assignmentName, assignmentValue);
        return true;
    }
    printf("parse:\tassignment expected name on line %d\n", ps->is->Line());
    return false;
}

