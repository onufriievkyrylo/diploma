#include <iostream>

#include "./lib/binary_search_tree.h"
#include "./lib/avl_tree.h"


int main() {
  AVLTreeNode* root = new AVLTreeNode(0);

  root = avl_add(root, -20);
  root = avl_add(root, -2);
  root = avl_add(root, -15);
  root = avl_add(root, 2);
  root = avl_add(root, 15);
  root = avl_add(root, 20);

  // root = remove(root, 0);

  avl_depth_search(root);

  return 0;
}