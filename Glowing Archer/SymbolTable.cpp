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
#include "Text.h"
#include "Value.h"
#include <stdio.h>

GlowingArcher::SymbolTable::SymbolTable(void) {
    for (int idx = 0; idx < 1024; idx++) {
        table[idx] = 0;
    }
}

GlowingArcher::SymbolTable::~SymbolTable() {
    for (int idx = 0; idx < 1024; idx++) {
        SymbolTableEntry *e = table[idx];
        while (e) {
            SymbolTableEntry *n = e->next;
            delete e;
            e = n;
        }
    }
}

bool GlowingArcher::SymbolTable::Add(Text *name, Value *value) {
    SymbolTableEntry *e = new SymbolTableEntry;
    e->hash        = name->Hash();
    e->name        = name;
    e->value       = value;
    e->next        = table[e->hash % 1024];
    table[e->hash % 1024] = e;
    return true;
}

GlowingArcher::Value *GlowingArcher::SymbolTable::Lookup(Text *name) {
    SymbolTableEntry *e = table[name->Hash() % 1024];
    while (e && !name->Equal(e->name)) {
        e = e->next;
    }
    return e ? e->value : 0;
}

bool GlowingArcher::SymbolTable::Dump(void) const {
    printf("symtb:\t%s\n", "*** dump ***");
    for (int idx = 0; idx < 1024; idx++) {
        SymbolTableEntry *e = table[idx];
        if (e) {
            printf("..buk:\t%5d ------------\n", idx);
            while (e) {
                printf(".hash:\t%8x name %s\n", e->hash, e->name->CString());
                e->value->Dump();
                e = e->next;
            }
        }
    }
    return true;
}

