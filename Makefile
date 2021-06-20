EXT = *.enc *.dec

all: clean encrypt decrypt

encrypt: 
	gcc -pthread encrypt.c -o encrypt 

decrypt:
	gcc -pthread decrypt.c -o decrypt

%.o: %.c
	gcc -g -Wall -c $< -o $@

util: file_util.o 
	gcc -g -Wall file_util.o -o file_util

clean:
	for i in $(EXT); do find . -name "$$i" -delete; done
	rm -f encrypt decrypt 
