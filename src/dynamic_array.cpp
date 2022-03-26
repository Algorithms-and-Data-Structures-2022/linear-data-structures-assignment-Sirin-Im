#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    size_ = 0;
    capacity_ = capacity;
    data_ = new int[capacity_];
    std::fill(data_,data_+capacity_,0);
  }

  DynamicArray::~DynamicArray() {
    size_ = 0;
    capacity_ = 0;

    delete[] data_;
    data_ = nullptr;
  }

  void DynamicArray::Add(int value) {
    if (size_ == capacity_) {
      int* data = new int[capacity_+kCapacityGrowthCoefficient]{};
      std::copy(data_,data_ + size_, data);
      data[size_] = value;
      size_++;
      capacity_ += kCapacityGrowthCoefficient;
      data_ = data;
    } else {
      data_[size_] = value;
      size_++;
    }
  }

  bool DynamicArray::Insert(int index, int value) {
    if (index <= size_ && index >= 0) {
      if (size_ >= capacity_) {
        Resize(capacity_+ kCapacityGrowthCoefficient);
      }
      for (int i = size_-1; i >= index; i--) {
        data_[i + 1] = data_[i];
      }
      data_[index] = value;
      size_++;
      return true;
    }
    return false;
  }

  bool DynamicArray::Set(int index, int new_value) {
    for (int i = 0; i < size_; i++) {
      if (i == index) {
        data_[i] = new_value;
        return true;
      }
    }
    return false;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    for (int i = 0; i < size_; ++i) {
      if(i == index) {
        int elem = data_[i];
        for (int j = i; j < size_-1; ++j) {
          data_[i] = data_[i+1];
        }
        size_ -= 1;
        return elem;
      }
    }
    return std::nullopt;
  }

  void DynamicArray::Clear() {
    size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    for (int i = 0; i < size_; ++i) {
      if (i == index) {
        return data_[i];
      }
    }
    return std::nullopt;
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    for (int i = 0; i < size_; ++i) {
      if (data_[i] == value) {
        return true;
      }
    }
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    return size_ == 0;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    if (new_capacity > capacity_) {
      int* data = new int[new_capacity];
      std::copy(data_,data_+size_,data);
      capacity_ = new_capacity;
      data_ = data;
      return true;
    }else {
      return false;
    }
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment