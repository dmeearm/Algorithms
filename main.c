#include <stdio.h>
#include "struct.h"

int main()
{
    // for bin tree
    /*
	int     rc = OK;

    bintree_t *root = NULL;
    bintree_t *node = NULL;

    bintree_create("tree.in", &root);

    inorder(root);
    node = bintree_search(root, 5);
    
    //if (node) {
    //    printf("search node successful, node:%p, key:%d\n", node, node->data);
    //}
    bintree_delete(&root, 5);
    bintree_delete(&root, 9);
    bintree_delete(&root, 0);
    
    bintree_inorder(root);
    //bintree_postorder(root);
    printf("\n");
    //postorder(root);
    */

    // for sort algorithms
    int s[16] = {6, 5, 1, 0, 4, 3, 9, 8, 7, 2, 18, 19, 12, 13, 10, 14};
    sort_print(s, 16);
    //sort_insert(s, 10);
    //sort_shell(s, 10);
    //sort_quick(s, 0, 9);
    //sort_select(s, 10);
    //sort_heap2(s, 16);
    sort_merge2(s, 0, 15);
    sort_print(s, 16);
    
	return 0;
}
