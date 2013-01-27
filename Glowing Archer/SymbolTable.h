//
//  SymbolTable.h
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

#ifndef __Glowing_Archer__SymbolTable__
#define __Glowing_Archer__SymbolTable__

#include "Object.h"
#include "Text.h"

namespace GlowingArcher {
    
    class SymbolTable : public Object {
    public:
        SymbolTable(void);
        ~SymbolTable();

        bool    Add(Text *name, Text *value);
        Object *Lookup(Text *name);

        // Object inheritance
        bool Dump(void) const;

    private:
        struct Entry {
            unsigned int  hash;
            Text         *name;
            Object       *obj;
            struct Entry *next;
        } *table[1024];
    }; // class SymbolTable
    
} // namespace GlowingArcher

#endif /* defined(__Glowing_Archer__SymbolTable__) */
