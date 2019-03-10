#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

#include <string>
#include <iostream>

typedef double data_t;

enum color_t { RED, BLACK, DOUBLE_BLACK };

struct RedBlackTreeNode {
  RedBlackTreeNode* parent = nullptr;
  RedBlackTreeNode* left = nullptr;
  RedBlackTreeNode* right = nullptr;
  data_t data;
  color_t color;

  RedBlackTreeNode(const data_t& data)
    : data(data), parent(nullptr), left(nullptr), right(nullptr), color(RED) {
  }
};

color_t rb_get_color(RedBlackTreeNode* &root) {
  return root == nullptr ? BLACK : root->color;
}

void rb_set_color(RedBlackTreeNode* &root, color_t color) {
  if (root != nullptr)
    root->color = color;
}

void rb_rotate_right(RedBlackTreeNode* &root, RedBlackTreeNode* &node) {
  RedBlackTreeNode* left_child = node->left;
  node->left = left_child->right;
  if (node->left != nullptr)
    node->left->parent = node;
  left_child->parent = node->parent;
  if (node->parent == nullptr)
    root = left_child;
  else if (node == node->parent->left)
    node->parent->left = left_child;
  else
    node->parent->right = left_child;
  left_child->right = node;
  node->parent = left_child;
}

void rb_rotate_left(RedBlackTreeNode* &root, RedBlackTreeNode* &node) {
  RedBlackTreeNode* right_child = node->right;
  node->right = right_child->left;
  if (node->right != nullptr)
    node->right->parent = node;
  right_child->parent = node->parent;
  if (node->parent == nullptr)
    root = right_child;
  else if (node == node->parent->left)
    node->parent->left = right_child;
  else
    node->parent->right = right_child;
  right_child->left = node;
  node->parent = right_child;
}

RedBlackTreeNode* rb_get_min_node(RedBlackTreeNode* root) {
  return root->left ? rb_get_min_node(root->left) : root;
}

void rb_fix_add(RedBlackTreeNode* &root, RedBlackTreeNode* &added) {
  RedBlackTreeNode* parent = nullptr;
  RedBlackTreeNode* grandparent = nullptr;
  while (added != root && rb_get_color(added) == RED && rb_get_color(added->parent) == RED) {
    parent = added->parent;
    grandparent = parent->parent;
    if (parent == grandparent->left) {
      RedBlackTreeNode* uncle = grandparent->right;
      if (rb_get_color(uncle) == RED) {
        rb_set_color(uncle, BLACK);
        rb_set_color(parent, BLACK);
        rb_set_color(grandparent, RED);
        added = grandparent;
      } else {
        if (added == parent->right) {
          rb_rotate_left(root, parent);
          added = parent;
          parent = added->parent;
        }
        rb_rotate_right(root, grandparent);
        color_t temp_color = parent->color;
        parent->color = grandparent->color;
        grandparent->color = temp_color;
        added = parent;
      }
    } else {
      RedBlackTreeNode* uncle = grandparent->left;
      if (rb_get_color(uncle) == RED) {
        rb_set_color(uncle, BLACK);
        rb_set_color(parent, BLACK);
        rb_set_color(grandparent, RED);
        added = grandparent;
      } else {
        if (added == parent->left) {
          rb_rotate_right(root, parent);
          added = parent;
          parent = added->parent;
        }
        rb_rotate_left(root, grandparent);
        color_t temp_color = parent->color;
        parent->color = grandparent->color;
        grandparent->color = temp_color;
        added = parent;
      }
    }
  }
  rb_set_color(root, BLACK);
}

void rb_fix_remove(RedBlackTreeNode* &root, RedBlackTreeNode* &removed) {
  if (removed == nullptr)
    return;
  if (removed == root) {
    root = nullptr;
    return;
  }
  if (rb_get_color(removed) == RED || rb_get_color(removed->left) == RED || rb_get_color(removed->right) == RED) {
    RedBlackTreeNode* child = removed->left != nullptr ? removed->left : removed->right;
    if (removed == removed->parent->left) {
      removed->parent->left = child;
      if (child != nullptr)
        child->parent = removed->parent;
      rb_set_color(child, BLACK);
      delete removed;
    } else {
      removed->parent->right = child;
      if (child != nullptr)
        child->parent = removed->parent;
      rb_set_color(child, BLACK);
      delete removed;
    }
  } else {
    RedBlackTreeNode* sibling = nullptr;
    RedBlackTreeNode* parent = nullptr;
    RedBlackTreeNode* ptr = removed;
    rb_set_color(ptr, DOUBLE_BLACK);
    while (ptr != root && rb_get_color(ptr) == DOUBLE_BLACK) {
      parent = ptr->parent;
      if (ptr == parent->left) {
        sibling = parent->right;
        if (rb_get_color(sibling) == RED) {
          rb_set_color(sibling, BLACK);
          rb_set_color(parent, RED);
          rb_rotate_left(root, parent);
        } else {
          if (rb_get_color(sibling->left) == BLACK && rb_get_color(sibling->right) == BLACK) {
            rb_set_color(sibling, RED);
            if (rb_get_color(parent) == RED)
              rb_set_color(parent, BLACK);
            else
              rb_set_color(parent, DOUBLE_BLACK);
            ptr = parent;
          } else {
            if (rb_get_color(sibling->right) == BLACK) {
              rb_set_color(sibling->left, BLACK);
              rb_set_color(sibling, RED);
              rb_rotate_right(root, sibling);
              sibling = parent->right;
            }
            rb_set_color(sibling, parent->color);
            rb_set_color(parent, BLACK);
            rb_set_color(sibling->right, BLACK);
            rb_rotate_left(root, parent);
            break;
          }
        }
      } else {
        sibling = parent->left;
        if (rb_get_color(sibling) == RED) {
          rb_set_color(sibling, BLACK);
          rb_set_color(parent, RED);
          rb_rotate_right(root, parent);
        } else if (rb_get_color(sibling->left) == BLACK && rb_get_color(sibling->right) == BLACK) {
          rb_set_color(sibling, RED);
          if (rb_get_color(parent) == RED)
            rb_set_color(parent, BLACK);
          else
            rb_set_color(parent, DOUBLE_BLACK);
          ptr = parent;
        } else {
          if (rb_get_color(sibling->left) == BLACK) {
            rb_set_color(sibling->right, BLACK);
            rb_set_color(sibling, RED);
            rb_rotate_left(root, sibling);
            sibling = parent->left;
          }
          rb_set_color(sibling, parent->color);
          rb_set_color(parent, BLACK);
          rb_set_color(sibling->left, BLACK);
          rb_rotate_right(root, parent);
          break;
        }
      }
    }
    if (removed == removed->parent->left)
      removed->parent->left = nullptr;
    else
      removed->parent->right = nullptr;
    delete removed;
    rb_set_color(root, BLACK);
  }
}

RedBlackTreeNode* rb_internal_add(RedBlackTreeNode* &root, RedBlackTreeNode* &added) {
  if (root == nullptr) {
    return added;
  } else if (added->data < root->data) {
    root->left = rb_internal_add(root->left, added);
    root->left->parent = root;
  } else if (added->data > root->data) {
    root->right = rb_internal_add(root->right, added);
    root->right->parent = root;
  }
  return root;
}

void rb_add(RedBlackTreeNode* &root, const data_t &data) {
  RedBlackTreeNode* added = new RedBlackTreeNode(data);
  root = rb_internal_add(root, added);
  rb_fix_add(root, added);
}

RedBlackTreeNode* rb_internal_remove(RedBlackTreeNode* &root, const data_t &data) {
  if (root == nullptr) {
    return root;
  } else if (data < root->data) {
    return rb_internal_remove(root->left, data);
  } else if (data > root->data) {
    return rb_internal_remove(root->right, data);
  } else if (root->left == nullptr || root->right == nullptr) {
    return root;
  }

  RedBlackTreeNode* temp = rb_get_min_node(root->right);
  root->data = temp->data;
  return rb_internal_remove(root->right, root->data);
}

void rb_remove(RedBlackTreeNode* &root, const data_t &data) {
  RedBlackTreeNode* removed = rb_internal_remove(root, data);
  rb_fix_remove(root, removed);
}

void rb_breadth_search(RedBlackTreeNode* root) {
  const int max_queue_size = 500;
  int queue_front = 0;
  int queue_back = 0;
  int* levels = new int[max_queue_size];
  RedBlackTreeNode** queue = new RedBlackTreeNode*[max_queue_size];
  levels[queue_back] = 1;
  queue[queue_back++] = root;
  while (queue_front != queue_back) {
    int level = levels[queue_front];
    RedBlackTreeNode* temp = queue[queue_front++];
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

void rb_depth_search(RedBlackTreeNode* root, int level = 1) {
  if (root->left) {
    rb_depth_search(root->left, level + 1);
  }
  std::cout << std::string(level, '=') << " " << root->data << std::endl;
  if (root->right) {
    rb_depth_search(root->right, level + 1);
  }
}

#endif // RED_BLACK_TREE_H_