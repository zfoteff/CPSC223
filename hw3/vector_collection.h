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
  std::pair<K, V> p(key, val);
  kv_list.push_back(p);
}


template<typename K, typename V>
void VectorCollection<K, V>::remove(const K& key)
{
  for(int i = 0; i < kv_list.size(); ++i)
  {
    if (kv_list[i].first == key)
      kv_list.erase(kv_list.begin() + i);
  }
}

template<typename K, typename V>
bool VectorCollection<K, V>::find(const K& key, V& val) const
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
void VectorCollection<K, V>::find(const K& k1, const K& k2, std::vector<K>& keys) const
{
  for(int i = 0; i < kv_list.size(); ++i)
  {
    if (kv_list[i].first >= k1 && kv_list[i].first <= k2)
      keys.push_back(kv_list[i].first);
  }
}

template<typename K, typename V>
void VectorCollection<K, V>::keys(std::vector<K>& keys) const
{
  for (int i = 0; i < kv_list.size(); ++i)
  {
    keys.push_back(kv_list[i].first);
  }
}

template<typename K, typename V>
void VectorCollection<K, V>::sort(std::vector<K>& keys) const
{
  std::sort(keys.begin(), keys.end());
}

template<typename K, typename V>
int VectorCollection<K, V>::size() const
{
  unsigned int i;

  for(i = 0; i < kv_list.size(); ++i)
    continue;

  return i;
}


#endif
