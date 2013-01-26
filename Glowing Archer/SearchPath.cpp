//
//  SearchPath.cpp
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

#include "SearchPath.h"
#include <stdio.h>
#include <cstring>
#include <sys/stat.h>

GlowingArcher::SearchPath::SearchPath(void) : Object("GlowingArcher::SearchPath") {
    for (int idx = 0; idx < 128; idx++) {
        paths[idx] = 0;
    }
}

GlowingArcher::SearchPath::~SearchPath() {
    for (int idx = 0; idx < 128; idx++) {
        delete [] paths[idx];
    }
}

bool GlowingArcher::SearchPath::AddPath(GlowingArcher::Text *path) {
    int idx;
    for (idx = 0; idx < 128; idx++) {
        if (!paths[idx]) {
            paths[idx] = new Text(path);
            return true;
        }
    }
    return false;
}

bool GlowingArcher::SearchPath::Dump(void) const {
    printf("spath:\t%s\n", "*** dump ***");
    for (int idx = 0; idx < 128; idx++) {
        if (paths[idx]) {
            printf("%5d:\t%-18s == '%s'\n", idx, "searchPath", paths[idx]->CString());
        }
    }
    return true;
}

GlowingArcher::Text *GlowingArcher::SearchPath::FindFile(GlowingArcher::Text *fileName) const {
    Text *fullPath = 0;

    for (int idx = 127; idx >= 0; idx--) {
        if (paths[idx]) {
            fullPath = new Text(paths[idx], fileName);

            struct stat sb;
            if (stat(fullPath->CString(), &sb) == 0 && S_ISREG(sb.st_mode)) {
                // found file, return full path to it
                //
                break;
            }
            
            delete fullPath;
            fullPath = 0;
        }
    }

    return fullPath;
}
