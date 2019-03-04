#ifndef AVL_TREE_LIB_H_
#define AVL_TREE_LIB_H_

typedef double data_t;

struct AVLTreeNode {
  AVLTreeNode* left = nullptr;
  AVLTreeNode* right = nullptr;
  data_t data;
  int height;

  AVLTreeNode(const data_t& data) : data(data), left(nullptr), right(nullptr), height(1) {
  }
};

int fix_height(AVLTreeNode* root) {
  int right_height = root->right ? root->right->height : 0;
  int left_height = root->left ? root->left->height : 0;
  if (right_height > left_height) {
    root->height = right_height + 1;
  } else {
    root->height = left_height + 1;
  }
}

int factor(AVLTreeNode* root) {
  return (root->right ? root->right->height : 0) - (root->left ? root->left->height : 0);
}

AVLTreeNode* avl_get_min_node(AVLTreeNode* root) {
  return root->left ? avl_get_min_node(root->left) : root;
}

AVLTreeNode* avl_rotate_right(AVLTreeNode* root) {
  AVLTreeNode* temp = root->left;
  root->left = temp->right;
  temp->right = root;
  fix_height(root);
  fix_height(temp);
  return temp;
}

AVLTreeNode* avl_rotate_left(AVLTreeNode* root) {
  AVLTreeNode* temp = root->right;
  root->right = temp->left;
  temp->left = root;
  fix_height(root);
  fix_height(temp);
  return temp;
}

AVLTreeNode* avl_balance(AVLTreeNode* root) {
  fix_height(root);
  if (factor(root) == 2) {
    if (factor(root->right) < 0) {
      root->right = avl_rotate_right(root->right);
    }
    return avl_rotate_left(root);
  } else if (factor(root) == -2) {
    if (factor(root->left) > 0) {
      root->left = avl_rotate_left(root->left);
    }
    return avl_rotate_right(root);
  }
  return root;
}

AVLTreeNode* avl_remove_min(AVLTreeNode* root) {
  if (root->left) {
    root->left = avl_remove_min(root->left);
  } else {
    delete root->left;
    root->left = root->right;
  }
  return avl_balance(root);
}

AVLTreeNode* avl_add(AVLTreeNode* root, const data_t& data) {
  if (root == nullptr) {
    return new AVLTreeNode(data);
  } else if (data > root->data) {
    root->right = avl_add(root->right, data);
  } else if (data < root->data) {
    root->left = avl_add(root->left, data);
  }
  return root;
  // return avl_balance(root);
}

AVLTreeNode* avl_remove(AVLTreeNode* root, const data_t& data) {
  if (data > root->data) {
    root->right = avl_remove(root->right, data);
  } else if (data < root->data) {
    root->left = avl_remove(root->left, data);
  } else {
    if (!root->right) return root->right;
    AVLTreeNode* temp = avl_get_min_node(root->right);
    temp->right = avl_remove_min(temp->right);
    temp->left = root->left;
    delete root;
    return avl_balance(temp);
  }
  return avl_balance(root);
}

void avl_breadth_search(AVLTreeNode* root) {
  const int max_queue_size = 500;
  int queue_front = 0;
  int queue_back = 0;
  int* levels = new int[max_queue_size];
  AVLTreeNode** queue = new AVLTreeNode*[max_queue_size];
  levels[queue_back] = 1;
  queue[queue_back++] = root;
  while (queue_front != queue_back) {
    int level = levels[queue_front];
    AVLTreeNode* temp = queue[queue_front++];
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

void avl_depth_search(AVLTreeNode* root, int level = 1) {
  if (root->left) {
    avl_depth_search(root->left, level + 1);
  }
  std::cout << std::string(level, '=') << " " << root->data << std::endl;
  if (root->right) {
    avl_depth_search(root->right, level + 1);
  }
}

#endif //AVL_TREE_LIB_H_
