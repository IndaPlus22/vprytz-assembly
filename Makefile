GCC = gcc

all: compile

compile:
	$(GCC) -o main src/main.c

run_multiply:
	./main multiply.bbvv

run_test: compile run_multiply clean

clean:
	rm main
