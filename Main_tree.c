

#include <stdio.h>
#include "tree.h"

/*main function block*/
int main()
{

	/*local variable declaration*/
	Bstree_t *root = NULL;
	int choice, data, flag = 0;

	do
	{

		/*menu for user*/
		printf("\nChoose the operation\n\n\t1.Insert Tree\n\t2.Find Min\n\t3.Find Max\n\t4.Print in order\n\t5.Print pre order\n\t6.Print post order\n\t7.Search Node\n\t8.Count Nodes\n\t9.Find height\n\t10.Delete Node\n\t11.BFS\n\t12.DFS\n\t13.Find Level\n\t14.Search Grandpa\n\t15.Search Father\n\t16.Find Uncle\n\t17.Find Brother\n\t18.Rotate Left\n\t19.Rotate Right\n\t20.Exit\n\nEnter the choice : ");
		scanf("%d", &choice);

		switch (choice)
		{

			/*Insert tree case*/	
			case 1:
				{
					printf("\nEnter the int data : ");
					scanf("%d", &data);

					if (root == NULL)
						flag = 1;

					root = insert_tree(root, data);

					if (flag == 1)
					{
						root->color = 0;
						flag = 0;
					}
					int level = find_level(root, data);

					if (level > 2)
					{
						check_balance(&root, data, level);
						root->color = 0;
					}
				}
				break;

				/*find min case*/	
			case 2:
				{
					int min = find_min(root);
					printf("\nMin value is %d\n", min);
				}
				break;

				/*find max case*/	
			case 3:
				{
					int max = find_max(root);
					printf("\nMin value is %d\n", max);

				}
				break;
				/*print in order case*/
			case 4:
				{
					in_order(root);
				}
				break;

				/*print pre order case*/
			case 5:
				{
					pre_order(root);
				}
				break;

				/*print post order case*/
			case 6:
				{
					post_order(root);
				}
				break;

				/*search case*/
			case 7:
				{

					printf("\nEnter the val to be found : ");
					scanf("%d", &data);
					search_node(root, data);
				}
				break;
				/*count node case*/
			case 8:
				{
					int count = 0;
					count_node(root, &count);
					printf("\nNumber of nodes in tree is %d\n", count);
				}
				break;

				/*find height case*/		
			case 9:
				{
					int height = find_height(root);
					printf("\nHeight of tree is %d\n", height);
				}
				break;

			case 10:
				{
					printf("\nEnter the val to be deleted : ");
					scanf("%d", &data);
					delete_node(root, data);
				}
				break;

				/*BFS case*/
			case 11:
				{
					printf("\n\n1.Print\t2.Search\n");
					scanf("%d", &choice);

					if (choice == 1)
						bfs_fun(root, choice, 0);

					else if (choice == 2)
					{
						printf("\nEnter the val : ");
						scanf("%d", &data);

						bfs_fun(root, choice, data);
					}
					else
					{
						printf("\nInvalid choice entered\n");
					}

				}
				break;

				/*DFS case*/
			case 12:
				{

					printf("\nEnter the val : ");
					scanf("%d", &data);
					/*find the height of the tree*/
					int height = find_height(root);
					int level = dfs_fun(root, height, data);
				}
				break;

				/*Find Level case*/
			case 13:
				{
					printf("\nEnter the val : ");
					scanf("%d", &data);

					int level = find_level(root, data);
					printf("\nLevel of the node : %d\n", level);
				}
				break;

				/*Search Grandpa case*/
			case 14:
				{
					printf("\nEnter the val : ");
					scanf("%d", &data);

					int level = find_level(root, data);

					if ((level - 2) < 1)
					{
						printf("\nSorry !!! Your Grandpa is Not Here\n\n");
						break;
					}
					Bstree_t *add = grandpa_search(root, level - 2, data);
					printf("\nYour Grandpa is : %d\n\n", add->data);
				}
				break;

				/*Find father case*/
			case 15:
				{
					printf("\nEnter the val : ");
					scanf("%d", &data);

					int level = find_level(root, data);

					if ((level - 1) < 1)
					{
						printf("\nSorry !!! Your Father is not here\n\n");
						break;
					}
					Bstree_t *add = grandpa_search(root, level - 1, data);
					printf("\nYour papa is : %d\n\n", add->data);
				}
				break;

				/*Find Uncle case*/
			case 16:
				{
					printf("\nEnter the val : ");
					scanf("%d", &data);

					int level = find_level(root, data);

					if ((level - 2) < 1)
					{
						printf("\nSorry !!! Your Uncle is not here\n\n");
						break;
					}
					Bstree_t *add = grandpa_search(root, level - 2, data);
					if (data < add->data)
					{
						if (add->right != NULL)
						{
							printf("\nYour Uncle is : %d\n", add->right->data);
						}

						else
							printf("\nSorry !!! Your Uncle is not here\n\n");

					}

					if (data > add->data)
					{
						if (add->left != NULL)
						{
							printf("\nYour Uncle is : %d\n", add->left->data);
						}

						else
							printf("\nSorry !!! Your Uncle is not here\n\n");

					}
				}
				break;

				/*Find Brother case*/
			case 17:
				{
					return 0;
				}
				break;

				/*Rotate Left case*/
			case 18:
				{
					printf("\nEnter the val : ");
					scanf("%d", &data);

					rotate_left(&root, data);

				}
				break;

				/*Rotate Right case*/
			case 19:
				{
					printf("\nEnter the val : ");
					scanf("%d", &data);

					rotate_right(&root, data);
				}
				break;

				/*exit case*/
			case 20:
				{
					return 0;
				}
				break;
		}

	} while (1);
}
