/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: hw7_tests.cpp
    Definition for Binary Search Tree (BST) class object
*/

#ifndef RBT_COLLECTION_H
#define RBT_COLLECTION_H

#include <vector>
#include <iostream>
#include "collection.h"

using namespace std;

template <typename K, typename V>
class RBTCollection : public Collection<K, V>
{
public:

  //  constructor
  RBTCollection();

  //  copy constructor
  RBTCollection(const RBTCollection<K, V>& rhs);

  //  assign a linked list
  RBTCollection<K, V>& operator=(const RBTCollection<K, V>& rhs);

  //  destructor
  ~RBTCollection();

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

  //  print the keys in the Tree
  void print() const;

private:

  //  BST node structure
  struct Node
  {
    K key;
    V value;
    bool is_black;
    Node* left;
    Node* right;
  };

  //  pointer to root of tree
  Node* root;


  //  number of kv-pairs in the collection
  int collection_size;

  //  helper to recursively empty the tree
  void make_empty (Node* root);

  //  helper to recursively build sorted list of keys
  void inorder (const Node* subtree, std::vector<K>& ks) const;

  void preorder (const Node* subtree, std::vector<K>& ks) const;

  //  helper to recursively find range of keys
  void range_search (const Node* subtree, const K& k1, const K& k2,
                     std::vector<K>& keys) const;

  //  return the height of the tree rooted at subtree_root
  int height (const Node* subtree_root) const;

  //  insert a node into the
  Node* insert (const K& key, const V& val, Node* subtree_root);

  //  remove a node from the Tree
  Node* remove (const K& key, Node* subtree_root);

  //  helper function to perform single right rotation
  Node* rotate_right (Node* k2);

  //  helper function to perform single left rotation
  Node* rotate_left (Node* k2);
};


template<typename K, typename V>
RBTCollection<K, V>::RBTCollection() :
  collection_size(0), root(nullptr)
{    }


template<typename K, typename V>
RBTCollection<K, V>::RBTCollection(const RBTCollection<K, V>& rhs)
: collection_size(0), root(nullptr)
{
  *this = rhs;
}


template<typename K, typename V>
RBTCollection<K, V>::~RBTCollection()
{
  make_empty(root);
}

template<typename K, typename V>
RBTCollection<K, V>& RBTCollection<K, V>::operator=(const RBTCollection<K, V>& rhs)
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

/*
  Helper Functions
*/
template <typename K, typename V>
void RBTCollection<K, V>::make_empty(Node* subtree_root)
{
  if (subtree_root != nullptr)
  {
    make_empty(subtree_root->left);
    make_empty(subtree_root->right);
    delete subtree_root;
  }
}


template <typename K, typename V>
void RBTCollection<K, V>::inorder(const Node* subtree, std::vector<K>& ks) const
{
  //  recursive helper function
  if (subtree == nullptr)
    return;

  inorder(subtree->left, ks);
  ks.push_back(subtree->key);
  inorder(subtree->right, ks);
}


template <typename K, typename V>
void RBTCollection<K, V>::preorder(const Node* subtree, std::vector<K>& ks) const
{
  //  recursive helper function
  if (subtree == nullptr)
    return;

  ks.push_back(subtree->key);
  inorder(subtree->left, ks);
  inorder(subtree->right, ks);
}


template <typename K, typename V>
void RBTCollection<K, V>::range_search(const Node* subtree, const K& k1,
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
int RBTCollection<K, V>::height(const Node* subtree_root) const
{
  if (subtree_root == nullptr)
    return 0;

  int lhs = 1 + height(subtree_root->left);
  int rhs = 1 + height(subtree_root->right);

  if (lhs > rhs)
    return lhs;

  return rhs;
}


template <typename K, typename V>
typename RBTCollection<K, V>::Node* RBTCollection<K, V>::rotate_left(Node* k2)
{
  Node* new_parent = k2->right;
  k2->right = new_parent->left;
  new_parent->left = k2;
  return new_parent;
}


template <typename K, typename V>
typename RBTCollection<K, V>::Node* RBTCollection<K, V>::rotate_right(Node* k2)
{
  Node* new_parent = k2->left;
  k2->left = new_parent->right;
  new_parent->right = k2;
  return new_parent;
}


template <typename K, typename V>
typename RBTCollection<K, V>::Node*
RBTCollection<K, V>::insert(const K& key, const V& val, Node* subtree_root)
{
  if (collection_size == 0 || subtree_root == nullptr)
  {
    Node* new_node = new Node;
    new_node->key = key;
    new_node->key = val;
    new_node->is_black = false;
    new_node->left = nullptr;
    new_node->right = nullptr;

    subtree_root = new_node;
    return subtree_root;
  }

  if (subtree_root == root)
    return subtree_root;

  else if (subtree_root && key < subtree_root->key)
  {
    subtree_root->left = insert(key, val, subtree_root->left);

    //  if the parent node is black, no rotations needed
    if (subtree_root->left->is_black)
      return subtree_root;

    //  if the parent node is red
    else if (!subtree_root->left->is_black)
    {
      //  if parent's sibling is red (recolor)
      if (subtree_root->right && !subtree_root->is_black)
      {
        subtree_root->left->is_black = true;
        subtree_root->right->is_black = true;
        subtree_root->is_black = false;
        return subtree_root;
      }

      //  if sibling is black or null
      else if (subtree_root->right->is_black || subtree_root->right == nullptr)
      {
        //  if the insert is an outside grandchild (left-left)
        if (!subtree_root->left->left->is_black
            && (subtree_root->left->right == nullptr
            || subtree_root->left->right->is_black)
           )
        {
          subtree_root = rotate_right(subtree_root);
          subtree_root->is_black = true;
          subtree_root->right->is_black = false;
          return subtree_root;
        }

        //  if the insert is an inside grandchild (left-right)
        else if (!subtree_root->left->right->is_black && (subtree_root->left->left->is_black || subtree_root->left->left == nullptr) && subtree_root->left->left->is_black)
        {
          subtree_root->left = rotate_left(subtree_root->left);
          subtree_root->left->is_black = true;
          subtree_root->is_black = false;
          subtree_root = rotate_right(subtree_root);
          return subtree_root;
        }
      }
    }
  }

  else if (subtree_root && key > subtree_root->key)
  {
    subtree_root->right = insert(key, val, subtree_root->right);

    //  if the parent node is black, no rotations needed
    if (subtree_root->right->is_black)
      return subtree_root;

    //  if parent node is red
    else if (!subtree_root->right->is_black)
    {
      //  if parent's sibling is red (recolor)
      if (subtree_root->left && !subtree_root->left->is_black)
      {
        subtree_root->left->is_black = true;
        subtree_root->right->is_black = true;
        subtree_root->is_black = false;
        return subtree_root;
      }

      //  if sibling is black or null
      else if (subtree_root->left->is_black || subtree_root->left == nullptr)
      {
        //  if insert is outside grandchild (rihgt-right)
        if (!subtree_root->right->right->is_black
            && (subtree_root->right->left == nullptr
            || subtree_root->right->left->is_black )
           )
        {
          subtree_root = rotate_left(subtree_root);
          subtree_root->is_black = true;
          subtree_root->left->is_black = false;
          return subtree_root;
        }

        //  if insert is inside grandchild (right-left)
        else if (!subtree_root->right->left->is_black && (subtree_root->right->right == nullptr || subtree_root->right->right->is_black))
        {
          subtree_root->right = rotate_right(subtree_root->right);
          subtree_root->right->is_black = true;
          subtree_root->is_black = false;
          subtree_root = rotate_left(subtree_root);
          return subtree_root;
        }
      }
    }
  }

  return subtree_root;
}


//  insert new node into the tree
template<typename K, typename V>
void RBTCollection<K, V>::insert(const K& key, const V& val)
{
  root = insert(key, val, root);
  root->is_black = true;
  collection_size++;
}

template <typename K, typename V>
typename RBTCollection<K, V>::Node*
RBTCollection<K, V>::remove(const K& key, Node* subtree_root)
{
  if (subtree_root && key < subtree_root->key)
    subtree_root->left = remove(key, subtree_root->left);

  else if (subtree_root && key > subtree_root->key)
    subtree_root->right = remove(key, subtree_root->right);

  else if (subtree_root && key == subtree_root->key)
  {
    //  if subtree_root has no children
    if (subtree_root->left == nullptr && subtree_root->right == nullptr)
    {
      subtree_root = nullptr;
      collection_size--;
    }

    //  if subtree has a left child but no right child
    else if (subtree_root->left != nullptr && subtree_root->right == nullptr)
    {
      K k = subtree_root->left->key;
      V v = subtree_root->left->value;
      Node* new_left = subtree_root->left->left;
      remove(key, subtree_root->left);
      subtree_root->key = k;
      subtree_root->value = v;
      subtree_root->left = new_left;
      collection_size--;
      return subtree_root;
    }

    //  if subtree root has a right child but not a left child
    else if (subtree_root->left == nullptr && subtree_root->right != nullptr)
    {
      K k = subtree_root->right->key;
      V v = subtree_root->right->value;
      Node* new_right = subtree_root->right->right;
      remove(key, subtree_root->right);
      subtree_root->key = k;
      subtree_root->value = v;
      subtree_root->right = new_right;
      collection_size--;
      return subtree_root;
    }

    //  if the subtree has two children
    else if (subtree_root->left != nullptr && subtree_root->right != nullptr)
    {
      Node* cur = new Node;
      cur = subtree_root;
      while(cur->left != nullptr)
        cur = cur->left;

      K k = cur->key;
      V v = cur->value;
      remove(key, cur);
      cur = nullptr;
      subtree_root->key = k;
      subtree_root->value = v;
      collection_size--;
      return subtree_root;
    }
  }

  return subtree_root;
}


template <typename K, typename V>
void RBTCollection<K, V>::remove(const K& key)
{ root = remove(key, root); }


/*
  Collection Functions
*/
template <typename K, typename V>
bool RBTCollection<K, V>::find(const K& key, V& val) const
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
void RBTCollection<K, V>::find(const K& k1, const K& k2, std::vector<K>& ks) const
{
  //  recursive helper function
  range_search(root, k1, k2, ks);
}


template <typename K, typename V>
void RBTCollection<K, V>::keys(std::vector<K>& ks) const { inorder(root, ks); }


template <typename K, typename V>
void RBTCollection<K, V>::sort(std::vector<K>& ks) const { inorder(root, ks); }


template <typename K, typename V>
int RBTCollection<K, V>::size() const { return collection_size; }


template <typename K, typename V>
int RBTCollection<K, V>::height() const { return height(root); }


template <typename K, typename V>
void RBTCollection<K, V>::print() const
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
