#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <vector>
#include <algorithm>
#include "collection.h"

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

private:
  struct Node
  {
    K key;
    V value;
    Node* next;
  };

  Node* head;
  Node* tail;
  int length;
};

template<typename K, typename V>
LinkedListCollection<K, V>::LinkedListCollection()
{
  head = nullptr;
  tail = nullptr;
  length = 0;
}

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

template<typename K, typename V>
LinkedListCollection<K, V>& LinkedListCollection<K, V>
::operator=(const LinkedListCollection<K, V>& rhs)
{
  if(this == &rhs)
    return *this;

  Node* temp = head;
  while(temp->next != nullptr)
  {
    head = head->next;
    delete temp;
    temp = head;
    length--;
  }

  temp = rhs.head;
  while(temp != nullptr)
  {
    this->insert(temp->key, temp->value);
    temp = temp->next;
  }

  return *this;
}

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

template<typename K, typename V>
int LinkedListCollection<K, V>::size() const
{
  return length;
}

#endif
