#ifndef mmix_proj_scanner
#define mmix_proj_scanner

typedef struct
{
	char* start;
	char* current;
	int line;
} Scanner;

typedef enum
{
	TOKEN_INSTRUCTION, TOKEN_GENERAL_REGISTER, TOKEN_SPECIAL_REGISTER, TOKEN_IMMEDIATE, TOKEN_LABEL, TOKEN_COMMA, TOKEN_LOCATION, TOKEN_STRING,TOKEN_ERR, TOKEN_EOF,
} TokenType;

typedef struct
{
	TokenType type;
	char* source;
	int length;
	int line;
} Token;

void initScanner(char* source);
Token scanToken();

#endif