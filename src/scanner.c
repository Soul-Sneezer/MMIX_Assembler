#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "scanner.h"
#include "common.h"
#include "trie.h"

char* getString(char* buffer, int length, int buf_index)
{
	if(length <= 1)
		return NULL;
	
	int i = 0;
	char* new_string = (char*)malloc(length * sizeof(char));
	new_string[length - 1] = '\0';
	for(; (i + 1 - length) != 0; i++)
	{
		new_string[i]	= buffer[buf_index - length + 1 + i];	
	}

	return new_string;
}

void toLowercase(char** string)
{
	for(int i = 0; i < (*string)[i] != '\0'; i++)
	{
		if((*string)[i] >= 'A' && (*string)[i] <= 'Z')
			(*string)[i] += 32;
	}
}

char** importInstructions(const char* path, int* size)
{
	char** strings = (char**)malloc(256 * sizeof(char*));

	char* buffer = readFile(path);
	int length = 0;
	int index = 0;
	int buf_index = 0;
	while(buffer[buf_index] != '\0')
	{
		if(buffer[buf_index] == ' ' || buffer[buf_index] == ';' || buffer[buf_index] == '\t' || buffer[buf_index] == '\n')
		{
			if(index == 0)
				length++;
			char* new_string = getString(buffer, length, buf_index);
			if(new_string != NULL)
			{
				strings[index++] = new_string;
			}
			length = 0;
		}
		buf_index++;
		length++;
	}
	*size = index;

	return strings;
}

static bool isAtEnd(Scanner* scanner)
{
	return *scanner->current == '\0';
}

static Token makeToken(Scanner* scanner, TokenType type)
{
	Token token;
	token.start = scanner->start;
	token.line = scanner->line;
	token.length = (int)(scanner->current - scanner->start);
	token.type = type;

	return token;
}

static Token errorToken(Scanner* scanner, char* message)
{
	Token token;
	token.start = message;
	token.line = scanner->line;
	token.length = strlen(message);
	token.type = TOKEN_ERR;

	return token;
}

static char advance(Scanner* scanner)
{
	scanner->current++;
	return scanner->current[-1];
}

static char peek(Scanner* scanner)
{
	return *scanner->current;
}

static char peekNext(Scanner* scanner)
{
	if(*scanner->current == '\0') return '\0';

	return scanner->current[1];
}

static void skipWhitespace(Scanner* scanner)
{
	for(;;)
	{
		char c = peek(scanner);

		switch(c)
		{
			case ' ':
			case '\t':
			case '\r':
				advance(scanner);
				break;
			case '\n':
				scanner->line++;
				advance(scanner);
				break;
			case ';': 
			{
				while(!isAtEnd(scanner) && peek(scanner) != '\n')
				{
					advance(scanner);
				}
			break;
			}
			default:
				return;
		}
	}
}

static bool isNumeric(Scanner* scanner)
{
	char c = peek(scanner);
	return (c >= '0' && c <= '9');
}

static bool isAlphanumeric(Scanner* scanner)
{
		char c = peek(scanner);
		return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

static TokenType identifierType(Scanner* scanner)
{
	int length = scanner->current - scanner->start;
	char* word = (char*)malloc(length * sizeof(char));
	for(int i = 0; i < length; i++)
	{
		word[i] = *(scanner->start + i);
	}
	toLowercase(&word);
	if(findWord(scanner->trie, word))
		return TOKEN_INSTRUCTION;

	return TOKEN_LABEL;
}

Scanner* initScanner(char* source)
{
	Scanner* scanner = (Scanner*)malloc(sizeof(Scanner));
	scanner->start = source;
	scanner->current = source;
	scanner->line = 1;

	int size;
	char** words = importInstructions("instructions.txt", &size);
	scanner->trie = getNode();
	for(int i = 0; i < size; i++)
	{
		toLowercase(&words[i]);
	}
	createTrie(scanner->trie, words, size);

	return scanner;
}

static Token identifier(Scanner* scanner)
{
	bool immediate = true;
	
	
	while(!isAtEnd(scanner) && isAlphanumeric(scanner))
	{
		if(isAlphanumeric(scanner) && !isNumeric(scanner))
		{
			immediate = false;
		}
		advance(scanner);
	}

	if(immediate)
		return makeToken(scanner, TOKEN_IMMEDIATE);

	return makeToken(scanner, identifierType(scanner));
}

static Token generalRegister(Scanner* scanner)
{
	advance(scanner);
	while(isAlphanumeric(scanner))
	{
		advance(scanner);
	}

	return makeToken(scanner, TOKEN_GENERAL_REGISTER);
}

static Token specialRegister(Scanner* scanner)
{
	advance(scanner);
	while(isAlphanumeric(scanner))
	{
		advance(scanner);
	}

	return makeToken(scanner, TOKEN_SPECIAL_REGISTER);
}

static Token location(Scanner* scanner)
{
	advance(scanner);
	while(isAlphanumeric(scanner))
	{
		advance(scanner);
	}

	return makeToken(scanner, TOKEN_CONSTANT);
}

Token scanToken(Scanner* scanner)
{
	skipWhitespace(scanner);
	scanner->start = scanner->current;

	if(isAlphanumeric(scanner))
	{
		return identifier(scanner);
		}

	if (isAtEnd(scanner))
		return makeToken(scanner, TOKEN_EOF);

	char c = advance(scanner);

	switch(c)
	{
		case ',': return makeToken(scanner, TOKEN_COMMA);
		case '$': return generalRegister(scanner);
		case 'r': return specialRegister(scanner);
		case '#': return constant(scanner);
		case '+': return makeToken(scanner, TOKEN_ADD);
		case '-': return makeToken(scanner, TOKEN_SUB);
		case '*': return makeToken(scanner, TOKEN_MUL);
		case '/': return makeToken(scanner, TOKEN_DIV);
		case '@': return makeToken(scanner, TOKEN_AROUND);
		case '"':
		{
			advance(scanner);
			while(peek(scanner) != '"' && !isAtEnd(scanner))
			{
				if(isAtEnd(scanner) || peek(scanner) == '\n')
					return errorToken(scanner, "Unterminated string.");
				advance(scanner);
			}

			advance(scanner);

			Token token;
			token.start = scanner->start + 1;
			token.length = scanner->current - scanner->start - 2;
			token.type = TOKEN_STRING;
			token.line = scanner->line;

			return token;
		}
	}
	return errorToken(scanner, "Unexpected character.");
}

void freeScanner(Scanner* scanner)
{

}
