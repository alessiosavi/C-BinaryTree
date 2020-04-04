#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Tree Tree;

struct Tree {
  int value;
  Tree *left;
  Tree *right;
};

// init_tree is delagated to initialize a new node
Tree *init_node(int val) {
  Tree *tree = (Tree *)malloc(sizeof(Tree));
  tree->value = val;
  tree->left = NULL;
  tree->right = NULL;
  return tree;
}

void insert(Tree **tree, int val) {

  // Empty tree
  if (*tree == NULL) {
    *tree = init_node(val);
    return;
  }
  Tree *root = *tree;
  // Managing left insert
  if (val <= root->value) {
    if (root->left == NULL) {
      root->left = init_node(val);
    } else {
      insert(&root->left, val);
    }
  } else {
    if (root->right == NULL) {
      root->right = init_node(val);
    } else {
      insert(&root->right, val);
    }
  }
}

void visit_pre_order(Tree *root) {
  if (root->left != NULL) {
    visit_pre_order(root->left);
  }
  printf("%d ", root->value);
  if (root->right != NULL) {
    visit_pre_order(root->right);
  }
}

void visit_post_order(Tree *root) {
  if (root->right != NULL) {
    visit_post_order(root->right);
  }
  printf("%d ", root->value);
  if (root->left != NULL) {
    visit_post_order(root->left);
  }
}

Tree *create_test_tree(int n_value) {

  int *values = malloc(sizeof(int) * n_value);
  srand(time(NULL)); // Initialization, should only be called once.
  Tree *root = NULL;

  for (int i = 0; i < n_value; i++) {
    insert(&root, rand() % (n_value * 2));
  }
  free(values);
  return root;
}

void free_tree(Tree **root) {
  if ((*root)->left != NULL) {
    free_tree(&(*root)->left);
    free((*root)->left);
  }
  if ((*root)->right != NULL) {
    free_tree(&(*root)->right);
    free((*root)->right);
  }
}

int main() {
  Tree *tree = create_test_tree(10);
  visit_pre_order(tree);
  printf("\n");
  visit_post_order(tree);
  printf("\n");
  free_tree(&tree);

  free(tree);
  return 0;
}
