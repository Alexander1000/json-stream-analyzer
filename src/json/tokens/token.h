#define TOKEN_TYPE_TEXT 0
#define TOKEN_TYPE_BRACES_OPEN 1
#define TOKEN_TYPE_BRACES_CLOSE 2
#define TOKEN_TYPE_COMMA 3
#define TOKEN_TYPE_QUOTES 4
#define TOKEN_TYPE_COLON 5
#define TOKEN_TYPE_ARRAY_OPEN 6
#define TOKEN_TYPE_ARRAY_CLOSE 7
#define TOKEN_TYPE_NUMERIC 8

#include "token.cpp"

#include "token_braces_open.cpp"
#include "token_braces_close.cpp"
#include "token_colon.cpp"
#include "token_comma.cpp"
#include "token_quotes.cpp"
#include "token_lexeme_word.cpp"
#include "token_array_open.cpp"
#include "token_array_close.cpp"
#include "token_numeric.cpp"
