//
//  Stream.cpp
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

#include "Stream.h"
#include <stdio.h>
#include <cstring>
#include <ctype.h>
#include <sys/stat.h>

GlowingArcher::InputStream::InputStream(Text *fileName) : GlowingArcher::Object("GlowingArcher::InputStream") {
    name   = fileName;
    errmsg = 0;

	struct stat statBuf;
	if (stat(name->CString(), &statBuf) != 0) {
        errmsg = new Text("file does not exist", -1);
        data      = new char[1];
        data[0]   = 0;
        curr      = data;
        endOfData = data;
    } else {
        // allocate enough space for the file and
        // the new line plus nil terminator
        //
        int actLength       = (int)statBuf.st_size;
        data = new char[actLength + 2];

        // set those two extra bytes to zero so that we don't forget to
        // do it later. they ensure that we end up nil-terminated.
        //
        std::memset(data, 0, actLength + 2);

        // only do the file read if it has data in it
        //
        if (actLength > 0) {
            FILE *fp = fopen(name->CString(), "r");
            if (!fp || fread(data, statBuf.st_size, 1, fp) != 1) {
                errmsg = new Text("should get the strerror", -1);
            }
            if (fp) {
                fclose(fp);
            }
        }
        curr      = data;
        endOfData = data + actLength;
    }

    line = 1;
}

GlowingArcher::InputStream::~InputStream() {
    delete [] data;
    delete errmsg;
}

bool GlowingArcher::InputStream::Dump(void) const {
    printf(" istr:\t*** dump %s\n", name->CString());
    printf("%s\n", data);
    printf("\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    return true;
}

bool  GlowingArcher::InputStream::SkipLine(void) {
    while (curr < endOfData && *curr != '\n') {
        NextChar();
    }
    if (*curr == '\n') {
        NextChar();
        return true;
    }
    return false;
}

bool  GlowingArcher::InputStream::SkipWhiteSpace(void) {
    if (curr >= endOfData || !isspace(*curr)) {
        return false;
    }
    while (curr < endOfData && isspace(*curr)) {
        NextChar();
    }
    return true;
}

// skips the current word. leaves curr pointing the
// first character after the end of the current word.
// assumes that if the first character of the current
// word is either ' or ", then we are to skip the
// quoted string. we allow escaped quotes in that string.
//
// returns false if there is no current word or if
// there was no closing quote found on a quoted string.
//
bool  GlowingArcher::InputStream::SkipWord(void) {
    if (curr >= endOfData || isspace(*curr)) {
        return false;
    }
    char q = *curr;
    NextChar();

    if (q == '\'' || q == '"') {
        while (curr < endOfData && *curr != q) {
            if (*curr == '\'' && *(curr + 1) == q) {
                NextChar();
            }
            NextChar();
        }
        if (*curr != q) {
            return false;
        }
        NextChar();
    } else {
        while (curr < endOfData && !isspace(*curr)) {
            NextChar();
        }
    }

    return true;
}

