#include <iostream>

#include "./lib/binary_search_tree.h"
#include "./lib/avl_tree.h"
#include "./lib/red_black_tree.h"

int main() {
  std::cout << "----Red-Black----" << std::endl << std::endl;
  RedBlackTreeNode* rb_root = nullptr;

  rb_add(rb_root, 0);
  rb_add(rb_root, -2);
  rb_add(rb_root, -20);
  rb_add(rb_root, -15);
  rb_add(rb_root, 2);
  rb_add(rb_root, 15);
  rb_add(rb_root, 20);
  rb_add(rb_root, 21);

  rb_remove(rb_root, 0);

  rb_depth_search(rb_root);

  std::cout << "----AVL----" << std::endl << std::endl;

  AVLTreeNode* avl_root = nullptr;

  avl_add(avl_root, 0);
  avl_add(avl_root, -2);
  avl_add(avl_root, -20);
  avl_add(avl_root, -15);
  avl_add(avl_root, 2);
  avl_add(avl_root, 15);
  avl_add(avl_root, 20);
  avl_add(avl_root, 21);

  avl_remove(avl_root, 0);

  avl_depth_search(avl_root);

  return 0;
}