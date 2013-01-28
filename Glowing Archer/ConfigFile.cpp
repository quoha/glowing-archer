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
#include "Text.h"
#include <stdio.h>
#include <ctype.h>
#include <cstring>

struct PSTATE {
    GlowingArcher::InputStream *is;
};

// for reasons that i don't understand, there is a difference between
// an undefined variable, a variable with a value of null, and a
// variable with a value of the empty string.
//
// file       = (section)* .
// section    = '[' '~'? SECTION_NAME ']' assignment* .
// assignment = NAME '=' QUOTED_STRING? ';' '\n' .
//
// think of the parser as
//    accepting terminals
//    expecting terminals
//    parsing non-terminals
//
static bool Accept(struct PSTATE *ps, const char *terminal);
static bool Expect(struct PSTATE *ps, const char *terminal);
static bool ParseFile(struct PSTATE *ps);
static bool ParseSection(struct PSTATE *ps);
static bool ParseAssignment(struct PSTATE *ps);

GlowingArcher::AST *GlowingArcher::ParseConfigFile(GlowingArcher::InputStream *is) {
    GlowingArcher::AST *root = 0;

    struct PSTATE ps;
    ps.is = is;
    ParseSection(&ps);

    return root;
}

static bool Accept(struct PSTATE *ps, const char *terminal) {
    printf("parse:\taccept doesn't understand terminal '%s'\n", terminal);
    return false;
}

bool Expect(struct PSTATE *ps, const char *terminal) {
    if (Accept(ps, terminal)) {
        return true;
    }
    printf("parse:\texpected '%s'\n", terminal);
    return false;
}

bool ParseFile(struct PSTATE *ps) {
    while (ParseSection(ps)) {
        //
    }
    return true;
}

bool ParseSection(struct PSTATE *ps) {
    GlowingArcher::InputStream *is = ps->is;
    if (is->CurrChar() != '[') {
        return false;
    }
    is->NextChar();

    bool isNot = (is->CurrChar() == '~') ? true : false;
    if (isNot) {
        is->NextChar();
    }
    const char *startName = is->PCurr();

    // pull out the section name
    while (!is->EndOfStream() && is->CurrChar() != ']') {
        is->NextChar();
    }

    if (is->CurrChar() != ']') {
        printf("error:\tinvalid section name\t");
        printf("\t%-20s == '%s'\n", "sourceName", is->Name()->CString());
        printf("\t%-20s == %d\n", "lineNumber", is->Line());
        return false;
    }

    GlowingArcher::Text *sectionName = new GlowingArcher::Text(startName, (int)(is->PCurr() - startName));

    // while currentCharacter is not '[', ParseAssignment

    return true;
}

bool ParseAssignment(struct PSTATE *ps) {
    return true;
}

bool ParseName(struct PSTATE *ps) {
    return true;
}

bool ParseValue(struct PSTATE *ps) {
    return true;
}

bool ParseWhiteSpace(struct PSTATE *ps) {
    GlowingArcher::InputStream *is = ps->is;
    while (true) {
        while (!is->EndOfStream() && !isspace(is->CurrChar())) {
            is->NextChar();
        }
        if (is->CurrChar() == '/' && is->PeekChar() == '/') {
            while (!is->EndOfStream() && is->CurrChar() != '\n') {
                is->NextChar();
            }
            continue;
        }
        break;
    }
    return true;
}
