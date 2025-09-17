common:=test
movi:=test_movi
io:=test_io
arith:=test_arith
common_test_files:= $(wildcard ${common}/*.pasm)
movi_test_files:= $(wildcard ${common}/${movi}/*.pasm)
io_test_files:= $(wildcard ${common}/${io}/*.pasm)
arith_test_files:= $(wildcard ${common}/${arith}/*.pasm)
target:=encoder

${target}: main.c
	clang main.c -o ${target}

@phony: test clean

run_test: ${target}
	@for test_file in $(common_test_files); do \
		echo "Running test: $$test_file"; \
		cat "$$test_file"; \
		./${target} < "$$test_file"; \
		echo ""; \
	done

test_movi: ${target}
	@for test_file in $(movi_test_files); do \
		echo "Running test: $$test_file"; \
		cat "$$test_file"; \
		./${target} < "$$test_file"; \
		echo ""; \
	done

test_io: ${target}
	@for test_file in $(io_test_files); do \
		echo "Running test: $$test_file"; \
		cat "$$test_file"; \
		./${target} < "$$test_file"; \
		echo ""; \
	done

test_arith: ${target}
	@for test_file in $(arith_test_files); do \
		echo "Running test: $$test_file"; \
		cat "$$test_file"; \
		./${target} < "$$test_file"; \
		echo ""; \
	done

test: run_test

clean:
	rm encoder

