//
//  AST.cpp
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

#include "AST.h"
#include <stdio.h>

GlowingArcher::AST::AST(void) : GlowingArcher::Object("GlowingArcher::AST") {
    //
}

GlowingArcher::AST::~AST() {
    //
}

GlowingArcher::AST *GlowingArcher::AST::Execute(void) {
    return Next();
}

bool GlowingArcher::AST::Dump(void) const {
    printf("  ast:\tno-op\n");
    return true;
}

GlowingArcher::AST_Text::AST_Text(const char *text_, int length_, bool isTainted_) {
    text      = text_;
    length    = length_;
    isTainted = isTainted_;
}

GlowingArcher::AST_Text::~AST_Text() {
    //
}

bool GlowingArcher::AST_Text::Dump(void) const {
    printf("  ast:\ttext%s\n", isTainted ? " is tainted" : "");
    return true;
}

GlowingArcher::AST *GlowingArcher::AST_Text::Execute(void) {
    // push the text onto the stack
    // return the next AST in the tree
    return Next();
}

GlowingArcher::AST_Word::AST_Word(void) {
    //
}

GlowingArcher::AST_Word::~AST_Word() {
    //
}

bool GlowingArcher::AST_Word::Dump(void) const {
    printf("  ast:\tword\n");
    return true;
}

GlowingArcher::AST *GlowingArcher::AST_Word::Execute(void) {
    // lookup word in the symbol table if needed
    // execute the word
    // if it failed, return an error
    // otherwise, return the next node to execute
    return Next();
}

