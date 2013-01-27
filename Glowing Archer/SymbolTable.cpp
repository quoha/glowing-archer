//
//  SymbolTable.cpp
//  Glowing Archer
//
//  Created by Michael Henderson on 1/26/13.
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

#include "SymbolTable.h"
#include <stdio.h>

GlowingArcher::SymbolTable::SymbolTable(void) : GlowingArcher::Object("GlowingArcher::SymbolTable") {
    for (int idx = 0; idx < 1024; idx++) {
        table[idx] = 0;
    }
}

GlowingArcher::SymbolTable::~SymbolTable() {
    for (int idx = 0; idx < 1024; idx++) {
        struct Entry *e = table[idx];
        while (e) {
            struct Entry *n = e->next;
            delete e;
            e = n;
        }
    }
}

bool GlowingArcher::SymbolTable::Add(Text *name, Text *value) {
    struct Entry *e = new struct Entry;
    e->hash = value->Hash();
    e->name = name;
    e->obj  = value;
    e->next = table[e->hash];
    table[e->hash] = e;
    return true;
}

GlowingArcher::Object *GlowingArcher::SymbolTable::Lookup(Text *name) {
    struct Entry *e = table[name->Hash()];
    while (e) {
        if (name->Equal(e->name)) {
            return e->obj;
        }
        e = e->next;
    }
    return 0;
}

bool GlowingArcher::SymbolTable::Dump(void) const {
    printf("symtb:\t%s\n", "*** dump ***");
    return true;
}

