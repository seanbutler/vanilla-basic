/*

MIT License

Copyright (c) 2023 sean butler

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#pragma once

// ----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

// ----------------------------------------------------------------------

class Token {

public:

    enum TokenTypeEnum : int {
        UNKNOWN = 0, 
        KEYWORD, 
        IDENTIFIER, 
        SYMBOL, 
        OP,
        NUMBER, 
        STRING
    };

    inline static std::string _tokentype_enum_debug_table[] =
    {
        "UNKNOWN", 
        "KEYWORD", 
        "IDENTIFIER", 
        "SYMBOL", 
        "OP", 
        "NUMBER", 
        "STRING"
    };

    Token() 
    : type{TokenTypeEnum::UNKNOWN}
    , token{TokenEnum::TOK_NULL}
    , symbol{SymbolEnum::TOK_UNKNOWN}
    , string{""}
    , number{0.0f}
    {

    }

    Token(float num) 
    : type{TokenTypeEnum::NUMBER}
    , number{num}
    {

    }

    Token(TokenTypeEnum ty, std::string str) 
    : type{ty}
    , string{str}
    {

    }

    enum TokenEnum : int {
        TOK_NULL = 0,
        TOK_LET, 
        TOK_DIM, 
        TOK_IF, TOK_THEN,
        TOK_FOR, TOK_TO, TOK_NEXT,
        TOK_WHILE, TOK_ENDWHILE,
        TOK_INPUT, TOK_PRINT,
        TOK_GOTO, TOK_GOSUB, TOK_RETURN, 
        TOK_REM
    };

    inline static std::string _token_enum_debug_table[] = {
        "TOK_NULL", 
        "TOK_LET", 
        "TOK_DIM", 
        "TOK_IF", "TOK_THEN",
        "TOK_FOR", "TOK_TO", "TOK_NEXT",
        "TOK_WHILE", "TOK_ENDWHILE",
        "TOK_INPUT", "TOK_PRINT",
        "TOK_GOTO", "TOK_GOSUB", "TOK_RETURN", 
        "TOK_REM",
    };


    inline static std::string _symbols_debug_table[] = {
        "?",
        "=",
        "!=",
        "+", "-", "*", "/", 
        ">", "<",
        ">=", "<=", 
        "(", ")",
        "[", "]" 
    };

    enum SymbolEnum : int {
        TOK_UNKNOWN = 0, 
        TOK_EQUALS, 
        TOK_NOTEQUAL, 
        TOK_ADD, TOK_SUB, TOK_MUL, TOK_DIV, 
        TOK_GREATERTHAN, TOK_LESSTHAN,  
        TOK_GREATERTHANEQUAL, TOK_LESSTHANEQUAL, 
        TOK_LPAREN, TOK_RPAREN,
        TOK_LBRACKET, TOK_RBRACKET
    };

    TokenTypeEnum type;
    TokenEnum token;
    SymbolEnum symbol;
    std::string string;
    double  number;

    friend std::ostream& operator<<(std::ostream& target, const Token& source);    
};

// ----------------------------------------------------------------------

std::ostream& operator<<(std::ostream& target, const Token& source)
{ 
    switch(source.type)
    {

        case Token::TokenTypeEnum::NUMBER :
            target << Token::_tokentype_enum_debug_table[source.type] 
                    << " "  
                    // << std::left
                    // << std::setw(32)
                    << source.number;
            break;

        case Token::TokenTypeEnum::SYMBOL :
            target << Token::_tokentype_enum_debug_table[source.type] 
                    << " " << Token::_symbols_debug_table[source.symbol];
            break;

        case Token::TokenTypeEnum::IDENTIFIER :
            target << Token::_tokentype_enum_debug_table[source.type] 
                    << " " << source.string;
            break;

        case Token::TokenTypeEnum::KEYWORD :
            target << Token::_tokentype_enum_debug_table[source.type] 
                    << " " << source.string;
            break;

        case Token::TokenTypeEnum::STRING :
            target << Token::_tokentype_enum_debug_table[source.type] 
                    << " " << source.string;
            break;

        default:
            target << Token::_tokentype_enum_debug_table[source.type] 
                    << " " << source.token 
                    << " " << source.symbol 
                    << " " << source.string 
                    << " " << source.number;
            break;
    }
    
    return target;          //Make chaining work
}

// ----------------------------------------------------------------------

