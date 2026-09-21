#pragma once
#include <atomic>
#include <bit>
#include <cstddef>
#include <type_traits>

template <typename T, size_t RequestedCapacity>
  requires std::is_trivially_copyable_v<T> // required to use an array since no
                                           // args are accepted in constructor
class SpscQueue {
public:
  static constexpr size_t Capacity = std::bit_ceil(RequestedCapacity);
  static constexpr size_t Mask = Capacity - 1; // since Capacity is power of 2

private:
  T buffer_[Capacity];
  std::atomic<size_t> start_ = 0;
  std::atomic<size_t> end_ = 0;

public:
  SpscQueue() {}

  bool push(const T &item) {
    if (this->size() >= Capacity) {
      return false;
    }
    buffer_[end_ & Mask] = item;
    end_++;
    return true;
  }

  bool pop(T &item) {
    if (this->empty()) {
      return false;
    }
    item = buffer_[start_ & Mask];
    start_++;
    return true;
  }

  [[nodiscard]] bool empty() const { return start_ == end_; }

  [[nodiscard]] size_t size() const { return end_ - start_; }

  [[nodiscard]] size_t capacity() const { return Capacity; }
};
