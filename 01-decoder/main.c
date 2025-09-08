#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

enum opcode_t
{
	movii = 0x0,
};

enum reg_t
{
	a = 0x0,
	b = 0x1,
	c = 0x2,
	d = 0x3,
};

union operands_t
{
	enum reg_t reg;
	struct
	{
		enum reg_t rs;
		enum reg_t rx;
	} regs;
	int imm;
};

struct instruction_t
{
	enum opcode_t oc;
};

void to_lower (char* src, size_t size)
{
	assert(src != NULL && "ERROR: String must be non NULL value\n");

	for (size_t i = 0; i < size; i++)
	{
		src[i] = tolower(src[i]);
	}
}

#define def_mnemonic_size 16

int main (int argc, char** argv)
{
	char mnemonic[def_mnemonic_size];
	int instruction;
	while(scanf("%15s\n", mnemonic) > 0)
	{
		to_lower(mnemonic, def_mnemonic_size);
		printf("%s ", mnemonic);
		if(strcmp("movi", mnemonic) == 0)
		{
			// parse
		}
		else
		{
			fprintf(stderr, "ERROR: Unknown mnemonic <%s>\n", mnemonic);
			return 69;
		}
	}
	printf("\n");
	return 0;
}

