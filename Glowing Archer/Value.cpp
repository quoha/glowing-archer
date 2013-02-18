//
//  Value.cpp
//  Glowing Archer
//
//  Created by Michael Henderson on 2/18/13.
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

#include "Value.h"

GlowingArcher::Value::Value(void) {
    //
}

GlowingArcher::Value::~Value() {
    //
}

bool GlowingArcher::Value::Dump(void) const {
    return false;
}

bool GlowingArcher::Value::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack) {
    return false;
}

bool GlowingArcher::Value::Render(void) const {
    return false;
}


GlowingArcher::Val_AST::Val_AST(AST *value_) {
    value = value_;
}

GlowingArcher::Val_AST::~Val_AST() {
    //
}

bool GlowingArcher::Val_AST::Dump(void) const {
    return value->Dump();
}

bool GlowingArcher::Val_AST::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack) {
    return value->Execute(symtab, stack);
}

bool GlowingArcher::Val_AST::Render(void) const {
    return value->Render();
}


GlowingArcher::Val_CFunc::Val_CFunc(void) {
    //
}

GlowingArcher::Val_CFunc::~Val_CFunc() {
    //
}

bool GlowingArcher::Val_CFunc::Dump(void) const {
    return false;
}

bool GlowingArcher::Val_CFunc::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack) {
    return false;
}

bool GlowingArcher::Val_CFunc::Render(void) const {
    return false;
}


GlowingArcher::Val_Number::Val_Number(int value_) {
    value = value_;
}

GlowingArcher::Val_Number::~Val_Number() {
    //
}

bool GlowingArcher::Val_Number::Dump(void) const {
    return false;
}

bool GlowingArcher::Val_Number::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack) {
    return false;
}

bool GlowingArcher::Val_Number::Render(void) const {
    return false;
}


GlowingArcher::Val_Stack::Val_Stack(GlowingArcher::Stack *value_) {
    value = value_;
}

GlowingArcher::Val_Stack::~Val_Stack() {
    //
}

bool GlowingArcher::Val_Stack::Dump(void) const {
    return value->Dump();
}

bool GlowingArcher::Val_Stack::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack) {
    return false;
}

bool GlowingArcher::Val_Stack::Render(void) const {
    return value->Render();
}


GlowingArcher::Val_Text::Val_Text(GlowingArcher::Text *value_) {
    value = value_;
}

GlowingArcher::Val_Text::~Val_Text() {
    //
}

bool GlowingArcher::Val_Text::Dump(void) const {
    return value->Dump();
}

bool GlowingArcher::Val_Text::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack) {
    return false;
}

bool GlowingArcher::Val_Text::Render(void) const {
    return value->Render();
}
