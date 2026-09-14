#pragma once
#include <bit>
#include <cstddef>
#include <type_traits>

template <typename T, size_t RequestedCapacity>
  requires std::is_trivially_copyable_v<T>
class SpscQueue {
public:
  static constexpr size_t Capacity = std::bit_ceil(RequestedCapacity);

private:
  T buffer[Capacity];
  size_t start = 0;
  size_t end = 0;

public:
  SpscQueue() {}

  bool push(const T &item) {
    if (this->size() >= Capacity) {
      return false;
    }
    buffer[end % Capacity] = item;
    end++;
    return true;
  }

  bool pop(T &item) {
    if (this->empty()) {
      return false;
    }
    item = buffer[start % Capacity];
    start++;
    return true;
  }

  bool empty() const { return start == end; }

  size_t size() const { return end - start; }

  size_t capacity() const { return Capacity; }
};
