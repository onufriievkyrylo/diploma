#ifndef BINARY_SEARCH_TREE_LIB_H_
#define BINARY_SEARCH_TREE_LIB_H_

#include <string>
#include <iostream>

typedef double data_t;

struct BinaryTreeNode {
  BinaryTreeNode* left = nullptr;
  BinaryTreeNode* right = nullptr;
  data_t data;

  BinaryTreeNode(const data_t& data) : data(data), left(nullptr), right(nullptr) {
  }
};

BinaryTreeNode* bst_get_min_node(BinaryTreeNode* root) {
  return root->left ? bst_get_min_node(root->left) : root;
}

BinaryTreeNode* bst_internal_add(BinaryTreeNode* root, const data_t& data) {
  if (root == nullptr) {
    return new BinaryTreeNode(data);
  } else if (root->data > data) {
    root->right = bst_internal_add(root->right, data);
  } else if (root->data < data) {
    root->left = bst_internal_add(root->left, data);
  }
  return root;
}

void bst_add(BinaryTreeNode* &root, const data_t& data) {
  root = bst_internal_add(root, data);
}

BinaryTreeNode* bst_internal_remove(BinaryTreeNode* root, const data_t& data) {
  if (root == nullptr) {
    return root;
  } else if (root->data > data) {
    root->right = bst_internal_remove(root, data);
  } else if (root->data < data) {
    root->left = bst_internal_remove(root->left, data);
  } else {
    if (root->left == nullptr) {
      BinaryTreeNode* temp = root->right;
      delete root;
      return temp;
    } else if (root->right == nullptr) {
      BinaryTreeNode* temp = root->left;
      delete root;
      return temp;
    }
    BinaryTreeNode* temp = bst_get_min_node(root->right);
    root->data = temp->data;
    root->right = bst_internal_remove(root->right, temp->data);
  }
}

void bst_remove(BinaryTreeNode* &root, const data_t& data) {
  root = bst_internal_remove(root, data);
}

void bst_breadth_search(BinaryTreeNode* root) {
  const int max_queue_size = 500;
  int queue_front = 0;
  int queue_back = 0;
  int* levels = new int[max_queue_size];
  BinaryTreeNode** queue = new BinaryTreeNode*[max_queue_size];
  levels[queue_back] = 1;
  queue[queue_back++] = root;
  while (queue_front != queue_back) {
    int level = levels[queue_front];
    BinaryTreeNode* temp = queue[queue_front++];
    std::cout << std::string(level, '=') << " " << temp->data << std::endl;
    if (temp->left) {
      levels[queue_back] = level + 1;
      queue[queue_back++] = temp->left;
    }
    if (temp->right) {
      levels[queue_back] = level + 1;
      queue[queue_back++] = temp->right;
    }
  }
  delete[] queue;
}

void bst_depth_search(BinaryTreeNode* root, int level = 1) {
  if (root->left) {
    bst_depth_search(root->left, level + 1);
  }
  std::cout << std::string(level, '=') << " " << root->data << std::endl;
  if (root->right) {
    bst_depth_search(root->right, level + 1);
  }
}

#endif //BINARY_SEARCH_TREE_LIB_H_
