#pragma once

#include <stdbool.h>

#include "deque.h"

// A struct for each node of the tree
typedef struct node
{
    char *val;

    struct node *left;
    struct node *right;
} equation;

// Locates a node on the tree based on its value. If the search value is NULL then finds a leaf node
deque *dfs(equation *tree, char *search_val);

// Finds the max height of a tree
int height(equation *root);

// Inserts a node in respective location
equation *insert(equation *value, equation *location, bool left);