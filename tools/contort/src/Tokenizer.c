//
// Created by rombus on 8/15/21.
//

#include "Tokenizer.h"

#include <stdbool.h>

// Simple matchers
bool
Token_IsWhitespace(const char c) {
    return c == '\n' || c == '\t' || c == ' ' || c == '\r';
}

bool
Token_IsEOL(const char c) {
    return c == '\n';
}

bool
Token_IsAlpha(const char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool
Token_IsNumber(const char c) {
    return (c >= '0' && c <= '9');
}

// This skips whitespace and comments
static void
skipUnusedTokens(Tokenizer *tokenizer) {
    for (;;) {
        if (Token_IsWhitespace(tokenizer->position[0])) {
            tokenizer->position++;
        } else if (tokenizer->position[0] == '/' && tokenizer->position[1] == '/') {
            tokenizer->position += 2;
            while (tokenizer->position[0] && !Token_IsEOL(tokenizer->position[0]))
                tokenizer->position[0]++;
        } else if (tokenizer->position[0] == '/' && tokenizer->position[1] == '*') {
            tokenizer->position += 2;
            while (tokenizer->position[0] && tokenizer->position[1] && !(tokenizer->position[0] != '*' &&
                                                                         tokenizer->position[1] != '/')) {
                tokenizer->position[0]++;
            }
            if (tokenizer->position[0] == '*')
                tokenizer->position += 2;
        } else {
            break;
        }
    }

}

Token
Tokenizer_GetToken(Tokenizer *tokenizer) {
    skipUnusedTokens(tokenizer);

    // Default token state
    Token token = {};
    token.length = 1;
    token.text = tokenizer->position;

    switch (tokenizer->position[0]) {
        // End of file
        case '\0':
            token.type = TOKEN_EOF;
            break;

            // Symbols
        case '(':
            token.type = TOKEN_LEFT_PAREN;
            tokenizer->position++;
            break;
        case ')':
            token.type = TOKEN_RIGHT_PAREN;
            tokenizer->position++;
            break;
        case '{':
            token.type = TOKEN_LEFT_CURLY;
            tokenizer->position++;
            break;
        case '}':
            token.type = TOKEN_RIGHT_CURLY;
            tokenizer->position++;
            break;
        case '[':
            token.type = TOKEN_LEFT_BRACE;
            tokenizer->position++;
            break;
        case ']':
            token.type = TOKEN_RIGHT_BRACE;
            tokenizer->position++;
            break;
        case ':':
            token.type = TOKEN_COLON;
            tokenizer->position++;
            break;
        case ';':
            token.type = TOKEN_SEMICOLON;
            tokenizer->position++;
            break;
        case '*':
            token.type = TOKEN_ASTERISK;
            tokenizer->position++;
            break;
        case '=':
            token.type = TOKEN_EQUALS;
            tokenizer->position++;
            break;

        // Strings
        case '"':
            tokenizer->position++;
            token.type = TOKEN_STRING;
            // Start of our string
            token.text = tokenizer->position;
            while (tokenizer->position[0] != '"') {
                // Skip two chars if there's a slash
                if (tokenizer->position[0] == '\\' && tokenizer->position[1]) {
                    tokenizer->position++;
                }
                tokenizer->position++;
            }

            // Get the length of the string
            token.length = (int) (tokenizer->position - token.text);

            // Skip the end quote
            if (tokenizer->position[0] == '"')
                tokenizer->position++;

            break;

        default:
            // Identifiers
            if (Token_IsAlpha(tokenizer->position[0])) {
                token.type = TOKEN_IDENTIFIER;
                token.text = tokenizer->position;

                while (
                        Token_IsAlpha(tokenizer->position[0]) ||
                        Token_IsNumber(tokenizer->position[0]) ||
                        tokenizer->position[0] == '_' ||
                        tokenizer->position[0] == '.') {
                    tokenizer->position++;
                }

                // End of the identifier
                token.length = (int) (tokenizer->position - token.text);

            // Numbers
            } else if (Token_IsNumber(tokenizer->position[0])) {
                token.type = TOKEN_NUMBER;
                token.text = tokenizer->position;

                while (
                        Token_IsNumber(tokenizer->position[0]) ||
                        tokenizer->position[0] == '.' || (Token_IsAlpha(tokenizer->position[0]) && !Token_IsNumber(
                                tokenizer->position[1]))) { // Edge case for typed numbers
                    tokenizer->position++;
                }

                // End of the Number
                token.length = (int) (tokenizer->position - token.text);
            } else {
                token.type = TOKEN_UNKNOWN;
                tokenizer->position++;
            }
            break;
    }

    return token;
}