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

  //  helper to delete linked list
  void make_empty();
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
  Node* cur = rhs.head;
  while (cur != nullptr)
  {
    this->insert(cur->key, cur->value);
    cur = cur->next;
  }
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
  if (head->next = nullptr)
    return;

  Node* sortStart = head;
  Node* sortEnd = head;
  Node* cur = sortEnd->next;
  Node* iter;
  Node* iterTail;
  Node* temp;

  if (sortStart == sortEnd)
  {
    /*
    When the list is first passed it, this case creates a 2 element sorted
    region that can be iterated through easily with a while loop
    */

    if (cur->next != nullptr)
      iter = cur->next;

    if (sortStart->value > cur->value)
    {
      cur->next = sortStart;
      sortStart->next = iter;
      sortEnd = sortStart;
      sortStart = cur;
    }

    else
      sortEnd = cur;

    cur = sortEnd->next;
  }

  /*
  Checks each element in sorted region to see if it is greater than cur, then
  inserts the unsorted node into its correct position in the sorted region
  */
  while (cur != nullptr)
  {
    if (sortStart->value > cur->value)
    {
      temp = cur->next;
      cur->next = sortStart;
      sortStart = cur;
      cur = temp;
      continue;
    }

    temp = cur->next;
    iterTail = sortStart;
    iter = sortStart->next;

    while (iter != sortEnd)
    {
      if (iter->value > cur->value)
      {
        temp = cur->next;
        iterTail->next = cur;
        cur->next = iter;
        break;
      }

      iter = iter->next;
      iterTail = iterTail->next;
    }

    cur = temp;
  }
}


//  Helper function for merging lists together
template<typename K, typename V>
typename LinkedListCollection<K, V>::Node*
LinkedListCollection<K, V>::merge_sort(Node* left, int len)
{
  //  Split Lists

  Node* newHead = nullptr;
  Node* right;

  if (this->head == nullptr)
    return left;

  if (len == 1)
    return left;

  int mid = len/2;
  int counter = 0;

  while (counter < mid)
    left = left->next;

  right = left->next;
  left->next = nullptr;

  left = merge_sort(left, mid);
  right = merge_sort(right, len-mid);

  //  merging lists
  if (left->value <= right->value)
  {
    if (newHead == nullptr)
    {
      newHead = left;
      newHead->next = right;
    }
  }

  if (right->value <= left->value)
  {
    if (newHead == nullptr)
    {
      newHead = right;
      newHead->next = left;
    }
  }

  return newHead;
}


//  In place merge sort method for linked lists
template<typename K, typename V>
void LinkedListCollection<K, V>::merge_sort()
{
  head = merge_sort(this->head, this->length);
}


//  Helper function for quick sort method
template<typename K, typename V>
typename LinkedListCollection<K, V>::Node*
LinkedListCollection<K, V>::quick_sort(Node* start, int len)
{
  int counter = 0;
  int mid = len/2;
  Node* lhs = nullptr;
  Node* rhs = nullptr;
  Node* lhsTail = nullptr;
  Node* pivot = start;
  Node* cur = start;

  //  Base case
  if (start->next == nullptr)
  {
    return start;
  }

  //  places nodes into correct lists
  while(cur != nullptr)
  {
    if (cur->value < pivot->value)
    {
      if (lhs == nullptr)
      {
        lhs = cur;
        continue;
      }

      lhs->next = cur;
    }

    if (cur->value > pivot->value)
    {
      if (rhs == nullptr)
      {
        rhs = cur;
        continue;
      }

      rhs->next = cur;
    }
  }

  lhs = quick_sort(lhs, mid);
  rhs = quick_sort(rhs, len-mid);

  //  reconnect lists
  cur = lhs;

  while (cur != nullptr)
    cur = cur->next;

  lhsTail = cur;
  pivot->next = rhs;
  lhsTail->next = pivot;

  return lhs;
}


//  In place quick sort for linked lists
template<typename K, typename V>
void LinkedListCollection<K, V>::quick_sort()
{
  head = quick_sort(this->head, this->length);
}

#endif
