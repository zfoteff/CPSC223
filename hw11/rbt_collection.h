/*
Weston Averill
CPSC223
HW11
Red Black Tree Remove Implementation
*/

#ifndef RBT_COLLECTION_H
#define RBT_COLLECTION_H

#include <vector>
#include "collection.h"
#include <cmath>

 template<typename K, typename V>
 class RBTCollection : public Collection<K,V>
 {
 public:

 // create an empty linked list
 RBTCollection();

 // copy a linked list
 RBTCollection(const RBTCollection<K,V>& rhs);

 // assign a linked list
 RBTCollection<K,V>& operator=(const RBTCollection<K,V>& rhs);


 // delete a linked list
 ~RBTCollection();

 // insert a key - value pair into the collection
 void insert(const K& key, const V& val);

 // remove a key - value pair from the collection
 void remove(const K& key);

 // find the value associated with the key
 bool find(const K& key, V& val) const;

 // find the keys associated with the range
 void find(const K& k1, const K& k2 , std :: vector <K >& keys ) const ;

 // return all keys in the collection
 void keys(std::vector<K>& keys) const;

 // return collection keys in sorted order
 void sort(std::vector<K>& keys) const;

 // return the number of keys in collection
 int size() const;

 // return the height of the tree
 int height() const;

 // optional print function ( for testing )
 void print() const;

 private:

 // binary search tree node structure
 struct Node{
 K key;
 V value;
 Node* left;
 Node* right;
 bool is_black; // true if black , false if red
 bool is_dbl_black_left; // for remove rotations
 bool is_dbl_black_right; // for remove rotations
 };
 
 void print(Node* subtree, std::vector<std::pair<K,bool>>& ks) const;

 // root node of the search tree
 Node* root;

 // number of k-v pairs in the collection
 int collection_size;

 // helper to recursively empty search tree
 void make_empty(Node* subtree_root);


 // recursive helper to remove node with given key
 Node* remove(const K& key, Node* parent, Node* subtree_root, bool& found);

 // helper to perform a single rebalance step on a red - black tree on remove
 Node* remove_color_adjust(Node* parent);

 // recursive helper to do red - black insert key - val pair ( backtracking )
 Node* insert(const K& key, const V& val, Node* subtree_root);

 // helper functions to perform a single right rotation
 Node* rotate_right(Node* k2);

 // helper functions to perform a single left rotation
 Node* rotate_left(Node* k2);

 // helper to recursively build sorted list of keys
 void inorder(const Node* subtree, std::vector<K>& keys) const;

 // helper to recursively build sorted list of keys
 void preorder(const Node* subtree, std::vector<K>& keys) const;

 // helper to recursively find range of keys
 void range_search(const Node* subtree_root, const K& k1, const K& k2,
 std::vector<K>& keys) const;

 // return the height of the tree rooted at subtree_root
 int height(const Node* subtree_root) const;

 };
 
 template<typename K, typename V>
 RBTCollection<K,V>::RBTCollection() :
  collection_size(0) , root(nullptr)
 {
 }

 template<typename K, typename V>
 void RBTCollection<K,V>::make_empty(Node* subtree_root)
 {
  //cout << "here in destructer" << endl;
  if (subtree_root)
  {
   make_empty(subtree_root->left);
   make_empty(subtree_root->right);
   delete subtree_root;
   root = nullptr;
   collection_size--;
  }
 }

 template<typename K, typename V>
 RBTCollection<K,V>::~RBTCollection()
 {
  make_empty(root);
 }
 
 template<typename K, typename V>
 RBTCollection<K,V>::RBTCollection(const RBTCollection<K,V>& rhs)
 : collection_size(0), root(nullptr)
 {
  *this = rhs;
 }
 
 template<typename K, typename V>
 RBTCollection<K,V>& RBTCollection<K,V>::operator=(const RBTCollection<K,V>& rhs)
 {
 if (this == &rhs)
  return *this;
 // delete current
 make_empty(root);
 // build tree
 std::vector<K> ks;
 preorder (rhs.root, ks);
 for (K key : ks)
 {
  V val;
  rhs.find(key, val);
  insert(key, val);
 }
 return *this;
 }
 
 template<typename K, typename V>
 typename RBTCollection<K,V>::Node* RBTCollection<K,V>::rotate_right(Node* k2)
 {
  Node* k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  return k1;
 }

 template<typename K, typename V>
 typename RBTCollection<K,V>::Node* RBTCollection<K,V>::rotate_left(Node* k2)
 {
  Node* k1 = k2->right;
  k2->right = k1->left;
  k1->left = k2;
  return k1;
 }
 
 template<typename K, typename V>
 typename RBTCollection<K,V>::Node*
 RBTCollection<K,V>::insert(const K& key, const V& val, Node* subtree_root)
 {
 if (subtree_root == nullptr)
 {
  Node* insertN = new Node;
  insertN->is_black = false;
  insertN->is_dbl_black_left = false;
  insertN->is_dbl_black_right = false;
  insertN->key = key;
  insertN->value = val;
  insertN->left = nullptr;
  insertN->right = nullptr;
  subtree_root = insertN;
 }
 
 else
 {
  if (key < subtree_root->key)
  {
   subtree_root->left = insert(key, val, subtree_root->left);
  }
  else 
  {
   subtree_root->right = insert(key, val, subtree_root->right);
  }
 }
 
  if (subtree_root->is_black)
  {
   if ((subtree_root->left && !subtree_root->left->is_black) && (subtree_root->right &&!subtree_root->right->is_black))
   {
   //case 1 if parent has a sibling that is a red node
    //left left recolor
    if (subtree_root->left->left && !subtree_root->left->left->is_black)
    {
     subtree_root->is_black = false;
     subtree_root->left->is_black = true;
     subtree_root->right->is_black = true;
    }
    
    //left right recolor
    else if (subtree_root->left->right && !subtree_root->left->right->is_black)
    {
     subtree_root->is_black = false;
     subtree_root->left->is_black = true;
     subtree_root->right->is_black = true;
    }
    
    //right left recolor
    else if (subtree_root->right->left && !subtree_root->right->left->is_black)
    {
     subtree_root->is_black = false;
     subtree_root->left->is_black = true;
     subtree_root->right->is_black = true;
    }
   
   //right right recolor
    else if (subtree_root->right->right && !subtree_root->right->right->is_black)
    {
     subtree_root->is_black = false;
     subtree_root->left->is_black = true;
     subtree_root->right->is_black = true;
    }
   }
   
   //case 2 and case 3
   else 
   {
    if ((subtree_root->left && !subtree_root->left->is_black) && (subtree_root->left->left && !subtree_root->left->left->is_black))
    {
     //single rotate right
     subtree_root = rotate_right(subtree_root);
     subtree_root->is_black = true;
     subtree_root->right->is_black = false;
    }
    
    else if ((subtree_root->right && !subtree_root->right->is_black) && (subtree_root->right->right && !subtree_root->right->right->is_black))
    {
     //single rotate left
     subtree_root = rotate_left(subtree_root);
     subtree_root->is_black = true;
     subtree_root->left->is_black = false;
    }
    
    else if ((subtree_root->left && !subtree_root->left->is_black) && (subtree_root->left->right && !subtree_root->left->right->is_black))
    {
     //left right double rotation
     subtree_root->left = rotate_left(subtree_root->left);
     subtree_root = rotate_right(subtree_root);
     subtree_root->is_black = true;
     subtree_root->right->is_black = false;
    }
    
    else if ((subtree_root->right && !subtree_root->right->is_black) && (subtree_root->right->left && !subtree_root->right->left->is_black))
    {
     //right left double rotation
     subtree_root->right = rotate_right(subtree_root->right);
     subtree_root = rotate_left(subtree_root);
     subtree_root->is_black = true;
     subtree_root->left->is_black = false;
    }
    
   }
  }
 return subtree_root;
 }


 template<typename K, typename V>
 void RBTCollection<K,V>::insert(const K& key, const V& val)
 {
 root = insert(key, val, root);
 root->is_black = true;
 collection_size++;
 }

 template<typename K, typename V>
 void RBTCollection<K,V>::remove(const K& key)
 {
 // check if anything to remove
 if (root == nullptr)
 return;
 // create a " fake " root to pass in as parent of root
 Node* root_parent = new Node;
 root_parent->key = root->key;
 root_parent->left = nullptr;
 root_parent->right = root;
 root_parent->is_black = true;
 root_parent->is_dbl_black_left = false;
 root_parent->is_dbl_black_right = false;
 // call remove
 bool found = false;
 root_parent = remove(key, root_parent, root, found);
 // update results
 if (found){
 collection_size--;
 root = root_parent->right;

 if (root){
 root->is_black = true;
 root->is_dbl_black_right = false;
 root->is_dbl_black_left = false;
  }
 }
 delete root_parent;
 }


 template<typename K, typename V>
 typename RBTCollection<K,V>::Node*
 RBTCollection<K,V>::remove(const K& key, Node* parent, Node* subtree_root,
 bool& found)
 {
 if (subtree_root && key < subtree_root->key)
 subtree_root = remove(key, subtree_root, subtree_root->left, found);
 else if (subtree_root && key > subtree_root->key)
 subtree_root = remove(key, subtree_root, subtree_root->right, found);
 else if (subtree_root && key == subtree_root->key){
 found = true;
 // leaf node
  if (!subtree_root->left && !subtree_root->right){
  // if node is black then set double -black , adjust parent ,
  // and delete subtree root ...
   if (parent->left == subtree_root)
   {
    parent->left = nullptr;
    if (subtree_root->is_black)
    {
     parent->is_dbl_black_left = true;
    }
   }
   else 
   {
    parent->right = nullptr;
    if (subtree_root->is_black)
    {
     parent->is_dbl_black_right = true;
    }
   }
   delete subtree_root;
  }
  // left non - empty but right empty
  else if (subtree_root->left && !subtree_root-> right) {
  // similar to above
   if (parent->left == subtree_root)
   { 
    if (subtree_root->is_black)
    {
     parent->is_dbl_black_left = true;
    }
    parent->left = subtree_root->left;
   }
   else
   {
    if (subtree_root->is_black)
    {
     parent->is_dbl_black_right = true;
    }
    parent->right = subtree_root->left;
   }
   delete subtree_root;
  }
  // left empty but right non - empty
  else if (!subtree_root->left && subtree_root->right) {
  // similar to avove
   if (parent->right == subtree_root)
   {
    if (subtree_root->is_black)
    {
     parent->is_dbl_black_right = true;
    }
    parent->right = subtree_root->right;
   }
   else
   {
    if (subtree_root->is_black)
    {
     parent->is_dbl_black_left = true;
    }
    parent->left = subtree_root->right;
   }
   delete subtree_root;
  }
  // left and right non empty
  else {
  // find inorder successor (right , then iterate left )
  // then call remove again on inorder successor key and subtree root’s
  // right child once the key and value copy is complete
    Node* temp = subtree_root;
    Node* cur = subtree_root->right;
    while (cur->left != nullptr)
    {
     temp = cur;
     cur = cur->left;
    }
    
    subtree_root->key = cur->key;
    subtree_root->value = cur->value;
    
    subtree_root = remove(cur->key, subtree_root, subtree_root->right, found);
  }
 }

 if (!found)
  return parent;

 // backtracking , adjust color at parent
 return remove_color_adjust(parent);
 }


 template<typename K, typename V>
 typename RBTCollection<K,V>::Node*
 RBTCollection<K,V>::remove_color_adjust(Node* subtree_root)
 {
 // subtree root is " grandparent " g, with left child gl and right child gr
 Node* g = subtree_root;
 Node* gl = g->left;
 Node* gr = g->right;
 // parent p is either gl or gr
 Node* p = nullptr;
 bool left_parent = false;
 if (gl && (gl->is_dbl_black_left || gl->is_dbl_black_right)) {
  p = gl;
  left_parent = true;
 }
 else if (gr && (gr->is_dbl_black_left || gr->is_dbl_black_right))
  p = gr;
 else
 {
  //std::cout <<  (subtree_root ? subtree_root->key : K()) << " no doublel" << std::endl;
  return subtree_root;
 }
  
 // parent ’s left child is a double black node
 if (p->is_dbl_black_left) {
 // case 1: red sibling
   if (!p->right->is_black)
   {
    p = rotate_left(p);
    p->is_black = true;
    p->left->is_black = false;
    p = remove_color_adjust(p);
    //p->left->is_dbl_black_left = true;
   }
  
    // case 2: black sibling with red child ( outside )
    else if (p->right->right && !p->right->right->is_black)
    {
     p = rotate_left(p);
     p->is_black = p->left->is_black;
     p->right->is_black = true;
     p->left->is_dbl_black_left = false;
     p->left->is_black = true;
    }
    
    // case 2: black sibling with red child ( inside )
    else if (p->right->left && !p->right->left->is_black)
    {
     p->right = rotate_right(p->right);
     p = rotate_left(p);
     p->is_black = p->left->is_black;
     p->left->is_dbl_black_left = false;
     p->left->is_black = true;
    }
    
    // case 3: black sibling with black children , red parent
    else if (!p->is_black)
    {
     p->is_black = true;
     p->right->is_black = false;
     p->is_dbl_black_left = false;
    }
    
   else
   {
    
    // case 3: black sibling with black children , black parent
     p->is_dbl_black_left = false;
     p->right->is_black = false;
     if (left_parent)
     {
      g->is_dbl_black_left = true;
     }
     else 
     {
      g->is_dbl_black_right = true;  
     }
   }
  }   
  
 // parent ’s right child is a double black node
 if (p->is_dbl_black_right) {
  
   if (!p->left->is_black) 
   {
    p = rotate_right(p);
    p->is_black = true;
    p->right->is_black = false;
    p = remove_color_adjust(p); //rebalance at p again
   }
  
    // case 2: black sibling with red child ( outside )
    else if (p->left->left && !p->left->left->is_black)
    {
     p = rotate_right(p);
     p->is_black = p->right->is_black;
     p->left->is_black = true;
     p->right->is_dbl_black_right = false;
     p->right->is_black = true;
    }
    
    // case 2: black sibling with red child ( inside )
    else if (p->left->right && !p->left->right->is_black)
    {
     p->left = rotate_left(p->left);
     p = rotate_right(p);
     p->is_black = p->right->is_black;
     p->right->is_dbl_black_right = false;
     p->right->is_black = true;
    }
    
    // case 3: black sibling with black children , red parent
    else if (!p->is_black)
    {
     p->is_black = true;
     p->left->is_black = false;
     p->is_dbl_black_right = false;
    }
    
   else
   {
    // case 3: black sibling with black children , black parent
     p->is_dbl_black_right = false;
     p->left->is_black = false;
     if (left_parent)
     {
      g->is_dbl_black_left = true;
     }
     else 
     {
      g->is_dbl_black_right = true;
     }
   }
 }

 // connect up the subtree_root to the parent
 if (left_parent)
 subtree_root->left = p;
 else
 subtree_root->right = p;
 return subtree_root;
 }

template<typename K, typename V>
 bool RBTCollection<K,V>::find(const K& key, V& val) const
 {
 
  Node* cur = root;
  while (cur != nullptr)
  {
   if (key == cur->key)
   { 
    val = cur->value;
    return true;
   }
   else if (key < cur->key)
   {
    cur = cur->left;
   }
   else
   {
    cur = cur->right;
   }
  }
  return false;
 }
 
 template<typename K, typename V> void RBTCollection<K,V>::range_search(const Node* subtree, const K& k1, const K& k2, std::vector<K>& ks) const
 { 
   if (subtree == nullptr)
   { 
    return;
   }
   
   if (subtree->key < k1)
   {
    range_search(subtree->right, k1, k2, ks);
   }
   
   if (k1 <= subtree->key && k2 >= subtree->key)
   {
    range_search(subtree->left, k1, k2, ks);
    range_search(subtree->right, k1, k2, ks);
    ks.push_back(subtree->key);
   }
   
   if (subtree->key > k2)
   {
    range_search(subtree->left, k1, k2, ks);
   }
 }


 template<typename K, typename V> void RBTCollection<K,V>::find(const K& k1, const K& k2, std::vector<K>& ks) const
 {
 // defer to the range search ( recursive ) helper function
 range_search(root, k1, k2, ks);
 }

 template<typename K, typename V> void RBTCollection<K,V>::inorder(const Node* subtree, std::vector<K>& ks) const
 {
  if (subtree == nullptr)
   return;
  inorder(subtree->left, ks);
  ks.push_back(subtree->key);
  //cout << subtree->key << "," << subtree->is_black << " ";
  inorder(subtree->right, ks);
 }

 template<typename K, typename V> 
 void RBTCollection<K,V>::preorder(const Node* subtree, std::vector<K>& ks) const
 {
  if (subtree == nullptr)
   return;
   
  ks.push_back(subtree->key);
  preorder(subtree->left, ks);
  preorder(subtree->right, ks);
 }
 
 template<typename K, typename V>
 void RBTCollection<K,V>::keys(std::vector<K>& ks) const
 {
 // defer to the inorder ( recursive ) helper function
  inorder(root, ks);
 }

 template<typename K, typename V>
 void RBTCollection<K,V>::sort(std::vector<K>& ks) const
 {
 // defer to the inorder ( recursive ) helper function
  inorder(root, ks);
 }


 template<typename K, typename V>
 int RBTCollection<K,V>::size() const
 {
  return collection_size;
 }
 
 template<typename K, typename V>
 int RBTCollection<K,V>::height(const Node* subtree_root) const
 {
  if (subtree_root == nullptr)
   return 0;
   
  int leftHeight = 1+height(subtree_root->left);
  int rightHeight = 1+height(subtree_root->right);
  
  if (leftHeight < rightHeight)
   return rightHeight;
   
  return leftHeight;
 }

 template<typename K, typename V>
 int RBTCollection<K,V>::height() const
 {
 // defer to the height ( recursive ) helper function
  return height(root);
 }
 
 
// optional print function ( for testing )
template<typename K,typename V>
void RBTCollection<K,V>::print() const
{
	std::vector<std::pair<K,bool>> ks;
	print(root, ks);
	std::cout << std::endl;
	for(int i = 0; i < ks.size(); i++)
	{
		for(int j = 0; j <= std::floor(std::log2(ks.size())) - std::floor(std::log2(i+1)); j++)
		{
			std::cout << " ";
		}
		std::cout << ks[i].first << " " << ks[i].second << std::endl;
	}
	std::cout << std::endl;
}

template<typename K,typename V>
void RBTCollection<K,V>::print(Node* subtree, std::vector<std::pair<K,bool>>& ks) const
{
if(subtree)
{
	std::vector<std::pair<K,bool>> left_ks, right_ks;
	print(subtree->left, left_ks);
	print(subtree->right, right_ks);
	int size = std::max(left_ks.size(), right_ks.size());
	for(int i = left_ks.size(); i < size; i++)
	{
		left_ks.push_back(std::pair<K,bool>(K(), 1));
	}
	for(int i = right_ks.size(); i < size; i++)
	{
		right_ks.push_back(std::pair<K,bool>(K(), 1));
	}
	ks.push_back(std::pair<K,bool>(subtree->key, subtree->is_black));
	for(int i = 0,k = 0; i < size; k++)
	{
		for(int j = 0; j < std::pow(2,k); j++)
		{
			ks.push_back(std::pair<K,bool>(left_ks[0].first, left_ks[0].second));
			i++;
			left_ks.erase(left_ks.begin());
		}
		for(int j = 0; j < std::pow(2,k); j++)
		{
			ks.push_back(std::pair<K,bool>(right_ks[0].first, right_ks[0].second));
			i++;
			right_ks.erase(right_ks.begin());
		}
	}
}
}


#endif
