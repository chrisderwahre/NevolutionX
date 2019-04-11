#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdlib.h>

template<typename T>
class vector {
private:
  T* items;
  size_t m_length;
  size_t m_size;
public:
  vector() {
    m_size = 4;
    items = (T*)malloc(m_size * sizeof(T));
    m_length = 0;
  }

  ~vector() {
    if (!empty()) {
      clear();
    }
  }

  void clear() {
    for (int i = 0; i < m_length; ++i) {
      free(items[i]);
      items[i] = nullptr;
    }
    m_length = 0;
  };

  void push_back(T item) {
    if (m_length == m_size) {
      m_size = m_size<<1;
      items = static_cast<T*>(realloc(items, m_size * sizeof(T)));
    }
    items[m_length] = T(item);
    ++m_length;
  }

  T pop_back() {
    T tmp = items[m_length - 1];
    items[m_length - 1] = nullptr;
    --m_length;
    return tmp;
  }

  bool empty() {
    return m_length == 0;
  }
  
  size_t size() {
    return m_length;
  }

  size_t capacity() {
    return m_size;
  }

  T at(int key) {
    if (m_length <= key) {
      return nullptr;
    }
    return items[key];
  }

  T operator[](int key) {
    return items[key];
  }

  T front() {
    return items[0];
  }

  T back() {
    return items[m_length - 1];
  }
  
  T erase(int key) {
    if (m_length <= key) {
      return nullptr;
    }
    T ret = items[key];
    for (int i = key; i < m_length - 1; ++i) {
      items[i] = items[i + 1];
    }
    items[m_length] = nullptr;
    --m_length;
    return ret;
  }
};

#endif
