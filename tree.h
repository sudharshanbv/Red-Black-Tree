

#ifndef TREE_H
#define TREE_H

typedef struct tree
{

int data;
struct tree *left;
struct tree *right;
int color;

}Bstree_t;

#define RED "\x1b[31m"
#define RESET "\x1b[0m"
void in_order(Bstree_t *root);
void rotate_right(Bstree_t **root, int data);
void rotate_left(Bstree_t **root, int data);

void check_balance(Bstree_t **root, int data, int level);

int find_level(Bstree_t *root, int data);

void bfs(Bstree_t *root, int level, int choice, int val);

Bstree_t *grandpa_search(Bstree_t *root, int level, int val);

Bstree_t *uncle_search(Bstree_t *gp_add, int val);

void bfs_fun(Bstree_t *root, int choice, int val);

int dfs_fun(Bstree_t *root,int height, int val);

int find_height(Bstree_t *root);

int count_node(Bstree_t *root, int *count);

Bstree_t *search_node(Bstree_t *root, int data);

int find_min(Bstree_t *root);

int find_max(Bstree_t *root);

void pre_order(Bstree_t *root);

void post_order(Bstree_t *root);

Bstree_t *insert_tree(Bstree_t *root, int data);

Bstree_t *create_tree(int data);

Bstree_t *delete_node(Bstree_t *root, int val);
#endif
