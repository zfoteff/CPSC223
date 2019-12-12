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
    Node* left;
    Node* right;
    bool is_black;
    bool is_dbl_black_left;
    bool is_dbl_black_right;
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

  //  helper to insert a node into the tree
  Node* insert (const K& key, const V& val, Node* subtree_root);

  //  helper to remove a node from the Tree
  Node* remove (const K& key, Node* parent, Node* subtree_root, bool& found);

  //  helper to perform a single rebalance step on a red-black tree on removed
  Node* remove_color_adjust(Node* subtree_root);

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
RBTCollection<K, V>::~RBTCollection() { make_empty(root); }

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

//  insert helper function
template <typename K, typename V>
typename RBTCollection<K, V>::Node*
RBTCollection<K, V>::insert(const K& key, const V& val, Node* subtree_root)
{
  if (collection_size == 0 || subtree_root == nullptr)
  {
    Node* new_node = new Node;
    new_node->key = key;
    new_node->value = val;
    new_node->is_black = false;
    new_node->left = nullptr;
    new_node->right = nullptr;
    subtree_root = new_node;
  }

  else
  {
    if (key < subtree_root->key)
      subtree_root->left = insert(key, val, subtree_root->left);

    else
      subtree_root->right = insert(key, val, subtree_root->right);
  }

  if (subtree_root->is_black)
  {
    if ((subtree_root->left && !subtree_root->left->is_black) && (subtree_root->right && !subtree_root->right->is_black))
    {
      if (subtree_root->left->left && !subtree_root->left->left->is_black)
      {
        subtree_root->is_black = false;
        subtree_root->left->is_black = true;
        subtree_root->right->is_black = true;
      }

      else if (subtree_root->right->right && !subtree_root->right->right->is_black)
      {
        subtree_root->is_black = false;
        subtree_root->left->is_black = true;
        subtree_root->right->is_black = true;
      }

      else if (subtree_root->left->right && !subtree_root->left->right->is_black)
      {
        subtree_root->is_black = false;
        subtree_root->left->is_black = true;
        subtree_root->right->is_black = true;
      }

      else if (subtree_root->right->left && !subtree_root->right->left->is_black)
      {
        subtree_root->is_black = false;
        subtree_root->left->is_black = true;
        subtree_root->right->is_black = true;
      }
    }

    else
    {
      if ((subtree_root->left && !subtree_root->left->is_black) && (subtree_root->left->left && !subtree_root->left->left->is_black))
      {
        subtree_root = rotate_right(subtree_root);
        subtree_root->is_black = true;
        subtree_root->right->is_black = false;
      }

      else if ((subtree_root->right && !subtree_root->right->is_black) && (subtree_root->right->right && !subtree_root->right->right->is_black))
      {
        subtree_root = rotate_left(subtree_root);
        subtree_root->is_black = true;
        subtree_root->left->is_black = false;
      }

      else if ((subtree_root->left && !subtree_root->left->is_black) && (subtree_root->left->right && !subtree_root->left->right->is_black))
      {
        subtree_root->left = rotate_left(subtree_root->left);
        subtree_root = rotate_right(subtree_root);
        subtree_root->is_black = true;
        subtree_root->right->is_black = false;
      }

      else if ((subtree_root->right && !subtree_root->right->is_black) && (subtree_root->right->left && !subtree_root->right->left->is_black))
      {
        subtree_root->right = rotate_right(subtree_root->right);
        subtree_root = rotate_left(subtree_root);
        subtree_root->is_black = true;
        subtree_root->left->is_black = false;
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

//  remove helper function
template <typename K, typename V>
typename RBTCollection<K, V>::Node*
RBTCollection<K, V>::
remove(const K& key, Node* parent, Node* subtree_root, bool& found)
{
  if (subtree_root && key < subtree_root->key)
    subtree_root = remove(key, subtree_root, subtree_root->left, found);

  else if (subtree_root && key > subtree_root->key)
    subtree_root = remove(key, subtree_root, subtree_root->right, found);

  else if (subtree_root && key == subtree_root->key)
  {
    found = true;

    // leaf node
    if (!subtree_root->left && !subtree_root->right)
    {
      if (parent->left == subtree_root)
      {
        parent->left = nullptr;
        if (subtree_root->is_black)
          parent->is_dbl_black_left = true;
      }

      else
      {
        parent->right = nullptr;
        if (subtree_root->is_black)
          parent->is_dbl_black_right = true;
      }

      delete subtree_root;
    }

    //  left non empty but right empty
    else if (subtree_root->left && !subtree_root->right)
    {
      if (parent->left == subtree_root)
      {
        if (subtree_root->is_black)
          parent->is_dbl_black_left = true;

        parent->left = subtree_root->left;
      }

      else
      {
        if (subtree_root->is_black)
          parent->is_dbl_black_right = true;

        parent->right = subtree_root->left;
      }

      delete subtree_root;
    }

    //  left empty but right non-empty
    else if (!subtree_root->left && subtree_root->right)
    {
      if (parent->right == subtree_root)
      {
        if (subtree_root->is_black)
          parent->is_dbl_black_right = true;

        parent->right = subtree_root->right;
      }

      else
      {
        if (subtree_root->is_black)
          parent->is_dbl_black_left = true;

        parent->left = subtree_root->right;
      }

      delete subtree_root;
    }

    //  left and right non empty
    else
    {
      Node* temp = subtree_root;
      Node* cur = subtree_root->right;

      while (cur->left != nullptr)
      {
        temp = cur;
        cur = cur->left;
      }

      subtree_root->key = cur->key;
      subtree_root->value = cur->value;
      subtree_root = remove (cur->key, subtree_root, subtree_root->right, found);
    }
  }

  if (!found)
    return parent;

  return remove_color_adjust(parent);
}


//  remove a node from the tree
template <typename K, typename V>
void RBTCollection<K, V>::remove(const K& key)
{
  //  check if there is anything to remove
  if (root == nullptr)
    return;
  //  create a fake root to pass in as a parent of root
  Node* root_parent = new Node;
  root_parent->key = root->key;
  root_parent->left = nullptr;
  root_parent->right = root;
  root_parent->is_black = true;
  root_parent->is_dbl_black_left = false;
  root_parent->is_dbl_black_right = false;

  //  call remove
  bool found = false;
  root_parent = remove(key, root_parent, root, found);

  //  update results
  if (found)
  {
    collection_size--;
    root = root_parent->right;

    if (root)
    {
      root->is_black = true;
      root->is_dbl_black_left = false;
      root->is_dbl_black_right = false;
    }
  }

  delete root_parent;
}


//  helper to perform a single reblance step for a red-black Tree
template<typename K, typename V>
typename RBTCollection<K, V>::Node*
RBTCollection<K, V>::remove_color_adjust(Node* subtree_root)
{
  //  subtree_root = grandparent (g)
  Node* g = subtree_root;
  Node* gl = g->left;
  Node* gr = g->right;
  //  parent is either gl or gr
  Node* p = nullptr;
  bool left_parent = false;

  if (gl && (gl->is_dbl_black_left || gl->is_dbl_black_right))
  {
    p = gl;
    left_parent = true;
  }

  else if (gr && (gr->is_dbl_black_left || gr->is_dbl_black_right))
    p = gr;

  // no double black nodes in subtree
  else
    return subtree_root;

  //  Case 1: parent's left child is a double black node
  if (p->is_dbl_black_left)
  {
    //  case 1: sibling is red
    if (!p->right->is_black)
    {
      p = rotate_left(p);
      p->is_black = true;
      p->left->is_black = false;
      p = remove_color_adjust(p);
    }

    //  case 2: sibling's outside child is red
    else if (p->right->right && !p->right->right->is_black)
    {
      p = rotate_left(p);
      p->is_black = p->left->is_black;
      p->right->is_black = true;
      p->left->is_dbl_black_left = false;
      p->left->is_black = true;
    }

    //  case 2: sibling's inside child is red
    if (p->right->left && !p->right->left->is_black)
    {
      p->right = rotate_right(p->right);
      p = rotate_left(p);
      p->is_black = p->left->is_black;
      p->left->is_dbl_black_left = false;
      p->left->is_black = true;
    }

    //  case 3: black sibling with black children - red parent
    else if (!p->is_black)
    {
      p->is_black = true;
      p->right->is_black = false;
      p->is_dbl_black_left = false;
    }

    //  case 3: black sibling with black children - black parent
    else
    {
      p->is_dbl_black_left = false;
      p->right->is_black = false;

      if (left_parent)
        g->is_dbl_black_left = true;

      else
        g->is_dbl_black_right = true;
    }
  }

  //  Case 2: parent's right child is a double black node
  if (p->is_dbl_black_right)
  {
    //  case 1: sibling is red
    if (!p->left->is_black)
    {
      p = rotate_right(p);
      p->is_black = true;
      p->right->is_black = false;
      p = remove_color_adjust(p);
    }

    //  case 2: sibling's outside child is red
    else if (p->left->left && !p->left->left->is_black)
    {
      p = rotate_right(p);
      p->is_black = p->right->is_black;
      p->left->is_black = true;
      p->right->is_dbl_black_right = false;
      p->right->is_black = true;
    }

    //  case 2: sibling's inside child is red
    else if (p->left->right && !p->left->right->is_black)
    {
      p->left = rotate_left(p->left);
      p = rotate_right(p);
      p->is_black = p->right->is_black;
      p->right->is_dbl_black_right = false;
      p->right->is_black = true;
    }

    //  case 3: black sibling with black children - red parent
    else if (!p->is_black)
    {
      p->is_black = true;
      p->left->is_black = false;
      p->is_dbl_black_right = false;
    }

    //  case 3: black sibling with black children - black parent
    else
    {
      p->is_dbl_black_right = false;
      p->left->is_black = false;

      if (left_parent)
        g->is_dbl_black_left = true;

      else
        g->is_dbl_black_right = true;
    }
  }

  //  connect up the subtree_root to the parent
  if (left_parent)
    subtree_root->left = p;
  else
    subtree_root->right = p;

  return subtree_root;
}


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
