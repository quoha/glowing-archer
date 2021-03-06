//
//  main.cpp
//  Glowing Archer
//
//  Created by Michael Henderson on 1/25/13.
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

#include "Text.h"
#include "SearchPath.h"
#include "Stream.h"
#include "SymbolTable.h"
#include "AST.h"
#include "ConfigFile.h"
#include "ModelFile.h"
#include "Value.h"
#include <stdio.h>
#include <cstring>

int main(int argc, const char * argv[])
try {
    printf(" todo:\timplement AST\n");

    bool isVerbose = false;
    GlowingArcher::SearchPath  *searchPath = new GlowingArcher::SearchPath;
    GlowingArcher::SymbolTable *symtab     = new GlowingArcher::SymbolTable;
    GlowingArcher::Text        *envName    = new GlowingArcher::Text("environment", -1);
    GlowingArcher::Text        *envValue   = 0;

    // find the environment first
    //
    for (int idx = 1; idx < argc; idx++) {
        const char *opt = argv[idx];
        if (std::strcmp(opt, "--") == 0) {
            break;
        } else if (std::strncmp(opt, "env=", 4) == 0) {
            if (envValue) {
                delete envValue;
            }
            envValue = new GlowingArcher::Text(opt + 4, -1);
            argv[idx] = 0;
        }
    }
    if (!envValue) {
        printf("\nerror:\tyou must specify an environment on the command line\n\n");
        return 2;
    }
    symtab->Add(envName, envValue);

    // now parse the rest of the command line
    //
    for (int idx = 1; idx < argc; idx++) {
        if (!argv[idx]) {
            continue;
        }
        char *opt = new char[std::strlen(argv[idx]) + 1];
        std::strcpy(opt, argv[idx]);
        char *val = opt;
        while (*val && *val != '=') {
            val++;
        }
        if (*val == '=') {
            *(val++) = 0;
        }

        if (std::strcmp(opt, "config-file") == 0 && *val) {
            GlowingArcher::Text *cfgFile = searchPath->FindFile(new GlowingArcher::Text(val, -1));
            if (!cfgFile) {
                printf("\nerror:\tunable to locate config file '%s'\n", val);
                return 2;
            }
            if (isVerbose) {
                printf(" info:\t%-20s == '%s'\n", "configFile", cfgFile->CString());
            } else {
                printf(" info:\t%-20s == '%s'\n", "configFile", val);
            }
            GlowingArcher::InputStream *is = new GlowingArcher::InputStream(cfgFile);
            is->Dump();
            if (!GlowingArcher::ParseConfigFile(envValue, symtab, is)) {
                printf("error:\terror parsing config file\n");
                return 2;
            }
            symtab->Dump();
        } else if (std::strcmp(opt, "model-file") == 0 && *val) {
            GlowingArcher::Text *modelFile = searchPath->FindFile(new GlowingArcher::Text(val, -1));
            if (!modelFile) {
                printf("\nerror:\tunable to locate model file '%s'\n", val);
                return 2;
            }
            if (isVerbose) {
                printf(" info:\t%-20s == '%s'\n", "modelFile", modelFile->CString());
            } else {
                printf(" info:\t%-20s == '%s'\n", "modelFile", val);
            }
            GlowingArcher::InputStream *is = new GlowingArcher::InputStream(modelFile);
            is->Dump();
            if (!GlowingArcher::ParseConfigFile(envValue, symtab, is)) {
                printf("error:\terror parsing config file\n");
                return 2;
            }
            symtab->Dump();
        } else if (std::strcmp(opt, "verbose") == 0) {
            if (std::strcmp(val, "yes") == 0 || std::strcmp(val, "true") == 0) {
                isVerbose = true;
            } else {
                isVerbose = false;
            }
        } else if (std::strcmp(opt, "search-path") == 0 && *val) {
            searchPath->AddPath(new GlowingArcher::Text(val, -1));
        } else {
            printf("\nerror:\tinvalid option '%s%s%s'\n", opt, *val ? "=" : "", val);
            return 2;
        }
    }

    symtab->Dump();
    searchPath->Dump();
    
    return 0;
} catch (...) {
    // do something with the exception?
    return 0;
}

