#include <stdlib.h>
#include <stdio.h>

//
// A binary tree node with value and left and right children
struct Node {
  int value;
  struct Node *left, *right;
};

//
// Create a new node
//
struct Node* newNode(int value) {
  struct Node *node = malloc(sizeof(struct Node));
  node->left = NULL;
  node->right = NULL;
  node->value = value;
}

//
// Insert node n into tree rooted at toNode
//
void insertNode (struct Node* toNode, struct Node* n) {
  if (n->value <= toNode->value) {
    if (toNode->left == NULL) {
      toNode->left = n;
    } else {
      insertNode(toNode->left, n);
    }
  } else {
    if (toNode->right == NULL) {
      toNode->right = n;
    } else {
      insertNode(toNode->right, n);
    }
  }
}

//
// Insert new node with specified value into tree rooted at toNode
//
void insert (struct Node* toNode, int value) {
  struct Node *n = newNode(value);
  insertNode(toNode, n);
}


//
// Print values of tree rooted at node in ascending order
//
void printInOrder (struct Node* node) {
  if (node->left != NULL) {
    printInOrder(node->left);
  }
  printf("%d\n", node->value);
  if (node->right != NULL) {
    printInOrder(node->right);
  }
}

//
// Create root node, insert some values, and print tree in order
//
int main (int argc, char* argv[]) {
  struct Node *root = newNode(100);
  insert (root, 10);
  insert (root, 120);
  insert (root, 130);
  insert (root, 90);
  insert (root, 5);
  insert (root, 95);
  insert (root, 121);
  insert (root, 131);
  insert (root, 1);
  printInOrder(root);
}
