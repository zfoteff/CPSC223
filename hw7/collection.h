#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>

template<typename K, typename V>
class Collection
{
public:
  //  All pure-virtual functions (must be overridden)
  //  Insert a key-value pair into the collection
  virtual void insert(const K& key, const V& val) = 0;

  //  Remove a key-value pair from the Collection
  virtual void remove(const K& key) = 0;

  //  Find and return the value associated with the key
  virtual bool find(const K& key, V& val) const = 0;

  //  Find and return a list of keys with values >= k1 and <= k2
  virtual void find(const K& k1, const K& k2, std::vector<K>& keys) const = 0;

  //  Return all the keys in the collection
  virtual void keys(std::vector<K>& keys) const = 0;

  //  Returns all the keys in ascending (sorted order)
  virtual void sort(std::vector<K>& keys) const = 0;

  //  Returns the number of keys in the Collection
  virtual int size() const = 0;
};

#endif
