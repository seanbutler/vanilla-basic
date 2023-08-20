// interpreter.hpp

#pragma once

#include "token.hpp"

#include <map>
#include <vector>

namespace Interpreter {

    class Context {
    public:
        std::string filename;
        std::map<unsigned int, std::vector<Token>>::iterator current_line_itor;
        std::vector<Token>::iterator current_token_itor;
    };

    void report_execution_error( Interpreter::Context & context, 
                                    std::map<unsigned int, std::vector<Token>> & tokens,
                                    const std::string & message ) 
    {
        std::cerr << context.filename 
                << " (" << (*context.current_line_itor).first << ") : error - " 
                << message << std::endl;
    }

    void report_execution_info( Interpreter::Context & context, 
                                    std::map<unsigned int, std::vector<Token>> & tokens,
                                    const std::string & message ) 
    {
        std::cerr << context.filename 
                << " (" << (*context.current_line_itor).first << ") : info - " 
                << message << std::endl;
    }

    bool execute_lhs_expression(Interpreter::Context & context, 
                            std::map<unsigned int, std::vector<Token>> & tokens)
    {
        return false;
    }

    bool execute_rhs_expression(Interpreter::Context & context, 
                            std::map<unsigned int, std::vector<Token>> & tokens)
    {
        return false;
    }

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

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_REM ) {
            Interpreter::report_execution_info(context, tokens,  "comment" );
            return true;
        }

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_PRINT ) {
            Interpreter::report_execution_info(context, tokens,  "print" );

            if ( execute_rhs_expression(context, tokens) == false ) {
                Interpreter::report_execution_error(context, tokens,  "expression rhs execution problem" );
                return false;                
            }

            //
            // OK IF WE GOT HERE THEN 
            //  STD::COUT THE RESULT
            //

            return true;
        }

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_GOTO ) {
            Interpreter::report_execution_info(context, tokens,  "goto" );
            
           if ( execute_rhs_expression(context, tokens) == false ) {
                Interpreter::report_execution_error(context, tokens,  "expression rhs execution problem" );
                return false;                
            }

            //
            // OK IF WE GOT HERE THEN 
            //  SET LINE ITERATOR TO THE DESTINATION
            //

            return true;
        }

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_GOSUB ) {
            Interpreter::report_execution_info(context, tokens,  "gosub" );

           if ( execute_rhs_expression(context, tokens) == false ) {
                Interpreter::report_execution_error(context, tokens,  "expression rhs execution problem" );
                return false;                
            }

            //
            // OK IF WE GOT HERE THEN...
            //  SET LINE ITERATOR TO THE DESTINATION
            //  SET LINE RETURN VARIABLE TO THE TO CURRENT LINE
            //

            return true;
        }

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_RETURN ) {
            Interpreter::report_execution_info(context, tokens,  "return" );

            //  SET LINE ITERATOR TO THE LINE RETURN VARIABLE

            return true;
        }

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_INPUT ) {
            Interpreter::report_execution_info(context, tokens,  "input" );

            if ( execute_lhs_expression(context, tokens) == false) {
                Interpreter::report_execution_error(context, tokens,  "expression lhs execution problem" );
                return false;
            }

            //
            // OK IF WE GOT HERE THEN WRITE THE VALUE TO THE DESTINATION
            //

            // (*context.destination) = context.expression_value;


            return true;
        }

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_PRINT ) {
            Interpreter::report_execution_info(context, tokens,  "print" );
            return true;
        }

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_LET ) {
            Interpreter::report_execution_info(context, tokens,  "let" );

            if ( execute_lhs_expression(context, tokens) == false) {
                Interpreter::report_execution_error(context, tokens,  "expression lhs execution problem" );
                return false;
            }

            if ((*context.current_token_itor).symbol != Token::SymbolEnum::TOK_EQUALS ) {
                Interpreter::report_execution_error(context, tokens,  "expected equals/assignment after expression lhs" );
                return false;                
            }

            if ( execute_rhs_expression(context, tokens) == false ) {
                Interpreter::report_execution_error(context, tokens,  "expression rhs execution problem" );
                return false;                
            }

            //
            // OK IF WE GOT HERE THEN WRITE THE VALUE TO THE DESTINATION
            //

            // (*context.destination) = context.expression_value;

        }

        if ((*context.current_token_itor).token == Token::TokenEnum::TOK_DIM ) {
            Interpreter::report_execution_info(context, tokens,  "dim" );
            
            if ( execute_lhs_expression(context, tokens) == false) {
                Interpreter::report_execution_error(context, tokens,  "expression lhs execution problem" );
                return false;
            }

            if ((*context.current_token_itor).symbol != Token::SymbolEnum::TOK_LPAREN ) {
                Interpreter::report_execution_error(context, tokens,  "expected left parenthesis before array dimension expression" );
                return false;                
            }

            context.current_token_itor++;

            if ( execute_rhs_expression(context, tokens) == false ) {
                Interpreter::report_execution_error(context, tokens,  "expression rhs execution problem" );
                return false;                
            }

            if ((*context.current_token_itor).symbol != Token::SymbolEnum::TOK_RPAREN ) {
                Interpreter::report_execution_error(context, tokens,  "expected right parenthesis after array dimension expression" );
                return false;                
            }

            //
            // OK IF WE GOT HERE THEN DECLARE THE ARRAY TO THE SIZE OF THE EXPRESSION
            //

        }
        return true;
    }

    void execute_token_vector_map(struct Interpreter::Context & context, 
                            std::map<unsigned int, std::vector<Token>> & tokens)
    {
        context.current_line_itor = tokens.begin();
        bool status = true;

        while ( ( context.current_line_itor != tokens.end() && status != false )) {
            status = execute_token_vector(context, tokens);
            context.current_line_itor++;
        }
    }
}

