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

namespace GlowingArcher {
    
    // generic AST is simply a no-op
    //
    class AST {
    public:
        AST(void);
        virtual ~AST();

        virtual bool Dump(void) const;
        virtual AST *Execute(SymbolTable *symtab, Stack *stack);

    protected:
        AST *Next(void) const { return next; }
        void Next(AST *next_) { next = next_; }

    private:
        AST *next;
    }; // class AST

    class AST_If : public AST {
    public:
        AST_If(AST *branchIfTrue, AST *branchIfFalse);
        ~AST_If(void);

        bool Dump(void) const;
        AST *Execute(SymbolTable *symtab, Stack *stack);

    private:
        AST *ifTrue;
        AST *ifFalse;
    }; // class AST_If

    class AST_Text : public AST {
    public:
        AST_Text(Text *text);
        ~AST_Text(void);
        
        bool Dump(void) const;
        AST *Execute(SymbolTable *symtab, Stack *stack);

    private:
        Text *text;
    }; // class AST_Text

    class AST_Word : public AST {
    public:
        AST_Word(Text *name);
        ~AST_Word(void);
        
        bool Dump(void) const;
        AST *Execute(SymbolTable *symtab, Stack *stack);

    private:
        Text *name;
    }; // class AST_Word
    
} // namespace GlowingArcher

#endif /* defined(__Glowing_Archer__AST__) */
