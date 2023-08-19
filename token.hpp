
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

    // inline static std::map<std::string, TokenEnum> keywords = {   
    //     { "null",       TokenEnum::TOK_NULL     },

    //     { "let",        TokenEnum::TOK_LET      },
    //     { "dim",        TokenEnum::TOK_DIM      },

    //     { "if",         TokenEnum::TOK_IF       },
    //     { "then",       TokenEnum::TOK_THEN     },

    //     { "for",        TokenEnum::TOK_FOR      },
    //     { "to",         TokenEnum::TOK_TO       },
    //     { "next",       TokenEnum::TOK_NEXT     },

    //     { "while",      TokenEnum::TOK_WHILE    },
    //     { "wend",       TokenEnum::TOK_ENDWHILE },

    //     { "input",      TokenEnum::TOK_INPUT    },
    //     { "print",      TokenEnum::TOK_PRINT    },

    //     { "goto",       TokenEnum::TOK_GOTO     },
    //     { "gosub",      TokenEnum::TOK_GOSUB    },
    //     { "return",     TokenEnum::TOK_RETURN   },
    //     { "rem",        TokenEnum::TOK_REM      }>
    // };

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

