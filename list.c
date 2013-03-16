#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "struct.h"

/*
 * todo:
 * 1. 链表排序
 * 2. 链表翻转(逆序)
 * 3. 链表的合并 
 */


/* 从文件file数据构造单链表 */ 
int list_create(const char *file, list_t **root)
{
	int     data;
	list_t *pl = NULL;
	list_t *plast = NULL;

    if (!file) {
    	return EPARAM1;
    } else if (!root) {
    	return EPARAM2;
    }
    
	if (freopen(file, "r", stdin) == NULL) {
		printf("%s\n", strerror(errno));
		return ESYSCALL;
	}

	while (scanf("%d", &data) != EOF) {
		pl = malloc(sizeof(list_t));
		if (!pl) {
            fclose(stdin);
			return ENOMEMORY;
		}
		
		pl->data = data;
		pl->next = NULL;
		
		if (*root == NULL) {
			*root = pl;
			plast = pl;
		} else {
			plast->next = pl;
			plast = pl;
		}
	}
    
	fclose(stdin);
	
	return OK;
}

/* 打印链表中的元素 */
int list_show(list_t *head)
{
	list_t *pl;
	
	if (!head) {
		return EPARAM1;
	}
	
	printf("show list elements:\n");
	
	pl = head;
	
	while (pl) {
		printf("%d", pl->data);
		if (pl->next) {
			printf(" ");
		}
		pl = pl->next;
	}
	
	printf("\n");
	
	return OK;
}


/* 直接插入排序法 */
void list_sort1(list_t **head, int flag)
{
	list_t *pcur;
	list_t *pnext;
	list_t *prev = NULL;
	list_t *walker;
	list_t  root;
	
	if (!head) {
	    return;
	}

	root.next = *head;
	root.data = -1;

    pcur = (*head)->next;
    prev = &root;
    (*head)->next = NULL;

    while (pcur) {
        
        pnext = pcur->next;
        
        for (walker = root.next; walker; walker = walker->next) {
            if (flag == UP && walker->data > pcur->data) {
                break;
            } else if (flag == DOWN && walker->data <= pcur->data) {
                break;
            }
            prev = walker;
        }
        
        pcur->next = walker;
        prev->next = pcur;
        
        pcur = pnext;
        prev = &root;
    }
	
    *head = root.next;
    
	return;
}

void list_reverse(list_t **head)
{
    list_t *ph;
    list_t *prev;
    list_t *pnext;
    list_t *pcur;

    if (!head) {
        return;
    }

    ph = *head;
    
    prev = ph;
    pcur = ph->next;
    ph->next = NULL;
    
    while (pcur) {
        pnext = pcur->next;
        pcur->next = prev;
        prev = pcur;
        pcur = pnext;
    }

    *head = prev;
}

/* 链表合并 */
list_t *list_merge(list_t *head1, list_t *head2)
{
    list_t *new_list = NULL;

    list_t *ph1;
    list_t *ph2;
    list_t *node;
    list_t *plast;
    int     data;

    list_sort1(&head1, UP);
    list_sort1(&head2, UP);

    ph1 = head1;
    ph2 = head2;

    while (ph1 || ph2) {
        
        if (ph1 && ph2) {     
            if (ph1->data == ph2->data) {
                data = ph1->data;
                ph1 = ph1->next;
                ph2 = ph2->next;
            } else if (ph1->data < ph2->data) {
                data = ph1->data;
                ph1 = ph1->next;
            } else {
                data = ph2->data;
                ph2 = ph2->next;
            }
        } else if (ph1) {
            data = ph1->data;
            ph1 = ph1->next;
        } else {
            data = ph2->data;
            ph2 = ph2->next;
        }
        
        node = malloc(sizeof(list_t));
        if (!node) {
            new_list = NULL;
            break;
        }

        node->data = data;
        node->next = NULL;
        
        if (new_list == NULL) {
            new_list = node;
            plast = node;
        } else {
            plast->next = node;
            plast = node;
        }
        
    }

    return new_list;
    
}
