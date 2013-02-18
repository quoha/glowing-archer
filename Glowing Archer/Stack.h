//
//  Stack.h
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

#ifndef __Glowing_Archer__Stack__
#define __Glowing_Archer__Stack__

#include "Text.h"

namespace GlowingArcher {

    struct StackItem {
        StackItem *prev;
        StackItem *next;
        enum {siNumber, isText} kind;
        union {
            int   number;
            Text *text;
        } u;
    }; // struct StackItem
    
    class Stack {
    public:
        Stack(void);
        ~Stack();

        int        Height(void) const { return height; }
        StackItem *Pop(void);
        StackItem *Push(int        number);
        StackItem *Push(StackItem *s);
        StackItem *Push(Text      *text);

    private:
        int        height;
        StackItem *top;
        StackItem *bottom;
    }; // class Stack

} // namespace GlowingArcher

#endif /* defined(__Glowing_Archer__Stack__) */
