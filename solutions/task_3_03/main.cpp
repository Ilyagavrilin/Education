#include <iostream>
#include <stdexcept>
#include "gtest/gtest.h"
class List {
  struct Node {
    int value;
    Node *next;
  };
  Node *head_{nullptr};
  Node *tail_{nullptr};

public:
  ~List() {
    while (head_) {
      auto *n = head_->next;
      delete head_;
      head_ = n;
    }
  }
  bool empty() const noexcept { return head_ == nullptr; }
  void push_front(int v) {
    auto *n = new Node{v, head_};
    head_ = n;
    if (!tail_)
      tail_ = head_;
  }
  void push_back(int v) {
    auto *n = new Node{v, nullptr};
    if (!tail_) {
      head_ = tail_ = n;
    } else {
      tail_->next = n;
      tail_ = n;
    }
  }
  void pop_front() {
    if (!head_)
      return;
    auto *n = head_->next;
    delete head_;
    head_ = n;
    if (!head_)
      tail_ = nullptr;
  }
  void pop_back() {
    if (!head_)
      return;
    if (head_ == tail_) {
      delete head_;
      head_ = tail_ = nullptr;
      return;
    }
    auto *p = head_;
    while (p->next != tail_)
      p = p->next;
    delete tail_;
    tail_ = p;
    tail_->next = nullptr;
  }
  int get() const {
    if (!head_)
      throw std::runtime_error("empty");
    auto *slow = head_;
    auto *fast = head_;
    for (; fast && fast->next; slow = slow->next, fast = fast->next->next) {
    }
    return slow->value;
  }
  void show() const {
    for (auto *p = head_; p; p = p->next)
      std::cout << p->value << (p->next ? ' ' : '\n');
    if (!head_)
      std::cout << '\n';
  }
};

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}