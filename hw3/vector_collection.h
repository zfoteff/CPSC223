#ifndef VECTOR_COLLECTION_H
#define VECTOR_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"

template<typename K, typename V>
class VectorCollection : public Collection<K, V>
{
public:

  void insert(const K& key, const V& val);

  void remove(const K& key);

  bool find(const K& key, V& value) const;

  void find(const K& k1, const K& k2, std::vector<K>& keys) const;

  void keys(std::vector<K>& keys) const;

  void sort(std::vector<K>& keys) const;

  int size() const;

private:
  std::vector<std::pair<K, V>> kv_list;
};

template<typename K, typename V>
void VectorCollection<K, V>::insert(const K& key, const V& val)
{
  std::pair<K, V> p(key, value);
  kv_list.push_back(p);
}


template<typename K, typename V>
void VectorCollection::remove(const K& key)
{
  for(int i = 0; i < kv_list.size(); ++i)
  {
    if (kv_list[i].first == key)
      kv_list[i].erase();
  }
}

template<typename K, typename V>
bool VectorCollection::find(const K& key, const V& val) const
{
  bool r = false;

  for (int i = 0; i < kv_list.size(); ++i)
  {
    if(kv_list[i].first == key)
    {
      r = true;
      val = kv_list[i].second;
      break;
    }
  }

  return r;
}

template<typename K, typename V>
void VectorCollection::find(const K& k1, const K& k2, std::vector<K>& keys) const
{
  for(int i = 0; i < kv_list.size(); ++i)
  {
    if (kv_list[i].second >= k1.second || kv_list[i].second <= k2.value)
      keys.push_back(kv_list[i].first);
  }
}

template<typename K, typename V>
void VectorCollection::keys(std::vector<K>& keys) const
{
  for (int i = 0; i < kv_list.size(); ++i)
  {
    keys.push_back(kv_list[i].first);
  }
}

template<typename K, typename V>
void VectorCollection::sort(std::vector<K>& keys) const
{
  //  uses altered implementation of a selection sort
  int i;
  int j,
  int min_idx;
  K dummy;

  for (i = 0; i < keys.size() - 1; ++i)
  {
    min_idx = i;
    for (j = 0; j < keys.size(); ++j)
    {
      if (keys[j] < keys[min_idx])
        min_idx = j;
    }

    dummy = keys[i];
    keys[i] = keys[min_idx];
    keys[min_idx] = dummy;
  }
}

template<typename K, typename V>
int VectorCollection::size()
{
  unsigned int i;

  for(i = 0; i < kv_list.size(); ++i)
    continue;

  return i;
}


#endif
