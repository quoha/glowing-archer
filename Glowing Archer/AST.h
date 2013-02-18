//
//  AST.h
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

#ifndef __Glowing_Archer__AST__
#define __Glowing_Archer__AST__

#include "Stack.h"
#include "SymbolTable.h"
#include "Text.h"
#include "Value.h"

namespace GlowingArcher {

    // generic AST is simply a no-op
    //
    class AST {
    public:
        AST(void) {
            //
        }
        virtual ~AST() {
            //
        }

        virtual bool Dump(void) const {
            return false;
        }
        virtual bool Execute(SymbolTable *symtab, Stack *stack, AST **next) {
            *next = 0;
            return false;
        }
        virtual bool Render(void) const {
            return false;
        }
    }; // class AST

    class AST_If : public AST {
    public:
        AST_If(AST *branchIfTrue, AST *branchIfFalse) {
            ifTrue  = branchIfTrue;
            ifFalse = branchIfFalse;
        }
        ~AST_If(void) {
            //
        }

        bool Dump(void) const;
        bool Execute(SymbolTable *symtab, Stack *stack, AST **next);

    private:
        AST *ifTrue;
        AST *ifFalse;
        bool test;
    }; // class AST_If

    class AST_Text : public AST {
    public:
        AST_Text(Text *text_) {
            text = text_;
        }
        ~AST_Text(void) {
            //
        }

        bool Dump(void) const;
        bool Execute(SymbolTable *symtab, Stack *stack, AST **next_) {
            bool result = text->Execute(symtab, stack);
            *next_ = result ? next : 0;
            return result;
        }

    private:
        AST  *next;
        Text *text;
    }; // class AST_Text

    class AST_Word : public AST {
    public:
        AST_Word(Text *name_) {
            name = name_;
            func = 0;
        }
        ~AST_Word(void) {
            //
        }
        
        bool Dump(void) const;
        bool Execute(SymbolTable *symtab, Stack *stack, AST **next);
        AST *Next(void) const {
            return next;
        }

    private:
        AST   *next;
        Text  *name;
        Value *func;
    }; // class AST_Word

    
    class ASTRoot : public GlowingArcher::Value {
    public:
        ASTRoot(void) : Value() {
            root = 0;
        }
        ~ASTRoot() {
            //
        }

        virtual bool Dump(void) const;
        virtual bool Execute(SymbolTable *symtab, Stack *stack);
        virtual bool Render(void) const {
            return false;
        }

    private:
        AST *root;
    }; // class ASTRoot

} // namespace GlowingArcher

#endif /* defined(__Glowing_Archer__AST__) */
