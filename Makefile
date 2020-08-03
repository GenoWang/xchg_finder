all:main.c
	gcc main.c -o xchg_finder
clean:
	rm -rf ./xchg_finder