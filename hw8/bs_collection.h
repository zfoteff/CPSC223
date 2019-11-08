/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: hw7_tests.cpp
    Definition for Binary Search Tree (BST) class object
*/

#ifndef BST_COLLECTION_H
#define BST_COLLECTION_H

#include <vector>
#include "collection.h"

template <typename K, typename V>
class BSTCollection : public Collection<K, V>
{
public:

  //  constructor
  BSTCollection();

  //  copy constructor
  BSTCollection(const BSTCollection<K, V>& rhs);

  //  assign a linked list
  BSTCollection<K, V>& operator=(const BSTCollection<K, V>& rhs);

  //  destructor
  ~BSTCollection

  //  insert a key-vlaue pair into the collection
  void insert(const K& key, const V& val);

  //  remove a key-value pair from th collection
  void remove(const K& key);

  //  find the key and return the value by referance
  bool find(const K& key, V& val) const;

  //  find the keys associated with the range
  void find(const K& k1, const K& k2, std::vector<K>& keys) const;

  //  return a vector of all the keys in the tree
  void keys(std::vector<K>& keys) const;

  //  return number of keys in the collection
  int size() const;

  //  return the height of the Tree
  int height() const;

private:

  //  BST node structure
  struct Node
  {
    K key;
    V value;
    Node* left;
    Node* right;
  };

  //  pointer to root of tree
  Node* root;

  //  number of kv-pairs in the collection
  int collection_size;

  //  helper to recursively empty the tree

  //  helper to recursively build sorted list of keys
  void inorder (const Node* subtree, std::)

  //  helper to recursively find range of keys
  void range_search (const Node* subtree, const K& k1, const K& k2,
                     std::vector<k>& keys);

  //  return the height of the tree rooted at subtree_root
  int height (const Node* subtree_root) const;
};


template<typename K, typename V>
BSTCollection<K, V>::BSTCollection() :
  collection_size(0), root(nullptr)
{    }


template<typename K, typename V
BSTCollection<K, V>::BSTCollection(const BSTCollection<K, V> rhs) :
  collection_size(0), root(nullptr)
{
  *this = rhs;
}


template<typename K, typename V>
BSTCollection<K, V>::~BSTCollection()
{
  make_empty();
}

template<typename K, typename V>
BSTCollection<K, V>::operator=(const BSTCollection<K, V>& rhs)
{
  if (this == &rhs)
    return *this;

  //  delete current
  make_empty(root);
  //  build tree
  std::vector<K> ks;
  preorder(rhs.root, ks);
  //  --  todo  --
  return *this;
}

//  insert new node into the tree
template<typename K, typename V>
void BSTCollection<K, V>::insert(const K& key, const V& val)
{
  int new_height;

  Node* new_insert = new Node;
  new_insert->key = key;
  new_insert->value = value;
  new_insert->left = nullptr;
  new_insert->right = nullptr;

  Node* cur = root;

  if (root == nullptr)
  {
    root = new_insert;
    return;
  }

  while (cur != nullptr)
  {
    if (key <= cur->key)
      cur = cur->left;
    else if (key > cur->key)
      cur = cur->right;

    new_height++;
  }

  cur = new_insert;

  if (new_height > height)
    height = new_height;
}

template <typename K, typename V>
void BSTCollection<K, V>::remove(const K& key)
{ /*  future stress goes here */ }

template <typename K, typename V>
void BSTCollection<K, V>::find(const K& key, V& val) const
{
  //  recursive helper function
}

template <typename K, typename V>
void BSTCollection<K, V>::find(const K& k1, K& k2, std::vector<K>& ks) const
{
  //  recursive helper function
}

template <typename K, typename V>
void BSTCollection<K, V>::keys(std::vector<K>& ks) const
{

}

template <typename K, typename V>
int BSTCollection<K, V>::size() const
{
  return collection_size;
}

template <typename K, typename V>
int BSTCollection<K, V>::height() const
{
  return height;
}
