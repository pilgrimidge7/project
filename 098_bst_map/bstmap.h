#include <cstdlib>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : key(), value(), left(NULL), right(NULL) {}
    Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL) {}
    Node(const K & k, const V & v, Node * l, Node * r) :
        key(k),
        value(v),
        left(l),
        right(r) {}
  };
  Node * root;
  const V & lookup(const K & toFind, const Node * current) const {
    if (current == NULL) {
      throw std::invalid_argument("Key does not exist in tree.\n");
    }
    if (current->key == toFind) {
      return current->value;
    }
    if (toFind < current->key) {
      return lookup(toFind, current->left);
    }
    else {
      return lookup(toFind, current->right);
    }
  }
  Node * add(const K & key, const V & val, Node * current) {
    if (current == NULL) {
      return new Node(key, val);
    }
    if (current->key == key) {
      current->value = val;
    }
    else if (key < current->key) {
      current->left = add(key, val, current->left);
    }
    else {
      current->right = add(key, val, current->right);
    }
    return current;
  }
  Node * remove(const K & key, Node * current) {
    if (current == NULL) {
      throw std::invalid_argument("Key does not exist in this tree.\n");
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
    Node * curr = new Node(node->key, node->value);
    curr->left = copy(node->left);
    curr->right = copy(node->right);
    return curr;
  }

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      destructor(root);
      root = copy(rhs.root);
    }
    return *this;
  }
  virtual void add(const K & key, const V & value) { root = add(key, value, root); }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    return lookup(key, this->root);
  }
  virtual void remove(const K & key) { root = remove(key, root); }
  virtual ~BstMap() { destructor(root); }
};
