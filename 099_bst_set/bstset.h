#include <cstdlib>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node() : key(), left(NULL), right(NULL) {}
    Node(const T & k) : key(k), left(NULL), right(NULL) {}
    Node(const T & k, Node * l, Node * r) : key(k), left(l), right(r) {}
  };
  Node * root;
  Node * add(const T & key, Node * current) {
    if (!current) {
      return new Node(key);
    }
    if (current->key == key) {
      return current;
    }
    else if (current->key < key) {
      current->right = add(key, current->right);
    }
    else {
      current->left = add(key, current->left);
    }
    return current;
  }

  bool contains(const T & key, const Node * current) const {
    if (current == NULL) {
      return false;
    }
    if (current->key == key) {
      return true;
    }
    else if (current->key < key) {
      return contains(key, current->right);
    }
    else {
      return contains(key, current->left);
    }
  }

  Node * remove(const T & key, Node * current) {
    if (current == NULL) {
      throw std::invalid_argument("Key does not exist\n");
    }
    if (current->key == key) {
      if (current->left && current->right) {
        Node * temp = current->right;
        while (temp->left) {
          temp = temp->left;
        }
        temp->left = current->left;
        Node * new_current = current->right;
        delete current;
        return new_current;
      }
      else if (current->left) {
        Node * new_current = current->left;
        delete current;
        return new_current;
      }
      else if (current->right) {
        Node * new_current = current->right;
        delete current;
        return new_current;
      }
      else {
        delete current;
        return NULL;
      }
    }
    else if (key < current->key) {
      current->left = remove(key, current->left);
    }
    else {
      current->right = remove(key, current->right);
    }
    return current;
  }

  void destructor(Node * node) {
    if (!node) {
      return;
    }
    destructor(node->left);
    destructor(node->right);
    delete node;
  }
  Node * copy(Node * node) {
    if (!node) {
      return NULL;
    }
    Node * curr = new Node(node->key);
    curr->left = copy(node->left);
    curr->right = copy(node->right);
    return curr;
  }

 public:
  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs) : root(NULL) { root = copy(rhs.root); }
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      destructor(root);
      root = copy(rhs.root);
    }
    return *this;
  }
  virtual ~BstSet() { destructor(root); }
  virtual void add(const T & key) { root = add(key, root); }
  virtual bool contains(const T & key) const {
    // bool res = contains(key, root);
    return contains(key, root);
  }
  virtual void remove(const T & key) { root = remove(key, root); }
};
