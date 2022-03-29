#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* newFront_ = new Node(value, nullptr);
    if (front_ == nullptr) {
      front_ = newFront_;
      back_ = newFront_;
    } else {
      back_->next = newFront_;
      back_ = newFront_;
    }
    size_++;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index <= size_) {
      Node* node = new Node(value, nullptr);
      if (index == 0) {
        node->next = front_;
        front_ = node;
        if(size_ == 0) {
          back_ = front_;
        }
        size_++;
        return true;
      }
      if(index == size_) {
        back_->next = node;
        back_ = node;
        size_++;
        return true;
      }
      Node* node1 = front_;
      for (int i = 0; i < size_; ++i) {
        if (i == index) {
          node->next = node1->next->next;
          node1->next = node;
          size_++;
          return true;
        }
        node1 = node1->next;
      }
    }else {
      return false;
    }
  }

  bool LinkedList::Set(int index, int new_value) {
    Node* node = front_;
    for (int i = 0; i < size_; ++i) {
      if (i == index) {
        node->value = new_value;
        return true;
      }
      node = node->next;
    }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    Node* node = front_;
    Node* node2;
    for (int i = 0; i < size_; ++i) {
      if (i == index) {
        if(i == 0) {
          front_ = front_->next;
        }
        node2->next = node->next;
        size_--;
        return node->value;
      }
      node2 = node;
      node = node->next;
    }
    return std::nullopt;
  }

  void LinkedList::Clear() {
    size_ = 0;
    front_ = nullptr;
    back_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    Node* node = front_;
    for (int i = 0; i < size_; ++i) {
      if (i == index) {
        return node->value;
      }
      node = node->next;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* node = front_;
    for (int i = 0; i < size_; ++i) {
      if(node->value == value) {
        return i;
      }
      node = node->next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    Node* node = front_;
    for (int i = 0; i < size_; ++i) {
      if (node->value == value) {
        return true;
      }
      node = node->next;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (size_ > 0) {
      return front_->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (size_ > 0) {
      return back_->value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    Node* node = front_;
    for (int i = 0; i < size_; ++i) {
      if (i == index) {
        return node;
      }
      node = node->next;
    }
    return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment