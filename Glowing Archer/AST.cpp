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

GlowingArcher::AST::AST(void) {
    next = 0;
}

GlowingArcher::AST::~AST() {
    //
}

GlowingArcher::AST *GlowingArcher::AST::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack) {
    return Next();
}

bool GlowingArcher::AST::Dump(void) const {
    printf("  ast:\tno-op\n");
    return true;
}

GlowingArcher::AST_If::AST_If(GlowingArcher::AST *branchIfTrue, GlowingArcher::AST *branchIfFalse) {
    ifTrue  = branchIfTrue;
    ifFalse = branchIfFalse;
}

GlowingArcher::AST_If::~AST_If() {
    //
}

GlowingArcher::AST *GlowingArcher::AST_If::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack) {
    bool test = true;
    AST *result = 0;
    if (test && ifTrue) {
        result = ifTrue->Execute(symtab, stack);
    }
    if (!test && ifFalse) {
        result = ifFalse->Execute(symtab, stack);
    }
    return result;
}

bool GlowingArcher::AST_If::Dump(void) const {
    printf("  ast:\tif\n");
    return true;
}

GlowingArcher::AST_Text::AST_Text(GlowingArcher::Text *text_) {
    text      = text_;
}

GlowingArcher::AST_Text::~AST_Text() {
    //
}

bool GlowingArcher::AST_Text::Dump(void) const {
    printf("  ast:\ttext\n");
    return true;
}

GlowingArcher::AST *GlowingArcher::AST_Text::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack) {
    // push the text onto the stack
    stack->Push(new Val_Text(text));

    // return the next AST in the tree
    return Next();
}

GlowingArcher::AST_Word::AST_Word(GlowingArcher::Text *name_) {
    name = name_;
}

GlowingArcher::AST_Word::~AST_Word() {
    //
}

bool GlowingArcher::AST_Word::Dump(void) const {
    printf("  ast:\tword\n");
    return true;
}

GlowingArcher::AST *GlowingArcher::AST_Word::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack) {
    // lookup word in the symbol table if needed
    Value *v = symtab->Lookup(name);
    if (!v) {
        printf("error:\tundefined word '%s'\n", name->CString());
        return 0;
    }
    // execute the word
    // if it failed, return an error
    // otherwise, return the next node to execute
    return Next();
}

