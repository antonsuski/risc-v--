test:=test
target:=encoder

${target}: main.c
	clang main.c -o ${target}

@phony: test run_test clean

run_test: encoder
	./encoder < ${test}/test0.pasm
	./encoder < ${test}/test1.pasm
	./encoder < ${test}/test2.pasm
	./encoder < ${test}/test3.pasm
	./encoder < ${test}/test4.pasm
	./encoder < ${test}/test5.pasm

test: run_test

clean:
	rm encoder

