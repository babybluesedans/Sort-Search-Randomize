sorter:
	clang -c -o algos.o algos.c
	clang -c -o sorter.o sorter.c
	clang -o sorter algos.o sorter.o