ENCRYPT = des_encrypt
DECRYPT = des_decrypt

CC = gcc
CFLAGS = -g
WARNING = -Wall -Wpointer-arith -Wno-unused-parameter -Wunused-function \
	-Wunused-variable -Wunused-value -Werror

CORE = des.o
OBJ1 = des_encrypt.o 
OBJ2 = des_decrypt.o

.PHONY: all
all: $(DECRYPT) $(ENCRYPT)

$(ENCRYPT) : $(CORE) $(OBJ1)
	$(CC) -o $@ $^

$(DECRYPT) : $(CORE) $(OBJ2)
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -c $(CFLAGS) $(WARNING) $< -o $@

clean:
	rm -rf $(ENCRYPT) $(DECRYPT) $(CORE) $(OBJ1) $(OBJ2) 

