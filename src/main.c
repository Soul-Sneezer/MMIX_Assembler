#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "parser.h"
#include "vm.h"
#include "common.h"
#include "debug.h"

typedef enum
{
	OK,
	COMPILE_ERROR,
	RUNTIME_ERROR,
} ErrorType;

ErrorType runFile(const char* source)
{
	//parse();
	//execute();
}

int32_t main(int32_t argc, const char* argv[])
{
	const char* flags;
	// possible options
	// -s (for running time statistics when the program ends)
	// -P (profile showing exactly how often each instruction was executed)
	// -v ("verbose" details about everything the simulator did)
	// -t2 (trace each instruction the first two times it is performed
	// -i (run simulator in interactive mode)
	const char* source;
	FILE* output_fd;
	
	VM* vm;
	
	if (argc == 2)
	{
		source = readFile(argv[1]);
	}
	else if (argc == 3)
	{
		if(argv[1][0] == '-')
		{
			flags = (char*)malloc(sizeof(argv[1]));
			strcpy(flags, ++argv[1]);
			source = readFile(argv[2]);
		}
		else
		{
			source = readFile(argv[1]);
			output_fd = createFile(argv[2]);
		}
	}	
	else if (argc == 4)
	{
		flags = (char*)malloc(sizeof(argv[1]));
		strcpy(flags, ++argv[1]);
		source = readFile(argv[2]);
		output_fd = createFile(argv[3]);
	}
	else
	{
		fprintf(stderr, "Usage: mmix [-options] [input file path] [output file path(default: out.mmix)]\n");
		exit(64);
	}

	initScanner(source);
	initParser();
	initVM(vm);

	freeVM(vm);
	freeParser();
	freeScanner();

	free(flags);
	return 0;
}
