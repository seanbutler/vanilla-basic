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

#include "token.hpp"

#include <map>
#include <vector>
#include <stack>

namespace Interpreter {

    class Context {
    public:
        std::string filename;
        std::map<unsigned int, std::vector<Token>>::iterator current_line_itor;
        std::vector<Token>::iterator current_token_itor;
        std::stack<std::map<unsigned int, std::vector<Token>>::iterator> gosub_return_destination_stack;
        std::map<std::string, Token> variables;

        Token source;
        Token destination;
    };

    // ------------------------------------------------------------

    void report_execution_error( Interpreter::Context & context, 
                                    std::map<unsigned int, std::vector<Token>> & tokens,
                                    const std::string & message ) 
    {
        std::cerr << context.filename
                << " (" << (*context.current_line_itor).first << ") : error - " 
                << message
                << " at or near " 
                << (*context.current_token_itor) 
                << std::endl;
    }

    void report_execution_info( Interpreter::Context & context, 
                                    std::map<unsigned int, std::vector<Token>> & tokens,
                                    const std::string & message ) 
    {
        return;

        std::cerr << context.filename
                << " (" << (*context.current_line_itor).first << ") : info - " 
                << message
                << " at or near " 
                << (*context.current_token_itor)
                << std::endl;
    }

    // ------------------------------------------------------------

    bool execute_lhs_expression(Interpreter::Context & context, 
                            std::map<unsigned int, std::vector<Token>> & tokens)
    {
        if ((*context.current_token_itor).type == Token::TokenTypeEnum::IDENTIFIER ) {

            context.destination = (*context.current_token_itor);

            return true;

        }

        Interpreter::report_execution_error(context, tokens, "lhs expression problem" );
        return false;
    }

    // ------------------------------------------------------------

    bool execute_rhs_expression(Interpreter::Context & context, 
                            std::map<unsigned int, std::vector<Token>> & tokens)
    {

        std::stack<Token> expression_value_stack;
        std::stack<Token> expression_symbol_stack;
        Token val1, val2, op, res;

        while ( ( context.current_token_itor != (*context.current_line_itor).second.end() )
                && ( (*context.current_token_itor).type != Token::TokenTypeEnum::KEYWORD ) 
                &&  ( (*context.current_token_itor).symbol != Token::SymbolEnum::TOK_RBRACKET ) )
        {
            // if ( (*context.current_token_itor).token == Token::TokenEnum::TOK_L ) 
            // {
            //     expression_symbol_stack.push((*context.current_token_itor));
            // }
            if ((*context.current_token_itor).type == Token::TokenTypeEnum::NUMBER ) 
            {
                expression_value_stack.push((*context.current_token_itor));
            }
            else if ((*context.current_token_itor).type == Token::TokenTypeEnum::IDENTIFIER ) 
            {
                expression_value_stack.push((*context.current_token_itor));
            }
            else if ( (*context.current_token_itor).type == Token::TokenTypeEnum::SYMBOL ) 
            {
                expression_symbol_stack.push((*context.current_token_itor));
            }

            context.current_token_itor++;

            while ( !expression_symbol_stack.empty() && ( expression_value_stack.size() >= 2 ) )
            {
                //
                // get the 2 values
                //

                if ( expression_value_stack.top().type == Token::TokenTypeEnum::IDENTIFIER )
                {
                    val2 = context.variables[expression_value_stack.top().string];
                }                
                else // assume its a value
                {
                    val2 = expression_value_stack.top().number;
                }                
                expression_value_stack.pop();

                if ( expression_value_stack.top().type == Token::TokenTypeEnum::IDENTIFIER )
                {
                    val1 = context.variables[expression_value_stack.top().string];
                }                
                else // assume its a value
                {
                    val1 = expression_value_stack.top().number;
                }                 
                expression_value_stack.pop();

                //
                // get the operator
                //
                op = expression_symbol_stack.top();
                expression_symbol_stack.pop();

                switch(op.symbol) {
                    case Token::SymbolEnum::TOK_ADD:
                        res.number = val1.number + val2.number;
                        break;

                    case Token::SymbolEnum::TOK_SUB:
                        res.number = val1.number - val2.number;
                        break;
                    
                    case Token::SymbolEnum::TOK_MUL:
                        res.number = val1.number * val2.number;
                        break;

                    case Token::SymbolEnum::TOK_DIV:
                        res.number = val1.number / val2.number;
                        break;

                    case Token::SymbolEnum::TOK_EQUALS:
                        res.number = (float)(val1.number == val2.number);
                        break;

                    case Token::SymbolEnum::TOK_NOTEQUAL:
                        res.number = (float)(val1.number != val2.number);
                        break;

                    case Token::SymbolEnum::TOK_GREATERTHAN:
                        res.number = (float)val1.number > val2.number;
                        break;

                    case Token::SymbolEnum::TOK_GREATERTHANEQUAL:
                        res.number = (float)val1.number >= val2.number;
                        break;

                    case Token::SymbolEnum::TOK_LESSTHAN:
                        res.number = (float)val1.number < val2.number;
                        break;

                    case Token::SymbolEnum::TOK_LESSTHANEQUAL:
                        res.number = (float)val1.number <= val2.number;
                        break;  

                    case Token::SymbolEnum::TOK_RBRACKET:
                        std::cout << "IMPOSSIBLE Right Bracket, Now What?" << std::endl;
                        return false;

                    default:
                        std::cout << "Unknown Expression Error" << std::endl;
                        return false;
                }

                res.type = Token::TokenTypeEnum::NUMBER;
                expression_value_stack.push(res);

            }

        }
    
        context.source = expression_value_stack.top();
        return true;

    }

    // ------------------------------------------------------------

    bool execute_token_vector(Interpreter::Context & context, 
                            std::map<unsigned int, std::vector<Token>> & tokens)
    {
        context.current_token_itor = (*context.current_line_itor).second.begin();

        if ((*context.current_token_itor).type != Token::TokenTypeEnum::NUMBER ) {
            Interpreter::report_execution_error(context, tokens,  "all lines should start with a line number" );
            return false;
        }

        context.current_token_itor++;

        if ((*context.current_token_itor).type != Token::TokenTypeEnum::KEYWORD ) {
            Interpreter::report_execution_error(context, tokens,  "expected a keyword" );
            return false;
        }

        // ---------- REM ----------

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_REM ) {
            Interpreter::report_execution_info(context, tokens,  "comment" );
            context.current_line_itor++;
            return true;
        }

        // ---------- GOTO ----------

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_GOTO ) {
            Interpreter::report_execution_info(context, tokens,  "got goto" );
            
            context.current_token_itor++;

           if ( execute_rhs_expression(context, tokens) == false ) {
                Interpreter::report_execution_error(context, tokens,  "expression rhs execution problem" );
                return false;                
            }

            if ( context.source.type == Token::TokenTypeEnum::NUMBER )
            {
                context.current_line_itor = tokens.find(context.source.number);
                return true;
            }
            else if ( context.source.type == Token::TokenTypeEnum::IDENTIFIER )
            {
                context.current_line_itor = tokens.find((context.variables[context.source.string]).number);
                return true;
            }

            return true;                
        }

        // ---------- GOSUB ----------

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_GOSUB ) {
            Interpreter::report_execution_info(context, tokens,  "gosub" );

            context.current_token_itor++;

           if ( execute_rhs_expression(context, tokens) == false ) {
                Interpreter::report_execution_error(context, tokens,  "expression rhs execution problem" );
                return false;                
            }

            //
            //  SET LINE RETURN VARIABLE TO THE TO CURRENT LINE
            //

            context.gosub_return_destination_stack.push(context.current_line_itor++); 

            //
            //  SET LINE ITERATOR TO THE DESTINATION
            //

            if ( context.source.type == Token::TokenTypeEnum::NUMBER )
            {
                context.current_line_itor = tokens.find(context.source.number);
                return true;
            }
            else if ( context.source.type == Token::TokenTypeEnum::IDENTIFIER )
            {
                context.current_line_itor = tokens.find(context.variables[context.source.string].number);
                return true;
            }

            return true;
        }

        // ---------- RETURN ----------

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_RETURN ) {
            Interpreter::report_execution_info(context, tokens,  "return" );

            context.current_line_itor = context.gosub_return_destination_stack.top(); 
            context.gosub_return_destination_stack.pop(); 

            context.current_line_itor++;

            return true;
        }

        // ---------- INPUT ----------

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_INPUT ) {
            Interpreter::report_execution_info(context, tokens,  "input" );

            context.current_token_itor++;

            if ( execute_lhs_expression(context, tokens) == false) {
                Interpreter::report_execution_error(context, tokens,  "expression lhs execution problem" );
                return false;
            }

            //
            // OK IF WE GOT HERE THEN WRITE THE VALUE TO THE DESTINATION
            //
            float tmp;
            std::cin >> tmp;
            context.variables[context.destination.string].number = tmp;

            context.current_line_itor++;
            return true;
        }

        // ---------- PRINT ----------

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_PRINT ) {
            Interpreter::report_execution_info(context, tokens,  "got print" );

            context.current_token_itor++;

            if ( (*context.current_token_itor).type == Token::TokenTypeEnum::STRING ) {
                std::cout << (*context.current_token_itor).string << std::endl;
            }
            else 
            {
                if ( execute_rhs_expression(context, tokens) == false ) {
                    Interpreter::report_execution_error(context, tokens,  "expression rhs execution problem" );
                    return false;                
                }

                if ( context.source.type == Token::TokenTypeEnum::IDENTIFIER )
                {
                    std::cout << context.variables[context.source.string].number << std::endl;
                }
                else
                {
                    std::cout << context.source << std::endl;
                }
            }

            context.current_line_itor++;
            return true;
        }

        // ---------- LET ----------

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_LET ) {
            Interpreter::report_execution_info(context, tokens,  "got let" );
            
            context.current_token_itor++;
            
            if ( execute_lhs_expression(context, tokens) == false) {
                Interpreter::report_execution_error(context, tokens,  "expression lhs execution problem" );
                return false;
            }

            context.current_token_itor++;

            if ((*context.current_token_itor).symbol != Token::SymbolEnum::TOK_EQUALS ) {
                Interpreter::report_execution_error(context, tokens,  "expected equals/assignment after expression lhs" );
                return false;                
            }

            context.current_token_itor++;

            if ( execute_rhs_expression(context, tokens) == false ) {
                Interpreter::report_execution_error(context, tokens,  "expression rhs execution problem" );
                return false;                
            }

            //
            // OK IF WE GOT HERE THEN WRITE THE VALUE TO THE DESTINATION
            //

            context.variables[context.destination.string] = context.source;

            context.current_line_itor++;
            return true;
        }

        // ---------- DIM (incomplete) ----------

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_DIM ) {
            Interpreter::report_execution_info(context, tokens,  "dim" );
            
            context.current_token_itor++;

            if ( execute_lhs_expression(context, tokens) == false) {
                Interpreter::report_execution_error(context, tokens,  "expression lhs execution problem" );
                return false;
            }

            context.current_token_itor++;

            if ((*context.current_token_itor).symbol != Token::SymbolEnum::TOK_LPAREN ) {
                Interpreter::report_execution_error(context, tokens,  "expected left parenthesis before array dimension expression" );
                return false;                
            }

            context.current_token_itor++;

            if ( execute_rhs_expression(context, tokens) == false ) {
                Interpreter::report_execution_error(context, tokens,  "expression rhs execution problem" );
                return false;                
            }

            context.current_token_itor++;

            if ((*context.current_token_itor).symbol != Token::SymbolEnum::TOK_RPAREN ) {
                Interpreter::report_execution_error(context, tokens,  "expected right parenthesis after array dimension expression" );
                return false;                
            }

            //
            // OK IF WE GOT HERE THEN DECLARE THE ARRAY TO THE SIZE OF THE EXPRESSION
            //
        }

        // context.current_line_itor++;
        return true;
    }

    void execute_token_vector_map(struct Interpreter::Context & context, 
                            std::map<unsigned int, std::vector<Token>> & tokens)
    {
        context.current_line_itor = tokens.begin();
        bool status = true;

        while ( ( context.current_line_itor != tokens.end() && status != false )) {
            status = execute_token_vector(context, tokens);
            
        }

    }

}
