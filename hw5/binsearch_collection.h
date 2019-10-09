#ifndef BINSEARCH_COLLECTION_H
#define BINSEARCH_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"

template<typename K, typename V>
class BinSearchCollection : public Collection<K, V>
{
public:
  //  sorts list, and inserts kv-pair into the Collection
  void insert(const K& key, const V& val);

  //  remove a kv-par from the collection
  void remove(const K&);

  //  return true if key exists in collection and return its value by reference
  //  return false otherwise
  bool find(const K& key, V& val) const;

  //  find and return the list of keys in the range [K1, K2]
  void find(const K& k1, const K& k2, std::vector<K>& keys) const;

  //  returns all keys in sorted order
  void sort(std::vector<K>& keys) const;

  //  return all keys in the Collection
  void keys(std::vector<K>& keys) const;

  //  return the number of keys in the Collection
  int size() const;

private:
  //  binary search helper function
  bool binsearch(const K& key, int& index) const;

  //  vector storage
  std::vector<std::pair<K, V>> kv_list;

};

template<typename K, typename V>
bool BinSearchCollection<K, V>::binsearch(const K& key, int& index) const
{
  int minval = 0;
  int maxval = kv_list.size() - 1;
  int midpoint;
  bool ret = false;

  if (kv_list.size() == 0)
    return false;

  while(minval <= maxval)
  {
    midpoint = (maxval + minval) / 2;

    if (kv_list[midpoint].first == key)
    {
      index = midpoint;
      ret = true;
      break;
    }

    else if (kv_list[midpoint].first > key)
      maxval = midpoint - 1;

    else if (kv_list[midpoint].first < key)
      minval = midpoint + 1;
  }

  index = midpoint;
  return ret;
}

template<typename K, typename V>
void BinSearchCollection<K, V>::insert(const K& key, const V& val)
{
  std::pair<K, V> p(key, val);
  int i;

  if (kv_list.size() == 0)
  {
    kv_list.insert(kv_list.begin(), p);
  }

  else
  {
    bool r = binsearch(p.first, i);
    kv_list.insert(kv_list.begin() + i+1, p);
  }

}

template<typename K, typename V>
void BinSearchCollection<K, V>::remove(const K& key)
{
  int rm_idx;
  bool r = binsearch(key, rm_idx);

  if (r)
    kv_list.erase(kv_list.begin()+rm_idx);
}

template<typename K, typename V>
bool BinSearchCollection<K, V>::find(const K& key, V& val) const
{
  int val_idx;
  bool r = binsearch(key, val_idx);

  if (r == false)
  {
    val = val_idx;
    return false;
  }

  val = kv_list[val_idx].second;
  return r;
}

template<typename K, typename V>
void BinSearchCollection<K, V>
::find(const K& k1, const K& k2, std::vector<K>& keys) const
{
    int k1_idx, k2_idx;
    bool r1 = binsearch(k1, k1_idx);
    bool r2 = binsearch(k2, k2_idx);

    if (r1 == true && r2 == true)
    {
      while(k1_idx <= k2_idx)
      {
          keys.push_back(kv_list[k1_idx].first);
          k1_idx++;
      }
    }
}


template<typename K, typename V>
void BinSearchCollection<K, V>
::sort(std::vector<K>& keys) const
{
  keys = keys;
}

template<typename K, typename V>
void BinSearchCollection<K, V>::keys(std::vector<K>& keys) const
{
  for (int i = 0; i < kv_list.size(); ++i)
  {
    keys.push_back(kv_list[i].first);
  }
}

template<typename K, typename V>
int BinSearchCollection<K, V>::size() const
{
  return kv_list.size();
}

#endif
