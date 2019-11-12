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
#include <iostream>
#include "collection.h"

using namespace std;

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
  ~BSTCollection();

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

  //  return a vector of sorted keys
  void sort(std::vector<K>& ks) const;

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
  void make_empty(Node* root);

  //  helper to recursively build sorted list of keys
  void inorder (const Node* subtree, std::vector<K>& ks) const;

  void preorder (const Node* subtree, std::vector<K>& ks) const;

  //  helper to recursively find range of keys
  void range_search (const Node* subtree, const K& k1, const K& k2,
                     std::vector<K>& keys) const;

  //  return the height of the tree rooted at subtree_root
  int height (const Node* subtree_root) const;

  //  print the keys in the Tree
  void print() const;
};


template<typename K, typename V>
BSTCollection<K, V>::BSTCollection() :
  collection_size(0), root(nullptr)
{    }


template<typename K, typename V>
BSTCollection<K, V>::BSTCollection(const BSTCollection<K, V>& rhs)
: collection_size(0), root(nullptr)
{
  *this = rhs;
}


template<typename K, typename V>
BSTCollection<K, V>::~BSTCollection()
{
  make_empty(root);
}

template<typename K, typename V>
BSTCollection<K, V>& BSTCollection<K, V>::operator=(const BSTCollection<K, V>& rhs)
{
  if (this == &rhs)
    return *this;

  //  delete current
  make_empty(root);
  //  build tree
  std::vector<K> ks;
  preorder(rhs.root, ks);
  //  create a new node in the new list using the kv-pair from rhs
  for (K key : ks)
  {
    V val;
    rhs.find(key, val);
    insert(key, val);
  }

  return *this;
}


template <typename K, typename V>
void BSTCollection<K, V>::make_empty(Node* subtree_root)
{
  if (subtree_root != nullptr)
  {
    make_empty(subtree_root->left);
    make_empty(subtree_root->right);
    delete subtree_root;
  }
}

template <typename K, typename V>
void BSTCollection<K, V>::inorder(const Node* subtree, std::vector<K>& ks) const
{
  //  recursive helper function
  if (subtree == nullptr)
    return;

  inorder(subtree->left, ks);
  ks.push_back(subtree->key);
  inorder(subtree->right, ks);
}

template <typename K, typename V>
void BSTCollection<K, V>::preorder(const Node* subtree, std::vector<K>& ks) const
{
  //  recursive helper function
  if (subtree == nullptr)
    return;

  ks.push_back(subtree->key);
  inorder(subtree->left, ks);
  inorder(subtree->right, ks);
}

template <typename K, typename V>
void BSTCollection<K, V>::range_search(const Node* subtree, const K& k1,
                                       const K& k2, std::vector<K>& keys) const
{
  if (subtree == nullptr)
    return;

  if (k1 < subtree->key)
    range_search(subtree->left, k1, k2, keys);

  if (subtree->key > k1 && subtree->key < k2)
    keys.push_back(subtree->key);

  if (k2 > subtree->key)
    range_search(subtree->right, k1, k2, keys);
}

template <typename K, typename V>
int BSTCollection<K, V>::height(const Node* subtree_root) const
{
  if (subtree_root == nullptr)
    return 0;

  int lhs = 1 + height(subtree_root->left);
  int rhs = 1 + height(subtree_root->right);

  if (lhs > rhs)
    return lhs;

  return rhs;
}

//  insert new node into the tree
template<typename K, typename V>
void BSTCollection<K, V>::insert(const K& key, const V& val)
{
  Node* new_insert = new Node;
  new_insert->key = key;
  new_insert->value = val;
  new_insert->left = nullptr;
  new_insert->right = nullptr;

  if (root == nullptr)
  {
    root = new_insert;
    collection_size++;
    return;
  }

  if (root->left == nullptr && root->right == nullptr)
  {
    if (key < root->key)
      root->left = new_insert;
    else
      root->right = new_insert;

    collection_size++;
    return;
  }

  Node* cur = root;
  Node* parent = nullptr;

  //  iterate down to leaf level
  while (cur != nullptr)
  {
    parent = cur;
    if (key <= cur->key)
      cur = cur->left;
    else
      cur = cur->right;
  }

  if (key <= parent->key)
      parent->left = new_insert;
  else
      parent->right = new_insert;

  collection_size++;
}

template <typename K, typename V>
void BSTCollection<K, V>::remove(const K& key)
{ /*  future stress goes here */ }

template <typename K, typename V>
bool BSTCollection<K, V>::find(const K& key, V& val) const
{
  Node* cur = root;

  while (cur != nullptr)
  {
    if (cur->key == key)
    {
      val = cur->value;
      return true;
    }

    else if (key <= cur->key)
      cur = cur->left;

    else if (key > cur->key)
      cur = cur->right;
  }

  return false;
}

template <typename K, typename V>
void BSTCollection<K, V>::find(const K& k1, const K& k2, std::vector<K>& ks) const
{
  //  recursive helper function
  range_search(root, k1, k2, ks);
}

template <typename K, typename V>
void BSTCollection<K, V>::keys(std::vector<K>& ks) const { inorder(root, ks); }

template <typename K, typename V>
void BSTCollection<K, V>::sort(std::vector<K>& ks) const { inorder(root, ks); }

template <typename K, typename V>
int BSTCollection<K, V>::size() const { return collection_size; }

template <typename K, typename V>
int BSTCollection<K, V>::height() const { return height(root); }

template <typename K, typename V>
void BSTCollection<K, V>::print() const
{
  std::cout<<"START OF PRINT"<<std::endl;
  std::vector<K> ks;
  keys(ks);

  for (K key : ks)
  {
    std::cout<<key+" ";
  }

  std::cout<<"END OF PRINT"<<std::endl;
}


#endif
