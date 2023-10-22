#pragma once
#include<string>
#include <unordered_map>
#include "lexer.h"


using opt_tkn = std::optional<Token>;
constexpr bool SUCCESS=1;
constexpr bool FAILURE=0;
inline int EOF_REACHED;
inline std::unordered_map<std::string, Token> symbol_table;
inline Tokenizer token_generator("");

bool Adjective1_node(opt_tkn tkn);
bool Subject_node(opt_tkn tkn);
bool Adverb_node(opt_tkn tkn);
bool Verb_node(opt_tkn tkn);
bool Adjective2_node(opt_tkn tkn);
bool Object_node(opt_tkn tkn);
bool Punctuation_node(opt_tkn tkn);


