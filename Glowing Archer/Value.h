//
//  Value.h
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

#ifndef __Glowing_Archer__Value__
#define __Glowing_Archer__Value__

#include "AST.h"
#include "Stack.h"
#include "SymbolTable.h"
#include "Text.h"
#include "Value.h"

namespace GlowingArcher {
    
    class Value {
    public:
        Value(void);
        virtual ~Value();
        
        virtual bool Dump(void) const;
        virtual bool Execute(class SymbolTable *symtab, class Stack *stack);
        virtual bool Render(void) const;
        
    private:
    }; // class Value
    
    
    class Val_AST : public Value {
    public:
        Val_AST(AST *ast);
        virtual ~Val_AST();
        
        bool Dump(void) const;
        bool Execute(SymbolTable *symtab, Stack *stack);
        bool Render(void) const;
        
    private:
        AST *ast;
    }; // class Val_AST
    
    
    class Val_CFunc : public Value {
    public:
        Val_CFunc(void);
        virtual ~Val_CFunc();
        
        virtual bool Dump(void) const;
        virtual bool Execute(SymbolTable *symtab, Stack *stack);
        virtual bool Render(void) const;
        
    private:
    }; // class Val_CFunc
    
    
    class Val_Number : public Value {
    public:
        Val_Number(int number);
        virtual ~Val_Number();
        
        bool Dump(void) const;
        bool Execute(SymbolTable *symtab, Stack *stack);
        bool Render(void) const;
        
    private:
        int number;
    }; // class Val_Number
    
    
    class Val_Stack : public Value {
    public:
        Val_Stack(Stack *value);
        ~Val_Stack();
        
        bool Dump(void) const;
        bool Execute(SymbolTable *symtab, Stack *stack);
        bool Render(void) const;
        
    private:
        Stack *value;
    }; // class Val_Stack
    
    
    class Val_Text : public Value {
    public:
        Val_Text(Text *value);
        ~Val_Text();
        
        bool Dump(void) const;
        bool Execute(SymbolTable *symtab, Stack *stack);
        bool Render(void) const;
        
    private:
        Text *value;
    }; // class Val_Text
    
} // namespace GlowingArcher

#endif /* defined(__Glowing_Archer__Value__) */
