test:=test
test_files:= $(wildcard ${test}/*.pasm)
target:=encoder

${target}: main.c
	clang main.c -o ${target}

@phony: test clean

run_test: ${target}
	@for test_file in $(test_files); do \
		echo "Running test: $$test_file"; \
		cat "$$test_file"; \
		./${target} < "$$test_file"; \
		echo ""; \
	done

test: run_test

clean:
	rm encoder

