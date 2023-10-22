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



bool Adjective1_node(std::optional<Token> tkn)
{
	std::string adjective1_value;
	
	if (tkn.has_value())
	{
		if ((*tkn).type == TOKEN_TYPE::Adword)  // Subject Phrase---> Adjective1 Subject
		{
			adjective1_value = str;
			token_generator.next_token();
			if (Subject_node(current_token))
			{
				if (symbol_table.count(adjective1_value)) //checking existence of lexeme in map
				{
					if (symbol_table[adjective1_value].sub_type != TOKEN_SUB_TYPE::Adjective)
					{//if lexeme exists check for semantic error
						ERR_302();
					}
				}
				else
				{// if it doesn't exist add the lexeme using it's value as key
					(*tkn).sub_type = TOKEN_SUB_TYPE::Adjective;
					symbol_table[adjective1_value] = *tkn;
				}
				return SUCCESS;

			}
			else
			{
				if (EOF_REACHED == 2)
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
			
			bool r_value= Subject_node(tkn);
			if (EOF_REACHED == 2)
			{
				ERR_204();
			}
			return r_value;
		}
	}
	else
	{
		ERR_101();
		token_generator.next_token();
		Subject_node(current_token);
		if (EOF_REACHED == 2)
		{
			ERR_204();
		}
		return FAILURE;
	}
	

}
bool Subject_node(std::optional<Token> tkn)
{
	std::string subject_value=str;
	if (tkn.has_value())
	{
		if ((*tkn).type == TOKEN_TYPE::Noun)
		{
			
			token_generator.next_token();
			if (Adverb_node(current_token))
			{
				if (symbol_table.count(subject_value))
				{
					if (symbol_table[subject_value].sub_type != TOKEN_SUB_TYPE::Subject)
					{//if lexeme exists check for semantic error
						ERR_301();
					}
				}
				else
				{
					(*tkn).sub_type = TOKEN_SUB_TYPE::Subject;
					symbol_table[subject_value] = *tkn;
				}
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
			ERR_201();
			Adverb_node(tkn);
			return FAILURE;
		}


	}
	else
	{
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
			adverb_value = str;
			token_generator.next_token();
			if (Verb_node(current_token))
			{

				if (symbol_table.count(adverb_value))
				{
					if (symbol_table[adverb_value].sub_type != TOKEN_SUB_TYPE::Adverb)
					{//if lexeme exists check for semantic error
						ERR_302();
					}
				}
				else
				{
					(*tkn).sub_type = TOKEN_SUB_TYPE::Adverb;
					symbol_table[adverb_value] = *tkn;
				}
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
			if (Adjective2_node(current_token))
			{
				if (!symbol_table.count(verb_value))
				{
					symbol_table[verb_value] = *tkn;
				}
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
			ERR_202();
			Adjective2_node(tkn);
			return FAILURE;
		}
	}


	else
	{
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
		if ((*tkn).type == TOKEN_TYPE::Adword)
		{
			adjective2_value = str;
			token_generator.next_token();
			std::optional<Token> temp_token = current_token;
			if (Object_node(current_token))
			{
				if (symbol_table.count(adjective2_value))
				{
					if (symbol_table[adjective2_value].sub_type != TOKEN_SUB_TYPE::Adjective)
					{//if lexeme exists check for semantic error
						ERR_302();
					}
				}
				else
				{
					(*tkn).sub_type = TOKEN_SUB_TYPE::Adjective;
					symbol_table[adjective2_value] = *tkn;
				}
				return SUCCESS;
			}
			else
			{
				ERR_201();
				Punctuation_node(temp_token);
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
			object_value = str;
			token_generator.next_token();
			if (Punctuation_node(current_token))
			{
				if (symbol_table.count(object_value))
				{
					if (symbol_table[object_value].sub_type != TOKEN_SUB_TYPE::Object)
					{//if lexeme exists check for semantic error
						ERR_301();
					}
				}
				else
				{
					(*tkn).sub_type = TOKEN_SUB_TYPE::Object;
					symbol_table[object_value] = *tkn;
				}
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
		ERR_102();
		token_generator.next_token();
		Punctuation_node(current_token);
		return FAILURE;
	}

}
bool Punctuation_node(std::optional<Token> tkn)
{
	if (tkn.has_value())
	{
		if ((*tkn).type == TOKEN_TYPE::Eof)
		{
			EOF_REACHED = 2;
			return FAILURE;
		}
		if ((*tkn).type != TOKEN_TYPE::Punc)
		{
			ERR_203();
			return FAILURE;
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











