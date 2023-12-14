typedef struct
{
	char* start;
	char* current;
	int line;
} Scanner;

typedef enum
{
	// Instructions
/* 0x */	TOKEN_TRAP, TOKEN_FCMP, TOKEN_FUN, TOKEN_FEQL, TOKEN_FADD, TOKEN_FIX, TOKEN_FSUB, TOKEN_FIXU,
/* 0x */ 	TOKEN_FLOT, TOKEN_FLOTI, TOKEN_FLOTU, TOKEN_FOLTUI, TOKEN_SFLOT, TOKEN_SFLOTI, TOKEN_SFLOTU, TOKEN_SFLOTUI,
/* 1x */	TOKEN_FMUL, TOKEN_FCMPE, TOKEN_FUNE, TOKEN_FEQLE, TOKEN_FDIV, TOKEN_FSQRT, TOKEN_FREM, TOKEN_FINT,
/* 1x */ 	TOKEN_MUL, TOKEN_MULI, TOKEN_MULU, TOKEN_MULUI, TOKEN_DIV, TOKEN_DIVI, TOKEN_DIVU, TOKEN_DIVUI,
/* 2x */	TOKEN_ADD, TOKEN_ADDI, TOKEN_ADDU, TOKEN_ADDUI, TOKEN_SUB, TOKEN_SUBI, TOKEN_SUBU, TOKEN_SUBUI,
/* 2x */  TOKEN_2ADDU, TOKEN_2ADDUI, TOKEN_4ADDU, TOKEN_4ADDUI, TOKEN_8ADDU, TOKEN_8ADDUI, TOKEN_16ADDU, TOKEN_16ADDUI,
/* 3x */  TOKEN_CMP, TOKEN_CMPI, TOKEN_CMPU, TOKEN_CMPUI, TOKEN_NEG, TOKEN_NEGI, TOKEN_NEGU, TOKEN_NEGUI,
/* 3x */  TOKEN_SL, TOKEN_SLI, TOKEN_SLU, TOKEN_SLUI, TOKEN_SR, TOKEN_SRI, TOKEN_SRU, TOKEN_SRUI,
/* 4x */  TOKEN_BN, TOKEN_BNB, TOKEN_BZ, TOKEN_BZB, TOKEN_BP, TOKEN_BPB, BOKEN_BOD, TOKEN_BODB,
/* 4x */  TOKEN_BNN, TOKEN_BNNB, TOKEN_BNZ, TOKEN_BNZB, TOKEN_BNP, TOKEN_BNPB, TOKEN_BEV, TOKEN_BEVB,
/* 5x */  TOKEN_PBN, TOKEN_PBNB, TOKEN_PBZ, TOKEN_PBZB, TOKEN_PBP, TOKEN_PBPB, TOKEN_BPOD, TOKEN_PBODB,
/* 5x */  TOKEN_PBNN, TOKEN_PBNNB, TOKEN_PBNZ, TOKEN_PBNZB, TOKEN_PBNP, TOKEN_PBNPB, TOKEN_PBEV, TOKEN_PBEVB,
/* 6x */  TOKEN_CSN, TOKEN_CSNI, TOKEN_CSZ, TOKEN_CSZI, TOKEN_CSP, TOKEN_CSPI, TOKEN_CSOD, TOKEN_CSODI,
/* 6x */  TOKEN_CSNN, TOKEN_CSNNI, TOKEN_CSNZ, TOKEN_CSNZI, TOKEN_CSNP, TOKEN_CSNPI, TOKEN_CSEV, TOKEN_CSEVI,
/* 7x */
	
} TokenType;

typedef struct
{
	TokenType type;
	char* source;
	int length;
	int line;
} Token;

void initScanner(char* source);
