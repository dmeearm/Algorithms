#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "struct.h"

bintree_t *bintree_search(bintree_t *root, int key)
{
    if (!root) {
        return NULL;
    }

    if (root->data == key) {
        return root;
    } else if (root->data > key) {
        return bintree_search(root->left, key);
    } else {
        return bintree_search(root->right, key);
    }
    
}

/* find the minsize node of the right subtree */
static bintree_t  *bintree_successor(bintree_t **root)
{
    bintree_t  *node = NULL;

    /* currect node is empty(actually it's a right subtree) */
    node = *root;
    if (!node) {
        return NULL;
    }

    /* the node have not left subtree */
    if (!node->left) {
        *root = node->right;
        return node;
    }

    return bintree_successor(&node->left);    
}

int bintree_delete(bintree_t **root, int key)
{
    bintree_t *node = NULL;
    bintree_t *successor = NULL;
    
    if (!root || !*root) {
        return ERROR;
    }

    node = *root;
    
    if (node->data == key) {
        successor = bintree_successor(&node->right);
        if (successor == NULL) {
            *root = node->left;
        } else {
            node->data = successor->data;
            node = successor;
        }
        
        free(node);
    } else if (node->data > key) {
        return bintree_delete(&node->left, key);
    } else {
        return bintree_delete(&node->right, key);
    }

    return OK;
}

void bintree_insert(bintree_t *root, bintree_t *node)
{    
    if (root == NULL) {
        return;
    }
    
    if (root->data == node->data) {
        return;
    }

    if (root->data > node->data) {
        if (root->left == NULL) {
            root->left = node;
        }  else {
            bintree_insert(root->left, node);
        }
    } else {
        if (root->right == NULL) {
            root->right = node;
        } else {
            bintree_insert(root->right, node);
        }
    }
    
    return;
}

/* recursive algorithm for preorder, inorder and postorder search. */
void bintree_preorder(bintree_t *root)
{
    if (root == NULL) {
        return;
    }
    
    printf("%d ", root->data);
    bintree_preorder(root->left);
    bintree_preorder(root->right);
}

void bintree_inorder(bintree_t *root)
{
    if (root == NULL) {
        return;
    }
    
    bintree_inorder(root->left);
    printf("%d ", root->data);
    bintree_inorder(root->right);
}

void bintree_postorder(bintree_t *root)
{
    if (root == NULL) {
        return;
    }
    
    bintree_postorder(root->left);
    bintree_postorder(root->right);
    printf("%d ", root->data);
}


/* no-recursive algorithm for tree type search */
void preorder(bintree_t *root)
{
    tnode_t      stack[MAX_SIZE];
    int          top = -1;
    tnode_t     *node;
    bintree_t   *tree;

    top++;
    
    if (root != NULL) {
        
        stack[top].tree = root;

        while (top > -1) {
            
            node = &stack[top];
            
            printf("%d ", node->tree->data);
            
            top--;

            tree = node->tree;
            if (!tree) {
                return;
            }
            
            if (tree->right) {
                top++;
                stack[top].tree = tree->right;
            }

            if (tree->left) {
                top++;
                stack[top].tree = tree->left;
            }
        }

        printf("\n");
    }
}

void inorder(bintree_t *root)
{
    tnode_t        stack[MAX_SIZE];
    int            top = -1;
    bintree_t     *node;

    if (!root) {
        return;
    }

    node = root;
    
    while (top > -1 || node != NULL) {
        
        while (node) {
            top++;
            stack[top].tree = node;
            node = node->left;
        }

        if (top > -1) {
            node = stack[top].tree;
            top--;
            printf("%d ", node->data);
            node = node->right;
        }
    }

    printf("\n");

    return;
}

void postorder(bintree_t *root)
{
    bintree_t *node;
    tnode_t   *one;
    tnode_t    stack[MAX_SIZE];
    int        top = -1;

    if (!root) {
        return;
    }
    
    node = root;
    
    while (top > -1 || node) {

        while (node) {
            top++;
            stack[top].tree = node;
            stack[top].l = stack[top].r = TODO;
            node = node->left;
        }

        if (top > -1) {
            one = &stack[top];
            if (one->r == 1 && one->l == 1) {
                printf("%d ", one->tree->data);
                top--;
                continue;
            }
            one->l = DONE;
            one->r = DONE;
            node = one->tree->right;   
        }
    }

    printf("\n");

    return;
}

int bintree_create(const char *file, bintree_t **root)
{
    int         in;
    bintree_t  *node;

    if (!root) {
        return EPARAM2;
    }
    
    if (freopen(file, "r", stdin) == NULL) {
        printf("%d\n", strerror(errno));
        return ESYSCALL;
    }

    while (scanf("%d", &in) != EOF) {
        node = malloc(sizeof(bintree_t));
        if (!node) {
            fclose(stdin);
            return ENOMEMORY;
        }

        node->data = in;
        node->left = node->right = NULL;
        
        if (*root == NULL) {
            *root = node;
            continue;
        }

        bintree_insert(*root, node);
    }

    fclose(stdin);
    
    return OK;
}



