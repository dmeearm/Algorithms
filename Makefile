CC := gcc 
obj := main.o list.o string.o bintree.o search.o rbtree.o sort.o
target := test
warn := -Wall

$(target) : $(obj)
	$(CC) $(warn) -o $@  $^

%.o : %.c
	$(CC) -g -c $< -o $@

clean:
	rm -rf $(target) $(obj)
