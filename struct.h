#ifndef _LIST_H_
#define _LIST_H_

#define  OK            0
#define  ENOMEMORY    -1  // no memory to alloc or malloc.
#define  ERROR        -2
#define  ESYSCALL     -3  // syscall or glibc function return a error.

/*
 * DOWN means increase order, and UP means decrease order
 */
#define  UP            1 
#define  DOWN          2 

#define  uchar_t       unsigned char
#define  MAX_SIZE      100

/*
 * the left and right subtree done, it's time to do father node.
 * otherwise, should not to do father. DONE means "done", TODO means "not done"
 */
#define  DONE          1  
#define  TODO          0  

enum {
	EPARAM1 = -5,  // the first parameter is invalid
	EPARAM2 = -6,  // second parameter ...
	EPARAM3 = -7,  // the third ...
	EPARAM4 = -8,  
	EPARAM5 = -9
};

typedef struct list_s {
	int            data;
	struct list_s *next;
} list_t;

typedef struct string_s{
    char       *data;
    int         len;
} str_t;

typedef struct bintree_s bintree_t;

struct bintree_s {
    int          data;
    bintree_t   *left;
    bintree_t   *right;
};

typedef struct tnode_s {
    bintree_t     *tree;
    uchar_t        l:1;  // left subtree is done
    uchar_t        r:1;  // right subtree is done
} tnode_t;

int list_create(const char *file, list_t **head);
int list_show(list_t *head);
void list_sort1(list_t **head, int flag);
void list_reverse(list_t **head);
list_t *list_merge(list_t *head1, list_t *head2);


#endif
