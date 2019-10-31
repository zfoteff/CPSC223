#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <vector>
#include <string>
#include <algorithm>
#include "collection.h"

using namespace std;

template<typename K, typename V>
class LinkedListCollection : public Collection<K, V>
{
public:

  //  DVC
  LinkedListCollection();

  //  Copy constuctor
  LinkedListCollection(const LinkedListCollection<K, V>& rhs);

  //  Assignment operator
  LinkedListCollection<K, V>& operator=(const LinkedListCollection<K, V>& rhs);

  //  Deleting Linked List
  ~LinkedListCollection();

  //  Insert new key-value pair into the collection
  void insert(const K& key, const V& val);

  //  remove a key-value pair from the collection
  void remove(const K& key);

  //  Find the value associated with the key
  bool find(const K& key, V& val) const;

  //  Find the keys associated with the range
  void find(const K& k1, const K& k2, std::vector<K>& keys) const;

  //  Return all keys in the Collection
  void keys(std::vector<K>& keys) const;

  //  Sorts the collection and passes the sorted list as a vector
  void sort(std::vector<K>& keys) const;

  //  Return the number of keys in the Collection
  int size() const;

  //  In place sorting
  void insertion_sort();
  void merge_sort();
  void quick_sort();

private:
  //  Linked list structure
  struct Node
  {
    K key;
    V value;
    Node* next;
  };

  Node* head;
  Node* tail;
  int length;

  //  merge sort Helper
  Node* merge_sort(Node* left, int len);
  //  quick sort HelperLinkedList key-value pair collection
  Node* quick_sort(Node* start, int len);
};


//  Constructor for a LinkedList key-value pair collection
template<typename K, typename V>
LinkedListCollection<K, V>::LinkedListCollection()
{
  head = nullptr;
  tail = nullptr;
  length = 0;
}



//  Copy Constructor for LinkedList key-value pair collection
template<typename K, typename V>
LinkedListCollection<K, V>::
LinkedListCollection(const LinkedListCollection<K, V>& rhs)
{
   *this = rhs;
}


//  Assignment copy operator for LinkedList key-value pair collection
template<typename K, typename V>
LinkedListCollection<K, V>& LinkedListCollection<K, V>
::operator=(const LinkedListCollection<K, V>& rhs)
{
  if (&rhs != this)
  {
    Node* temp = this->head;
    while(temp->next != nullptr)
    {
      temp = temp->next;
      delete temp;
      temp = head;
    }
    delete this->head;
    this->length = 0;

    temp = rhs.head;
    while(temp != nullptr)
    {
      this->insert(temp->key, temp->value);
      temp = temp->next;
    }
  }

  return *this;
}


//  Destructor for LinkedList key-value pair collection
template<typename K, typename V>
LinkedListCollection<K, V>::~LinkedListCollection()
{
  Node* cur = head;
  while (cur != nullptr)
  {
    Node* next = cur->next;
    delete cur;
    cur = next;
  }

  head = nullptr;
}


//  Method inserts a new node into LinkedList key-value pair collection
template<typename K, typename V>
void LinkedListCollection<K, V>::insert(const K& key, const V& val)
{
  Node* new_insert = new Node;
  new_insert->key = key;
  new_insert->value = val;

  if (length == 0)
  {
    head = new_insert;
    tail = new_insert;
    new_insert->next = nullptr;
    this->length++;
    return;
  }

  tail->next = new_insert;
  new_insert->next = nullptr;
  tail = new_insert;
  length++;
}


//  Method removes specified node from the LinkedList key-value pair collection
template<typename K, typename V>
void LinkedListCollection<K, V>::remove(const K& key)
{
  Node* last = new Node;
  Node* cur = head;

  while (cur != nullptr)
  {
    if (cur->key == key)
    {
      last->next = cur->next;
      delete cur;
      this->length--;
      break;
    }

    last = cur;
    cur = cur->next;
  }
}


//  Method finds a node with a specified key LinkedList key-value pair collectionand returns the value of that
//  key by reference
template<typename K, typename V>
bool LinkedListCollection<K, V>::find(const K& key, V& val) const
{
  Node* cur = head;
  while (cur != nullptr)
  {
    if(cur->key == key)
    {
      val = cur->value;
      return true;
    }

    cur = cur->next;
  }

  return false;
}


//  Methods finds all nodes in the range [k1, k2] and returns a vector of keys
//  by reference
template<typename K, typename V>
void LinkedListCollection<K, V>
::find(const K& k1, const K& k2, std::vector<K>& keys) const
{
  Node* cur = head;

  while (cur != nullptr)
  {
    if (cur->key >= k1 && cur->key <= k2)
      keys.push_back(cur->key);

    cur = cur->next;
  }
}


//  Method finds all the keys in the LinkedList key-value pair collection and
//  returns a vector of the keys by reference
template<typename K, typename V>
void LinkedListCollection<K, V>::keys(std::vector<K>& keys) const
{
  Node* cur = head;
  while(cur != nullptr)
  {
    keys.push_back(cur->key);
    cur = cur->next;
  }
}


//  Methods sorts all of keys in the list and returns a vector of the keys
//  by reference
template<typename K, typename V>
void LinkedListCollection<K, V>::sort(std::vector<K>& keys) const
{
  Node* cur = head;
  while (cur != nullptr)
  {
    keys.push_back(cur->key);
    cur = cur->next;
  }

  std::sort(keys.begin(), keys.end());
}


//  Method returns an int representing the size of the array
template<typename K, typename V>
int LinkedListCollection<K, V>::size() const
{
  return length;
}


//  In place insertion sort for linked lists
template<typename K, typename V>
void LinkedListCollection<K, V>::insertion_sort()
{
  Node* sortStart;
  Node* cur = head;

  for (int i = 1; i < length; ++i)
  {
    bool go = false;
    sortStart = head;

    //  Traverse sorted region
    while (!go && sortStart != cur->next)
    {
      go = false;

      //
      if (cur->next->key < head->key)
      {
        Node* temp = cur->next;
        cur->next = cur->next->next;
        temp->next = head;
        head = temp;
        go = true;
      }

      //
      else if (cur->next->key < sortStart->next->key)
      {
        Node* temp = cur->next;
        cur->next = cur->next->next;
        temp->next = sortStart->next;
        sortStart->next = temp;
        go = true;
      }

      else
        sortStart = sortStart->next;
    }

    if (!go)
      cur = cur->next;
  }
}


//  In place merge sort method for linked lists
template<typename K, typename V>
void LinkedListCollection<K, V>::merge_sort()
{
  head = merge_sort(this->head, this->length);
  tail = head;
  while (tail->next != nullptr)
    tail = tail->next;
}


//  Helper function for merging lists together
template<typename K, typename V>
typename LinkedListCollection<K, V>::Node*
LinkedListCollection<K, V>::merge_sort(Node* left, int len)
{
  if (length == 1)
    return left;

  Node* temp = left;
  Node* right;
  Node* newHead;
  int mid = len/2;
  int count = 0;

  //  all the nodes that belong to the left list are seperated
  while (count < mid-1)
  {
    temp = temp->next;
    count++;
  }
  right = temp->next;

  //  recursive sort calls
  left = merge_sort(left, mid);
  right = merge_sort(right, len-mid);

  //  reconnecting
  if (left->key < right->key)
  {
    newHead = left;
    left = left->next;
    newHead->next = nullptr;
  }

  else
  {
    newHead = right;
    right = right->next;
    newHead->next = nullptr;
  }

  temp = newHead;
  for (int i = 0; i < len-1; ++i)
  {
    //  left base case
    if (left == nullptr)
    {
      temp->next = right;
      right = right->next;
      temp->next->next = nullptr;
      temp = temp->next;
    }

    //  right base case
    else if (right == nullptr)
    {
      temp->next = left;
      left = left->next;
      temp->next->next = nullptr;
      temp = temp->next;
    }

    //  left-right comparisons
    else if (left->key < right->key)
    {
      temp->next = left;
      left = left->next;
      temp->next->next = nullptr;
      temp = temp->next;
    }

    else
    {
      temp->next = right;
      right = right->next;
      temp->next->next = nullptr;
      temp = temp->next;
    }
  }

  return newHead;
}


//  In place quick sort for linked lists
template<typename K, typename V>
void LinkedListCollection<K, V>::quick_sort()
{
  head = quick_sort(head, length);
  tail = head;
  while (tail->next != nullptr)
    tail = tail->next;
}


//  Helper function for quick sort method
template<typename K, typename V>
typename LinkedListCollection<K, V>::Node*
LinkedListCollection<K, V>::quick_sort(Node* start, int len)
{
  Node* cur = start->next;
  Node* left = new Node;
  Node* right = new Node;
  Node* left_end;
  Node* right_end;
  int left_length = 0;
  int right_length = 0;

  //  Base cases
  if (len <= 1)
    return start;

  if (len == 2)
  {
    if (start->key > start->next->key)
    {
      Node* temp = start;
      start = start->next;
      start->next = temp;
      return start;
    }
  }

  while (cur != nullptr)
  {
    if (cur->key < start->key && left == nullptr)
      left = cur;
    if (cur->key >= start->key && right == nullptr)
      right = cur;

    cur = cur->next;
  }

  cur = start->next;
  start->next = nullptr;
  left_end = left;
  right_end = right;

  //  traverse all items after the 1st (pivot element) and assign them to the
  //  right or left nodes
  while (cur != nullptr)
  {
    if (left != nullptr)
    {
      if (cur->key < start->key && cur != left)
      {
        left_end->next = cur;
        left_end = left_end->next;
      }
    }

    if (right != nullptr)
    {
      if (cur->key >= start->key && cur != right)
      {
        right_end->next = cur;
        right_end = right_end->next;
      }
    }

    cur = cur->next;
  }

  if (left_end != nullptr)
    left_end->next = nullptr;
  if (right_end != nullptr)
    right_end->next = nullptr;

  //  find lengths of the two nodes
  cur = left;
  if (left != nullptr)
  {
    while (cur != nullptr)
    {
      left_length++;
      cur = cur->next;
    }
  }

  cur = right;
  if (right != nullptr)
  {
    while (cur != nullptr)
    {
      right_length++;
      cur = cur->next;
    }
  }

  //  recursively call quicksort until nodes of only nodes of length 1 exist
  if (left != nullptr)
    left = quick_sort(left, left_length);
  if (right != nullptr)
   right = quick_sort(right, right_length);

  //  Reconnect nodes
  if (left != nullptr)
  {
    cur = left;
    while (cur->next != nullptr)
        cur = cur->next;

    left_end = cur;
    left_end->next = start;
    start->next = right;
    return left;
  }

  if (left == nullptr)
  {
    start->next = right;
    return start;
  }
}


#endif
