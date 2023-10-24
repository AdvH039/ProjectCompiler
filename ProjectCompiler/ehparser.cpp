#pragma once
#include <string>
#include <optional>
#include "lexer.h"
#include "parser.h"
#include "error.h"
#include<unordered_map>


extern Tokenizer token_generator;
extern int EOF_Reached;

extern std::unordered_map<std::string, Token> symbol_table;
inline int  ERR_OCC = 0;
inline int ERR_203_CALLED = 0;



bool Adjective1_node(std::optional<Token> tkn)
{

	std::string adjective1_value;
	ERR_OCC = 0;
	ERR_203_CALLED = 0;

	if (tkn.has_value())
	{
		if ((*tkn).type == TOKEN_TYPE::Adword)  // Subject Phrase---> Adjective1 (optional) Subject (mandatory)
		{
			adjective1_value = str;
			int w_c = word_count;
			int l_c = line_count;
			token_generator.next_token();
			if (Subject_node(current_token) && !ERR_OCC)// check if subject comes after adword (in a valid sentence this must happen.)
			{
				if (symbol_table.count(adjective1_value)) //checking existence of lexeme in symbol table
				{
					// after sentence is confirmed to be syntactically and lexically valid check for semantic validity.
					if (symbol_table[adjective1_value].sub_type != TOKEN_SUB_TYPE::Adjective)
					{//if lexeme exists check for semantic error
						ERR_302(l_c, w_c);// raise semantic error 302
					}
				}
				else
				{// if it doesn't exist add the lexeme to the symbol table using it's token value as key and it's properties as it's value.
					(*tkn).sub_type = TOKEN_SUB_TYPE::Adjective;
					symbol_table[adjective1_value] = *tkn;
				}
				return SUCCESS;

			}
			else
			{
				if (EOF_REACHED == 2) // check if EOF occurs before sentence termination.
				{
					ERR_204();
				}
				return FAILURE;
			}


		}
		else if ((*tkn).type == TOKEN_TYPE::Eof)
		{
			EOF_REACHED = 1;
			return SUCCESS;

		}
		else //Subject phrase---> Subject when there is no Adjective1
		{

			bool r_value = Subject_node(tkn);
			if (EOF_REACHED == 2)// check if EOF occurs befor..
			{
				ERR_204();
			}
			return r_value;
		}
	}
	else
	{/* Handling of lexical error when the token itself is invalid */
		ERR_OCC = 1;
		ERR_101();
		token_generator.next_token();
		Subject_node(current_token);
		if (EOF_REACHED == 2)// check if Eof oc...
		{
			ERR_204();
		}
		return FAILURE;
	}


}
bool Subject_node(std::optional<Token> tkn)
{
	std::string subject_value = str;
	if (tkn.has_value())
	{
		if ((*tkn).type == TOKEN_TYPE::Noun)
		{
			int w_c = word_count;
			int l_c = line_count;
			token_generator.next_token();
			bool adv_node = Adverb_node(current_token);
			if (adv_node && !ERR_OCC)
			{
				if (symbol_table.count(subject_value))
				{
					if (symbol_table[subject_value].sub_type != TOKEN_SUB_TYPE::Subject)
					{//if lexeme exists check for semantic error
						ERR_301(l_c, w_c);
					}
				}
				else
				{//create new lexeme in symbol table
					(*tkn).sub_type = TOKEN_SUB_TYPE::Subject;
					symbol_table[subject_value] = *tkn;
				}
				return SUCCESS;
			}
			else if (adv_node && ERR_OCC)
			{
				return SUCCESS;
			}
			else
			{

				return FAILURE;

			}
		}
		else if ((*tkn).type == TOKEN_TYPE::Eof)
		{
			// Eof before sentence termination
			EOF_REACHED = 2;
			return FAILURE;

		}
		else
		{
			/*if subject is missing, call a  syntactical error and continue till a  potential end of the
			sentence is found--->error handling commences here.

*/			ERR_OCC = 1;
ERR_201();
Adverb_node(tkn);
return FAILURE;
		}


	}
	else
	{
		/* Handling of lexical error when token itself is invalid. */
		ERR_OCC = 1;
		ERR_102();
		token_generator.next_token();
		Adverb_node(current_token);
		return FAILURE;
	}

}
bool Adverb_node(std::optional<Token> tkn)
{
	std::string adverb_value;
	if (tkn.has_value())
	{
		if ((*tkn).type == TOKEN_TYPE::Adword)
		{
			int w_c = word_count;
			int l_c = line_count;
			adverb_value = str;
			token_generator.next_token();
			bool v_node = Verb_node(current_token);
			if (v_node && !ERR_OCC)// Verb phrase---> Adverb (optional) Verb (mandatory)
			{

				if (symbol_table.count(adverb_value))
				{
					if (symbol_table[adverb_value].sub_type != TOKEN_SUB_TYPE::Adverb)
					{//if lexeme exists check for semantic error
						ERR_302(l_c, w_c);
					}
				}
				else
				{
					// else add new lexeme
					(*tkn).sub_type = TOKEN_SUB_TYPE::Adverb;
					symbol_table[adverb_value] = *tkn;
				}
				return SUCCESS;
			}
			else if (v_node && ERR_OCC)
			{
				return SUCCESS;
			}
			else
			{
				return FAILURE;
			}


		}
		else if ((*tkn).type == TOKEN_TYPE::Eof)
		{
			//ERR_204();
			EOF_REACHED = 2;
			return FAILURE;
		}
		else
		{
			return Verb_node(tkn);
		}
	}
	else
	{
		ERR_OCC = 1;
		ERR_103();
		token_generator.next_token();
		Verb_node(current_token);
		return FAILURE;

	}



}
bool Verb_node(std::optional<Token> tkn)
{
	std::string verb_value;
	if (tkn.has_value())
	{
		if ((*tkn).type == TOKEN_TYPE::Verb)
		{

			verb_value = str;
			token_generator.next_token();
			bool ad2_node = Adjective2_node(current_token);
			if (ad2_node && !ERR_OCC)
			{
				if (!symbol_table.count(verb_value))
				{
					symbol_table[verb_value] = *tkn;
				}
				return SUCCESS;
			}
			else if (ad2_node && ERR_OCC)
			{
				return SUCCESS;
			}

			else
			{
				return FAILURE;
			}
		}

		else if ((*tkn).type == TOKEN_TYPE::Eof)
		{
			//ERR_204();
			EOF_REACHED = 2;
			return FAILURE;
		}
		else
		{
			ERR_OCC = 1;
			ERR_202();
			Adjective2_node(tkn);
			return FAILURE;
		}
	}


	else
	{
		ERR_OCC = 1;
		ERR_104();
		token_generator.next_token();
		Adjective2_node(current_token);
		return FAILURE;
	}


}
bool Adjective2_node(std::optional<Token> tkn)
{
	std::string adjective2_value;



	if (tkn.has_value())
	{
		if ((*tkn).type == TOKEN_TYPE::Adword)// Object Phrase ---> Adjective2 (optional) Object (mandatory only when adjective 2 precedes it)
		{
			int w_c = word_count;
			int l_c = line_count;
			adjective2_value = str;
			token_generator.next_token();
			std::optional<Token> temp_token = current_token;
			bool obj_node = Object_node(current_token);
			if (obj_node && !ERR_OCC)
			{
				if (symbol_table.count(adjective2_value))
				{
					if (symbol_table[adjective2_value].sub_type != TOKEN_SUB_TYPE::Adjective)
					{
						ERR_302(l_c, w_c);
					}
				}
				else
				{
					(*tkn).sub_type = TOKEN_SUB_TYPE::Adjective;
					symbol_table[adjective2_value] = *tkn;
				}
				return SUCCESS;
			}
			else if (obj_node && ERR_OCC)
			{
				return SUCCESS;
			}
			else if (!obj_node)
			{
				ERR_OCC = 1;
				ERR_201();
				Punctuation_node(temp_token);
				return FAILURE;


			}
			else
			{
				return FAILURE;
			}


		}
		else if ((*tkn).type == TOKEN_TYPE::Eof)
		{
			//ERR_204();
			EOF_REACHED = 2;
			return FAILURE;
		}

		else
		{

			bool rvalue = Object_node(tkn);
			if (!rvalue)
			{
				return Punctuation_node(tkn);
			}
			return SUCCESS;

		}
	}

	else
	{
		ERR_OCC = 1;
		ERR_101();
		token_generator.next_token();
		Object_node(current_token);
		return FAILURE;

	}
}

bool Object_node(std::optional<Token> tkn)
{

	std::string object_value;

	if (tkn.has_value())
	{
		if ((*tkn).type == TOKEN_TYPE::Noun)
		{
			int w_c = word_count;
			int l_c = line_count;
			object_value = str;
			token_generator.next_token();
			bool punc_node = Punctuation_node(current_token);
			if (punc_node && !ERR_OCC)
			{
				if (symbol_table.count(object_value))
				{
					if (symbol_table[object_value].sub_type != TOKEN_SUB_TYPE::Object)
					{//if lexeme exists check for semantic error
						ERR_301(l_c, w_c);
					}
				}
				else
				{
					(*tkn).sub_type = TOKEN_SUB_TYPE::Object;
					symbol_table[object_value] = *tkn;
				}
				return SUCCESS;

			}
			else if (punc_node && ERR_OCC)
			{
				return SUCCESS;
			}
			else
			{
				return FAILURE;
			}
		}

		else if ((*tkn).type == TOKEN_TYPE::Eof)
		{
			//ERR_204();
			EOF_REACHED = 2;
			return FAILURE;
		}
		else
		{
			return FAILURE;
		}


	}

	else
	{
		ERR_OCC = 1;
		ERR_102();
		token_generator.next_token();
		Punctuation_node(current_token);
		return FAILURE;
	}

}
bool Punctuation_node(std::optional<Token> tkn)
{

	// Punctuation phrase ---> Punctuation (mandatory)

	if (tkn.has_value())
	{
		if ((*tkn).type == TOKEN_TYPE::Eof)
		{
			EOF_REACHED = 2;
			return FAILURE;
		}
		if ((*tkn).type != TOKEN_TYPE::Punc)
		{
			if (!ERR_203_CALLED)
			{
				ERR_203();
				ERR_203_CALLED = 1;

			}
			ERR_OCC = 1;
			return FAILURE;
		}


		if (!symbol_table.count(str) && !ERR_OCC)
		{

			symbol_table[str] = *tkn;
		}
		token_generator.next_token();
		return SUCCESS;
	}
	else
	{
		ERR_105();
		token_generator.next_token();
		Adjective1_node(current_token);
		return FAILURE;
	}
}