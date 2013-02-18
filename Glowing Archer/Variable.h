//
//  Variable.h
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

#ifndef __Glowing_Archer__Variable__
#define __Glowing_Archer__Variable__

#include "Text.h"

namespace GlowingArcher {
    class Variable {
    public:
        Variable(Text *name);
        virtual ~Variable();
        
        Text *Name(void) { return name; }
        virtual bool Dump(void) const;
        virtual bool Execute(class SymbolTable *symtab, class Stack *stack);
        virtual bool Render(void) const;

    private:
        Text *name;
    }; // class Variable

    class VarAST : public Variable {
    public:
        VarAST(Text *name, class AST *ast);
        ~VarAST();
    private:
        class AST *ast;
    }; // class VarAST
    
    class VarCFunc : public Variable {
    public:
        VarCFunc(Text *name, int value);
        ~VarCFunc();
    private:
    }; // class VarCFunc

    class VarNumber : public Variable {
    public:
        VarNumber(Text *name, int value);
        ~VarNumber();
    private:
        int value;
    }; // class VarNumber
    
    class VarStack : public Variable {
    public:
        VarStack(Text *name, class Stack *value);
        ~VarStack();
    private:
        class Stack *value;
    }; // class VarText

    class VarText : public Variable {
    public:
        VarText(Text *name, Text *value);
        ~VarText();
    private:
        Text *value;
    }; // class VarText

} // namespace GlowingArcher

#endif /* defined(__Glowing_Archer__Variable__) */
