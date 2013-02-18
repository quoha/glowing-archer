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
#include "Value.h"
#include <stdio.h>

bool GlowingArcher::ASTRoot::Add(GlowingArcher::AST *ast) {
    root = ast;
    return true;
}

bool GlowingArcher::ASTRoot::Dump(void) const {
    printf("  ast:\troot node\n");
    return root ? root->Dump() : true;
}

bool GlowingArcher::ASTRoot::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack) {
    bool result = true;
    AST *ast = root;
    while (result && ast) {
        AST *next = 0;
        result = ast->Execute(symtab, stack, &next);
        ast = next;
    }
    return result;
}

bool GlowingArcher::AST_If::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack, GlowingArcher::AST **next) {
    Value *value = stack->Pop();
    bool test = value ? value->IsTrue() : false;
    *next = test ? ifTrue : ifFalse;
    return true;
}

bool GlowingArcher::AST_If::Dump(void) const {
    printf("  ast:\tif\n");
    return true;
}


bool GlowingArcher::AST_Text::Dump(void) const {
    printf("  ast:\ttext\n");
    return true;
}


bool GlowingArcher::AST_Word::Dump(void) const {
    printf("  ast:\tword\n");
    return true;
}

bool GlowingArcher::AST_Word::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack, GlowingArcher::AST **next_) {
    // lookup word in the symbol table if needed
    Value *v = symtab->Lookup(name);
    if (!v) {
        printf("error:\tundefined word '%s'\n", name->CString());
        *next_ = 0;
        return false;
    }
    // execute the word
    bool result = v->Execute(symtab, stack);
    *next_ = result ? next : 0;

    return result;
}

