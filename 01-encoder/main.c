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
	mul  = 0xA,
	divv = 0xB,
	out  = 0x31,
	in   = 0x30
};

enum reg_t {
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

void reach_end()
{
	int c;
	while ((c = fgetc (stdin)) != EOF)
	{
		if (c == ' ')
		{
			continue;
		}
		else if (c == '\n')
		{
			break;
		}
		else
		{
			fprintf(stdout, "ERROR");
			exit(EXIT_SUCCESS);
		}
	}
}

void parse_punctuation ()
{
	char c;

	if (!scanf (" %c ", &c) || c != ',')
	{
		fprintf(stdout, "ERROR");
		exit(EXIT_SUCCESS);
	}
}

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
	int imm = -1;

	if (!scanf(" %u", &imm))
	{
		fprintf(stdout, "ERROR");
		exit(EXIT_SUCCESS);
	}

	if ( 0 > imm || imm > 0x7f)
	{
		fprintf(stdout, "ERROR");
		exit(EXIT_SUCCESS);
	}

	reach_end();

	inst.oct = move;
	inst.oc = movi;
	inst.os.imm = imm;

	return inst;
}

enum reg_t parse_reg ()
{
	enum reg_t res;
	char reg;

	if (!scanf("%c", &reg))
	{
		fprintf(stdout, "ERROR");
		exit(EXIT_SUCCESS);
	}

	reg = tolower (reg);

	switch (reg)
	{
		case 'a': return a;
		case 'b': return b;
		case 'c': return c;
		case 'd': return d;
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
	parse_punctuation ();
	inst.os.regs.rs = parse_reg ();
	reach_end();

	return inst;
}

struct instruction_t parse_io (enum opcode_t oc)
{
	struct instruction_t inst;

	inst.os.reg = parse_reg();
	inst.oc = oc;
	inst.oct = io;

	reach_end();

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
			fprintf(stdout, "ERROR");
			exit(EXIT_SUCCESS);
		} break;
	}

	return res;
}

int main (int argc, char** argv)
{
	char mnemonic[def_mnemonic_size];
	int instruction;
	while(scanf(" %15s\n", mnemonic) > 0)
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
			fprintf(stdout, "ERROR");
			exit(EXIT_SUCCESS);
		}
		printf("0x%02x ", instruction);
		fflush(stdout);
	}
	return EXIT_SUCCESS;
}

