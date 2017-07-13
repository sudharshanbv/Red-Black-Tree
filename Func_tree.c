
#include <stdio.h>
#include "tree.h"
#include <stdlib.h>


/*global variable declaration*/
int flag = 0;

/*------------------------------------------------------------------------------------------------------------------*/
/*dfs function block*/
int dfs_fun(Bstree_t *root, int height, int val)
{

	/*local variable declaration*/
	static int set_flag = 0;

	if (root)
	{
		if (root->left)
		{
			dfs_fun(root->left, height, val);
		}

		if (root->right)
		{
			dfs_fun(root->right, height, val);
		}

		if (flag == 0)
		{

			/*if the search value matches*/
			if (root->data == val)
			{

				/*calculate the level of the node*/
				int level = height - find_height(root);

				printf("\nValue found at level %d\n", level);

				flag = 1;

			}
		}
	}

	/*if the value not found*/
	if (flag = 0)
		printf("\n\t\tVALUE NOT FOUND\n\n");

	if (flag == 1)
		flag = 0;
}
/*------------------------------------------------------------------------------------------------------------------*/
/*bfs main function block*/
void bfs_fun(Bstree_t *root, int choice, int val)
{

	/*local variable declaration*/
	int idx, jdx;

	/*find the height of the tree*/
	int height = find_height(root);

	for (idx = 1; idx <= height; idx++)
	{

		/*print case, to print the pattern of tree*/
		if (choice == 1)
		{
			printf("\n");

			for (jdx = height + height / 2; jdx > idx; --jdx)
			{
				printf("\t");
			}
		}


		if (flag == 0)
			bfs(root, idx, choice, val);

	}

	if (flag == 0)
	{
		//printf("\nValue not found\n");
	}

	if (flag == 1)
		flag = 0;
}
/*------------------------------------------------------------------------------------------------------------------*/
void rotate_left(Bstree_t **root, int data)
{

	int flag = 0;
	Bstree_t *node = search_node(*root, data);
	int level = find_level(*root, data);

	if ((level - 1) >= 1)
	{
		Bstree_t *dad_node = grandpa_search (*root, level - 1, data);

		if (data < dad_node->data)
			dad_node->left = node->right;
		else
			dad_node->right = node->right;
		flag = 1;
	}

	if (!flag)
		*root = node->right;	

	Bstree_t *tmp = node->right->left;
	node->right->left = node;
	node->right = tmp;

}

/*------------------------------------------------------------------------------------------------------------------*/
void rotate_right(Bstree_t **root, int data)
{
	int flag = 0;

	Bstree_t *node = search_node(*root, data);
	int level = find_level(*root, data);

	if ((level - 1) >= 1)
	{
		Bstree_t *dad_node = grandpa_search (*root, level - 1, data);

		if (data < dad_node->data)
			dad_node->left = node->left;
		else
			dad_node->right = node->left;

		flag = 1;
	}

	if (!flag)
		*root = node->left;	

	Bstree_t *tmp = node->left->right;
	node->left->right = node;
	node->left = tmp;

}


/*------------------------------------------------------------------------------------------------------------------*/
/*bfs function block*/
void bfs(Bstree_t *root, int level, int choice, int val)
{

	if (root == NULL)
	{
		printf("\t\t");
		return;
	}
	if (level == 1)
	{
		if (choice == 1)
		{
			if (root->color == 0)
			printf("%d\t\t", root->data);

			else
			printf(RED "%d\t\t" RESET, root->data);
		}

		if (choice == 2)
		{
			if (val == root->data)
			{
				printf("\nValue Found\n");
				flag = 1;
				return;
			}
		}

	}

	if (level > 1)
	{

		bfs(root->left, level - 1, choice, val);
		bfs(root->right, level - 1, choice, val);
	}
}
/*------------------------------------------------------------------------------------------------------------------*/
void check_balance(Bstree_t **root, int data, int level)
{

	Bstree_t *x_add = search_node(*root, data);
	Bstree_t *p_add = grandpa_search(*root, level - 1, data);
	Bstree_t *gp_add = grandpa_search(*root, level - 2, data);
	Bstree_t *u_add = uncle_search(gp_add, data);


	int gp_level, tmp;

	/*if parent is RED*/
	if ((p_add->color == 1 && x_add->color == 1) || x_add != *root)
	{
		if (u_add != NULL && u_add->color != 0)
		{
				/*change color of parent and uncle as BLACK*/
				p_add->color = 0;
				u_add->color = 0;

				/*change color of grand parent as RED*/
				gp_add->color = 1;

				/*check balance at grand parent*/
				gp_level = find_level(*root, gp_add->data);

				if (gp_level > 2)
					check_balance(root, gp_add->data, gp_level);
		}

		/*if uncle is BLACK*/
		else if (u_add == NULL || u_add->color == 0)
		{
			/*Left-Left case*/
			if (p_add->data < gp_add->data && data < p_add->data)
			{
				/*Right Rotate at grand parent*/
				rotate_right(root, gp_add->data);

				/*swap parent and grand parent's color*/
				tmp = gp_add->color;
				gp_add->color = p_add->color;
				p_add->color = tmp;
			}

			/*Left-Right case*/
			if (p_add->data < gp_add->data && data > p_add->data)
			{
				/*Left Rotate at parent*/
				rotate_left(root, p_add->data);
				/*Right Rotate at grand parent*/
				rotate_right(root, gp_add->data);

				tmp = gp_add->color;
				gp_add->color = x_add->color;
				x_add->color = tmp;

			}

			/*Right-Right case*/
			if (p_add->data > gp_add->data && data > p_add->data)
			{
				printf("\nR-R");
				/*Left Rotate at parent*/
				rotate_left(root, gp_add->data);

				/*swap parent and grand parent's color*/
				tmp = gp_add->color;
				gp_add->color = p_add->color;
				p_add->color = tmp;
			}

			/*Right-Left case*/
			if (p_add->data > gp_add->data && data < p_add->data)
			{
				/*Right Rotate at parent*/
				rotate_right(root, p_add->data);
				/*Left Rotate at parent*/
				rotate_left(root, gp_add->data);

				/*swap parent and grand parent's color*/
				tmp = gp_add->color;
				gp_add->color = x_add->color;
				x_add->color = tmp;
			}
		}
	}

}

/*------------------------------------------------------------------------------------------------------------------*/
Bstree_t *bro_search(Bstree_t *p_add, int val)
{

	if (val > p_add->data)
	return p_add->left;

	else
	return p_add->right;

}


/*------------------------------------------------------------------------------------------------------------------*/
Bstree_t *uncle_search(Bstree_t *gp_add, int val)
{

	if (val < gp_add->data)
	{
		if (gp_add->right != NULL)
		{
			//printf("\nYour Uncle is : %d\n", add->right->data);
			return gp_add->right;
		}

		else
			return NULL;
		//printf("\nSorry !!! Your Uncle is not here\n\n");

	}

	if (val > gp_add->data)
	{
		if (gp_add->left != NULL)
		{
			//printf("\nYour Uncle is : %d\n", add->left->data);
			return gp_add->left;
		}

		else
			return NULL;
		//printf("\nSorry !!! Your Uncle is not here\n\n");

	}


}

/*------------------------------------------------------------------------------------------------------------------*/

Bstree_t *grandpa_search(Bstree_t *root, int level, int val)
{

	if (level == 1)
	{
		return root;
	}

	if (level > 1)
	{

		if (val < root->data)
		{
			return grandpa_search(root->left, level - 1, val);
		}

		if (val > root->data)
		{
			return  grandpa_search(root->right, level - 1, val);
		}

	}
}

/*------------------------------------------------------------------------------------------------------------------*/
int find_level(Bstree_t *root, int data)
{
	Bstree_t *node = search_node(root, data);
	int node_height = find_height(node);
	int tree_height = find_height(root);
	int level = tree_height - node_height + 1;
	return level;
}
/*------------------------------------------------------------------------------------------------------------------*/

/*delete node function block*/
Bstree_t *delete_node(Bstree_t *root, int val)
{

	/*if value not found in the tree*/
	if (root == NULL)
	{
		printf("\nValue not found in the tree\n");
		return NULL;
	}

	/*check left*/
	if (val < root->data)
		root->left = delete_node(root->left, val);

	/*check right*/
	else if (val > root->data)
		root->right = delete_node(root->right, val);

	/*if equal*/
	else
	{

		/*check for single child or no child*/
		if (root->left == NULL)
		{
			Bstree_t *tmp = root->right;
			free(root);
			return tmp;
		}

		/*check for single child or no child*/
		else if (root->right == NULL)
		{
			Bstree_t *tmp = root->left;
			free(root);
			return tmp;
		}

		/*two child case*/
		else
		{
			int min = find_min(root->right);
			root->data = min;
			root->right = delete_node(root->right, min);
		}
	}

	return root;
}
/*------------------------------------------------------------------------------------------------------------------*/
/*find height function block*/
int find_height(Bstree_t *root)
{

	/*base condition*/
	if (root == NULL)
	{
		return 0;
	}

	int left, right;

	left = find_height(root->left);
	right = find_height(root->right);

	if (left > right)
		return left + 1;

	else
		return right + 1;

}
/*------------------------------------------------------------------------------------------------------------------*/
/*count nodes function block*/
int count_node(Bstree_t *root, int *count)
{

	if (root != NULL)
	{
		++(*count);
		count_node(root->left, count);
		count_node(root->right, count);
	}

}
/*------------------------------------------------------------------------------------------------------------------*/
/*search node function block*/
Bstree_t *search_node(Bstree_t *root, int data)
{

	/*search left of tree*/
	if (data < root->data)
	{

		if (root->left != NULL)
		{
			return search_node(root->left, data);
		}

		else
		{
			//printf("\nValue not found\n");
			return NULL;
		}
	}

	/*search right of tree*/
	else if (data > root->data)
	{

		if (root->right != NULL)
		{
			return search_node(root->right, data);
		}

		else
		{
			//printf("\nValue not found\n");
			return NULL;
		}
	}

	else if (data == root->data)
	{
		//printf("\nValue found\n");
		return root;
	}
}

/*------------------------------------------------------------------------------------------------------------------*/
/*find max function block*/
int find_max(Bstree_t *root)
{

	/*reach the last right node on the right side of the tree*/
	if (root->right != NULL)
	{
		return find_max(root->right);
	}

	return root->data;
}

/*------------------------------------------------------------------------------------------------------------------*/
/*find min function block*/
int find_min(Bstree_t *root)
{

	/*reach the last left node on the left side of the tree*/
	if (root->left != NULL)
	{
		return find_min(root->left);
	}
	return root->data;
}

/*------------------------------------------------------------------------------------------------------------------*/
void in_order(Bstree_t *root)
{

	if (root != NULL)
	{
		in_order(root->left);
		printf("%d ", root->data);
		in_order(root->right);
	}
}

/*------------------------------------------------------------------------------------------------------------------*/
void post_order(Bstree_t *root)
{

	if (root != NULL)
	{
		post_order(root->left);
		post_order(root->right);
		printf("%d ", root->data);
	}
}

/*------------------------------------------------------------------------------------------------------------------*/
void pre_order(Bstree_t *root)
{

	if (root != NULL)
	{
		printf("%d ", root->data);
		pre_order(root->left);
		pre_order(root->right);
	}
}
/*------------------------------------------------------------------------------------------------------------------*/
Bstree_t *create_tree(int data)
{
	Bstree_t *new = malloc(sizeof (Bstree_t));
	new->left = NULL;
	new->right = NULL;
	new->data = data;
	new->color = 1;
	return new;
}

/*------------------------------------------------------------------------------------------------------------------*/
Bstree_t *insert_tree(Bstree_t *root, int data)
{

	if (root == NULL)
	{
		root = create_tree(data);
		return root;
	}

	if (data > root->data)
	{
		root->right = insert_tree(root->right, data);
	}

	else if (data < root->data)
	{
		root->left = insert_tree(root->left, data);
	}

	else
	{
		printf("\nError!!!value you are trying to insert matches the other value in the tree\n");
	}

	return root;
}
/*------------------------------------------------------------------------------------------------------------------*/
