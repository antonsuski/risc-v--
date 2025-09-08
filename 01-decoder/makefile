encoder: main.c
	clang main.c -o encoder

@phony: test run_test clean

run_test: encoder
	./encoder < test.pasm
	./encoder < test1.pasm

test: run_test

clean:
	rm encoder

