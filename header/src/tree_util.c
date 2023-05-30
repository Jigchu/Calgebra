#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "tree_util.h"
#include "deque.h"

bool has_operator(equation *node)
{
    char *operators = "+-*/^";

    for (int i = 0, count = strlen(operators); i < count; i++)
    {
        if (node->val[0] == operators[i])
        {
            return true;
        }
    }
    
    return false;
}

// Finds the max height of a tree
int height(equation *root)
{
    if (root == NULL || !strcmp(root->val, ")") || !strcmp(root->val, "]") || !strcmp(root->val, "}"))
    {
        return 0;
    }

    int left_height = height(root->left);
    int right_height = !strcmp(root->val, "(") || !strcmp(root->val, "[") || !strcmp(root->val, "{") ? 0 : height(root->right);

    return left_height >= right_height ? left_height++ : right_height++;
}

// Locates a node on the tree based on its value. If the search value is NULL then finds a leaf node that parent is an operator
deque *dfs(equation *tree, char *search_val)
{
	if (tree == NULL)
    {
        return init_deque(NULL, 1, 0);
    }
    
    // Get left and right deque
    deque *left = dfs(tree->left, search_val);
    deque *right = dfs(tree->right, search_val);

    if (left == NULL || right == NULL)
    {
        dlt_deque(left);
        dlt_deque(right);

        return NULL;
    }
    
    // Merge the deques
    for (long i = 0, count = get_count(right); i < count; i++)
    {
        equation *node = get_element(right, i);

        if (node == NULL)
        {
            free(dlt_deque(left));
            free(dlt_deque(right));

            return NULL;
        }

        if (push(left, node) != 0)
        {        
            free(dlt_deque(left));
            free(dlt_deque(right));

            return NULL;
        }
    }

    // Check if curr_node matches
    int retval = 0;
    equation *push_val;

    if (search_val == NULL)
    {
        push_val = has_operator(tree) && (tree->left == NULL || tree->right == NULL) ? tree : NULL;
    }
    else
    {
        push_val = !strcmp(tree->val, search_val) ? tree : NULL;
    }
    
    retval = push(left, push_val);

    if (retval == -2)
    {
        free(dlt_deque(left));
        free(dlt_deque(right));
        
        return NULL;
    }

    // Returns deque
    return left;
}

// Inserts a node in respective location
equation *insert(equation *value, equation *location, bool left)
{
    // Checking invalid input
    if (value == NULL || location == NULL)
	{
		return value;
	}
    
    // Insert || Replace node
    equation *replaced = left ? location->left : location->right;

    if (left)
    {
        location->left = value;
    }
    else
    {
        location->right = value;
    }
    
    return replaced;
}