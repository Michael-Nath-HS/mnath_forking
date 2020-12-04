fork.out: main.c
	gcc -o fork.out main.c
run: fork.out
	./fork.out
clean: 
	rm *.out