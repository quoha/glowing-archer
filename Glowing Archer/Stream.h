//
//  Stream.h
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

#ifndef __Glowing_Archer__Stream__
#define __Glowing_Archer__Stream__

#include "Object.h"
#include "Text.h"
//#include "Stack.h"

namespace GlowingArcher {

    class InputStream : protected Object {
    public:
        InputStream(Text *fileName);
        ~InputStream();

        bool  Close(void);
        bool  Open(Text *fileName);

        Text *ErrorMessage(void) const { return errmsg; }
        bool  IsValid(void) const { return errmsg ? false : true; }

        bool  EndOfStream(void) const;
        bool  NextChar(void);
        char  PeekChar(void);
        bool  SkipLine(void);
        bool  SkipQuotedString(void);
        bool  SkipWhiteSpace(void);

        // Object inheritance
        bool Dump(void) const;

    private:
        Text *sourceName;
        Text *errmsg;
        char *data;
        char *curr;
        int   line;
    }; // class InputStream

    class OutputStream : protected Object {
    public:
        OutputStream(Text *fileName);
        ~OutputStream();
        
        bool  Close(void);
        bool  Open(Text *fileName);
        bool  Redirect(Text *fileName);

        Text *ErrorMessage(void) const { return errmsg; }
        bool  IsValid(void) const { return errmsg ? false : true; }

        bool  Write(const char *fmt, ...);
        bool  Write(Text *text);

        bool  Flush(void);

        // Object inheritance
        bool Dump(void) const;

    private:
        Text *targetName;
        Text *errmsg;
        Text *data;
    }; // class OutputStream

} // namespace GlowingArcher

#endif /* defined(__Glowing_Archer__Stream__) */
