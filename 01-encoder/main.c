#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#define def_mnemonic_size 16

enum opc_type_t
{
	move  = 0,
	arith = 1,
	io    = 3,
};

enum opcode_t
{
	movi = 0x0,
	add  = 0x8,
	sub  = 0x9,
	divv = 0xA,
	mul  = 0xB,
	out  = 0x31,
	in   = 0x30
};

enum reg_t
{
	a = 0x0,
	b = 0x1,
	c = 0x2,
	d = 0x3,
};

union operand_t
{
	enum reg_t r;
	int imm;
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
	enum opc_type_t oct;
	enum opcode_t oc;
	union operands_t os;
};

void to_lower (char* src, size_t size)
{
	assert(src != NULL && "ERROR");

	for (size_t i = 0; i < size; i++)
	{
		src[i] = tolower(src[i]);
	}
}

struct instruction_t parse_movi ()
{
	struct instruction_t inst;
	int imm;

	if (!scanf("%u", &imm))
	{
		fprintf(stdout, "ERROR");
		exit(EXIT_SUCCESS);
	}

	inst.oct = move;
	inst.oc = movi;
	inst.os.imm = imm;

	return inst;
}

enum reg_t parse_reg ()
{
	enum reg_t res;
	char reg[2];

	if (!scanf("%s", reg))
	{
		fprintf(stdout, "ERROR");
		exit(EXIT_SUCCESS);
	}

	reg[0] = tolower (reg[0]);

	switch (reg[0])
	{
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		{
			res = reg[0] - 'a';
		} break;
		default:
		{
			fprintf(stdout, "ERROR");
			exit(EXIT_SUCCESS);
		} break;
	}
	return res;
}

struct instruction_t parse_arith (enum opcode_t oc)
{
	struct instruction_t inst;

	inst.oc = oc;
	inst.oct = arith;
	inst.os.regs.rx = parse_reg ();
	inst.os.regs.rs = parse_reg ();

	return inst;
}

struct instruction_t parse_io (enum opcode_t oc)
{
	struct instruction_t inst;

	inst.os.reg = parse_reg();
	inst.oc = oc;
	inst.oct = io;

	return inst;
}


int encode (struct instruction_t inst)
{
	int res = 0;

	switch (inst.oct)
	{
		case move:
		{
			res |= (inst.oc << 8) | (inst.os.imm & 0x7f);
		} break;
		case io:
		{
			res |= (inst.oc << 2) | (inst.os.reg & 0x03);
		} break;
		case arith:
		{
			res |= (inst.oc << 4) | (inst.os.regs.rx << 2) | (inst.os.regs.rs);
		} break;
		default:
		{
			fprintf(stdout, "ERROR: Wrong instruction.\n");
			exit(EXIT_SUCCESS);
		} break;
	}

	return res;
}

int main (int argc, char** argv)
{
	char mnemonic[def_mnemonic_size];
	int instruction;
	while(scanf("%15s\n", mnemonic) > 0)
	{
		to_lower(mnemonic, def_mnemonic_size);
		if(strcmp("movi", mnemonic) == 0)
		{
			instruction = encode(parse_movi());
		}
		else if(strcmp("out", mnemonic) == 0)
		{
			instruction = encode(parse_io(out));
		}
		else if(strcmp("in", mnemonic) == 0)
		{
			instruction = encode(parse_io(in));
		}
		else if(strcmp("add", mnemonic) == 0)
		{
			instruction = encode(parse_arith(add));
		}
		else if(strcmp("sub", mnemonic) == 0)
		{
			instruction = encode(parse_arith(sub));
		}
		else if(strcmp("div", mnemonic) == 0)
		{
			instruction = encode(parse_arith(divv));
		}
		else if(strcmp("mul", mnemonic) == 0)
		{
			instruction = encode(parse_arith(mul));
		}
		else
		{
			fprintf(stdout, "ERROR:");
			exit(EXIT_SUCCESS);
		}
		printf("0x%02x ", instruction);
		fflush(stdout);
	}
	return EXIT_SUCCESS;
}

