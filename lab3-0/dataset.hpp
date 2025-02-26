#pragma once
#include <cstddef>
#include <stdexcept>

template <class T> class dataset {
public:
  dataset();
  dataset(std::size_t capacity);
  dataset(const dataset &other);
  ~dataset();
  std::size_t size() const;
  std::size_t cap() const;
  T &front();
  T &back();
  void push_back(T *object);
  void pop_back();
  T *pull_out(std::size_t i);
  void insert(std::size_t pos, T *object);
  void erase(std::size_t first, std::size_t last);
  void clear();
  bool empty() const;

  T &operator[](std::size_t i);

private:
  void increase_capacity(std::size_t new_capacity);

  T **data;
  std::size_t len;
  std::size_t capacity;
};

template <class T> dataset<T>::dataset() : data(nullptr), len(0), capacity(0) {}

template <class T>
dataset<T>::dataset(std::size_t capacity) : len(0), capacity(capacity) {
  data = new T *[capacity];
}

template <class T>
dataset<T>::dataset(const dataset &other)
    : capacity(other.capacity), len(other.len) {
  data = new T *[capacity];
  for (std::size_t i = 0; i < len; ++i) {
    data[i] = new T(*other.data[i]);
  }
}

template <class T> dataset<T>::~dataset() {
  for (std::size_t i = 0; i < len; ++i) {
    delete data[i];
  }
  delete[] data;
}

template <class T> std::size_t dataset<T>::size() const { return len; }

template <class T> std::size_t dataset<T>::cap() const { return capacity; }

template <class T> T &dataset<T>::front() { return *data[0]; }

template <class T> T &dataset<T>::back() { return *data[len - 1]; }

template <class T> T &dataset<T>::operator[](std::size_t i) {
  if (i >= len)
    throw std::out_of_range::exception();
  return *data[i];
}

template <class T> void dataset<T>::push_back(T *object) {
  if (capacity == len) {
    increase_capacity(capacity == 0 ? 1 : capacity * 2);
  }
  *(data + len) = object;
  ++len;
}

template <class T> void dataset<T>::pop_back() {
  --len;
  delete data[len];
}

template <class T> void dataset<T>::insert(std::size_t pos, T *object) {
  if (pos > len)
    throw std::out_of_range::exception();
  push_back(object);
  T next = data[pos];
  data[pos] = object;
  for (std::size_t i = pos + 1; i < len; ++i) {
    std::swap(next, data[i]);
  }
  return data + pos;
}

template <class T> void dataset<T>::erase(std::size_t first, std::size_t last) {
  if (first >= last)
    return;
  if (last > len)
    last = len;
  std::size_t count = last - first;
  for (std::size_t i = first; i + count < len; ++i) {
    delete data[i];
    data[i] = data[i + count];
  }
  len -= count;
}

template <class T> T *dataset<T>::pull_out(std::size_t pos) {
  if (pos >= len)
    throw std::out_of_range::exception();
  T *out = data[pos];
  for (std::size_t i = pos; i < len - 1; ++i) {
    data[i] = data[i + 1];
  }
  --len;
  return out;
}

template <class T> void dataset<T>::clear() {
  for (std::size_t i = 0; i < len; ++i) {
    delete data[i];
  }
  delete[] data;
  capacity = 0;
  len = 0;
}

template <class T> bool dataset<T>::empty() const { return len == 0; }

template <class T>
void dataset<T>::increase_capacity(std::size_t new_capacity) {
  T **new_data = new T *[new_capacity];
  for (std::size_t current = 0; current < len; ++current) {
    *(new_data + current) = *(data + current);
  }
  if (len > 0)
    delete[] data;
  capacity = new_capacity;
  data = new_data;
}
