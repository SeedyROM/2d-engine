//
// Created by rombus on 8/15/21.
//

#pragma once

#include <stdbool.h>

typedef enum {
    TOKEN_UNKNOWN,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_NUMBER,

    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_CURLY,
    TOKEN_RIGHT_CURLY,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    TOKEN_ASTERISK,
    TOKEN_EQUALS,
    TOKEN_EOF
} TokenType;

typedef struct Token {
    int length;
    char *text;
    TokenType type;
} Token;

static inline bool
Token_IsWhitespace(char c);

static inline bool
Token_IsEOL(char c);

static inline bool
Token_IsAlpha(char c);

static inline bool
Token_IsNumber(char c);

typedef struct Tokenizer {
    char *position;
} Tokenizer;

Token
Tokenizer_GetToken(Tokenizer *);

