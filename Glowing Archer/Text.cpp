//
//  Text.cpp
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

#include "Text.h"
#include "Stack.h"
#include "SymbolTable.h"
#include <stdio.h>
#include <cstring>

GlowingArcher::Text::Text(void) : GlowingArcher::Value() {
    isNull    = true;
    isTainted = false;
    length    = 0;
    text      = new char[length + 1];
    text[length] = 0;
    
    hash = 0;
    for (int idx = 0; idx < length; idx++) {
		hash = (hash *  33) + text[idx];
	}
}

GlowingArcher::Text::Text(const char *text_, int length_) : GlowingArcher::Value() {
    isNull    = (text_ == 0) ? true : false;
    isTainted = false;
    if (length_ < 0) {
        length_ = (int)std::strlen(text_ ? text_ : "");
    }
    length = length_;
    text   = new char[length + 1];
    if (text_) {
        std::memcpy(text, text_, length);
    } else {
        std::memset(text, 0, length);
    }
    text[length] = 0;
    
    hash = 0;
    for (int idx = 0; idx < length; idx++) {
		hash = (hash *  33) + text[idx];
	}
}

GlowingArcher::Text::Text(Text *text_) : GlowingArcher::Value() {
    isNull    = text_ ? text_->isNull    : true;
    isTainted = text_ ? text_->isTainted : false;
    if (!text_) {
        length = 0;
    } else {
        length = text_->length;
    }
    text   = new char[length + 1];
    if (text_) {
        std::memcpy(text, text_->text, length);
    }
    text[length] = 0;

    hash = 0;
    for (int idx = 0; idx < length; idx++) {
		hash = (hash *  33) + text[idx];
	}
}

GlowingArcher::Text::Text(Text *t1, Text *t2) : GlowingArcher::Value() {
    if ((t1 && !t1->isNull) || (t2 && !t2->isNull)) {
        isNull = false;
    } else {
        isNull = true;
    }
    isTainted = (( t1 && t1->isTainted) || ( t2 && t2->isTainted)) ? true : false;
    length    = 0;
    if (t1) {
        length += t1->length;
    }
    if (t2) {
        length += t2->length;
    }
    text = new char[length + 1];
    if (t1 && t2) {
        std::memcpy(text, t1->text, t1->length);
        std::memcpy(text + t1->length, t2->text, t2->length);
    } else if (t1) {
        std::memcpy(text, t1->text, t1->length);
    } else {
        std::memcpy(text, t2->text, t2->length);
    }
    text[length] = 0;
}

GlowingArcher::Text::~Text() {
    delete [] text;
}

bool GlowingArcher::Text::Append(Text *text_) {
    if (text_) {
        if (isNull) {
            isNull = text_->isNull;
        }
        int   newLength = length + text_->length;
        char *newText   = new char[newLength + 1];
        
        std::memcpy(newText, text, length);
        std::memcpy(newText + newLength, text_->text, text_->length);
        newText[newLength] = 0;
        
        delete [] text;
        
        text   = newText;
        length = newLength;
    }
    return true;
}

bool GlowingArcher::Text::Dump(void) const {
    printf("%ctext:\t%s\n", isTainted ? '*' : ' ', isNull ? "((null))" : text);
    return true;
}

bool GlowingArcher::Text::Equal(Text *text_) const {
    if (text_ && length == text_->length && hash == text_->hash && std::strcmp(text, text_->text) == 0) {
        return true;
    }
    return false;
}

bool GlowingArcher::Text::Execute(GlowingArcher::SymbolTable *symtab, GlowingArcher::Stack *stack) {
    stack->Push(this);
    return true;
}

bool GlowingArcher::Text::Render(void) const {
    printf("%ctext:\t%s\n", isTainted ? 't' : ' ', text);
    return true;
}
