#pragma once
#include <cstddef>
#include <stdexcept>

template <class T> class dataset {
public:
  dataset();
  dataset(std::size_t len);
  dataset(const dataset &other);
  ~dataset();
  std::size_t size() const;
  T &front();
  T &back();
  void push_back(const T &object);
  void pop_back();
  T *insert(std::size_t pos, const T &object);
  T *erase(const T *first, const T *last);
  void erase(std::size_t first, std::size_t last);
  void clear();
  bool empty() const;

  dataset &operator=(const dataset &other);
  T &operator[](std::size_t i);

private:
  void increase_capacity(std::size_t new_capacity);

  T *data;
  std::size_t len;
  std::size_t capacity;
};

template <class T> dataset<T>::dataset() : data(nullptr), len(0), capacity(0) {}

template <class T>
dataset<T>::dataset(std::size_t len) : len(len), capacity(len) {
  data = new T[len];
}

template <class T> dataset<T>::dataset(const dataset &other) {
  len = 0;
  capacity = 0;
  increase_capacity(other.capacity);
  std::size_t new_size = 0;
  for (; new_size < other.len; ++new_size) {
    *(data + new_size) = *(other.data + new_size);
  }
  len = new_size;
}

template <class T> dataset<T>::~dataset() { delete[] data; }

template <class T> std::size_t dataset<T>::size() const { return len; }

template <class T> T &dataset<T>::front() { return data[0]; }

template <class T> T &dataset<T>::back() { return data[len - 1]; }

template <class T> dataset<T> &dataset<T>::operator=(const dataset &other) {
  clear();
  increase_capacity(other.capacity);
  for (; len < other.len; ++len) {
    *(data + len) = *(other.data + len);
  }
  return *this;
}

template <class T> T &dataset<T>::operator[](std::size_t i) {
  if (i >= len)
    throw std::out_of_range::exception();
  return data[i];
}

template <class T> void dataset<T>::push_back(const T &object) {
  if (capacity == len) {
    increase_capacity(capacity == 0 ? 1 : capacity * 2);
  }
  *(data + len) = object;
  ++len;
}

template <class T> void dataset<T>::pop_back() {
  --len;
  data[len].~T();
}

template <class T> T *dataset<T>::insert(std::size_t pos, const T &object) {
  push_back(object);
  T next = data[pos];
  data[pos] = object;
  for (std::size_t i = pos + 1; i < len; ++i) {
    std::swap(next, data[i]);
  }
  return data + pos;
}

template <class T> T *dataset<T>::erase(const T *first, const T *last) {
  if (first >= last)
    return nullptr;
  std::size_t count = last - first;
  std::size_t start = first - data;
  for (std::size_t i = start; i + count != len; ++i) {
    data[i] = data[i + count];
  }
  for (std::size_t i = 0; i < count; i++) {
    pop_back();
  }
  return data + start;
}

template <class T> void dataset<T>::erase(std::size_t first, std::size_t last) {
  erase(data + first, data + last);
}

template <class T> void dataset<T>::clear() {
  delete[] data;
  capacity = 0;
  len = 0;
}

template <class T> bool dataset<T>::empty() const { return len == 0; }

template <class T>
void dataset<T>::increase_capacity(std::size_t new_capacity) {
  T *new_data = new T[new_capacity];
  for (std::size_t current = 0; current < len; ++current) {
    *(new_data + current) = *(data + current);
  }
  if (len > 0)
    delete[] data;
  capacity = new_capacity;
  data = new_data;
}
