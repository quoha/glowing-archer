//
//  Stack.cpp
//  Glowing Archer
//
//  Created by Michael Henderson on 2/17/13.
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

#include "Stack.h"

GlowingArcher::Stack::Stack(void) : GlowingArcher::Value() {
    height = 0;
    top = bottom = 0;
}

GlowingArcher::Stack::~Stack() {
    //
}

bool GlowingArcher::Stack::Dump(void) const {
    return false;
}

bool GlowingArcher::Stack::Execute(class SymbolTable *symtab, class Stack *stack) {
    return false;
}

bool GlowingArcher::Stack::Render(void) const {
    return false;
}

GlowingArcher::Value *GlowingArcher::Stack::Pop(void) {
    StackItem *s = top;
    if (top) {
        height--;
        top = top->prev;
        if (top) {
            top->next = 0;
        } else {
            bottom = 0;
        }
    }
    Value *value = s->value;
    delete s;
    return value;
}

GlowingArcher::Value *GlowingArcher::Stack::Push(GlowingArcher::Value *value) {
    StackItem *s = new StackItem;
    s->value     = value;
    s->next      = 0;
    s->prev      = top;

    if (!top) {
        bottom = top = s;
    } else {
        top->next = s;
        top       = s;
    }
    
    height++;

    return value;
}
