//
//  Text.h
//  Glowing Archer
//
//  Created by Michael Henderson on 1/25/13.
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

#ifndef __Glowing_Archer__Text__
#define __Glowing_Archer__Text__

namespace GlowingArcher {
    
    class Text {
    public:
        Text(Text *text);
        Text(Text *text1, Text *text2);
        Text(const char *text, int length);
        ~Text();

        bool         Append(Text *text);
        const char  *CString(void) const { return text; }
        bool         Equal(Text *text) const;
        unsigned int Hash(void) const { return hash; }

        bool Dump(void) const;
        bool Render(void) const;

    private:
        int          length;
        char        *text;
        unsigned int hash;
        bool         isTainted;
    }; // class Text
    
} // namespace GlowingArcher

#endif /* defined(__Glowing_Archer__Text__) */
