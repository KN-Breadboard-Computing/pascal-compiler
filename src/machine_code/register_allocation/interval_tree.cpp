#include "interval_tree.hpp"

namespace machine_code {
IntervalTree::Node* IntervalTree::insert(IntervalTree::Node* node, const std::string& variable, std::size_t start,
                                         std::size_t end) {
  if (node == nullptr) {
    Node* newNode = new Node{variable, start, end};
    return newNode;
  }

  if (start < node->start_) {
    node->left_ = insert(node->left_, variable, start, end);
  }
  else {
    node->right_ = insert(node->right_, variable, start, end);
  }

  if (node->maxEnd_ < end) {
    node->maxEnd_ = end;
  }

  return node;
}

IntervalTree::Node* IntervalTree::remove(IntervalTree::Node* node, std::size_t start, std::size_t end) {
  if (node == nullptr) {
    return node;
  }

  if (start < node->start_) {
    node->left_ = remove(node->left_, start, end);
  }
  else if (start > node->start_) {
    node->right_ = remove(node->right_, start, end);
  }
  else {
    if (node->left_ == nullptr) {
      Node* temp = node->right_;
      delete node;
      return temp;
    }
    else if (node->right_ == nullptr) {
      Node* temp = node->left_;
      delete node;
      return temp;
    }

    Node* temp = node->right_;
    while (temp->left_) {
      temp = temp->left_;
    }
    node->start_ = temp->start_;
    node->end_ = temp->end_;
    node->right_ = remove(node->right_, temp->start_, temp->end_);
  }

  node->maxEnd_ = node->end_;
  if (node->left_) {
    node->maxEnd_ = std::max(node->maxEnd_, node->left_->maxEnd_);
  }
  if (node->right_) {
    node->maxEnd_ = std::max(node->maxEnd_, node->right_->maxEnd_);
  }

  return node;
}

void IntervalTree::overlaps(IntervalTree::Node* node, std::size_t start, std::size_t end,
                            std::vector<std::string>& overlapping) const {
  if (node == nullptr) {
    return;
  }

  if (node->start_ <= end && start <= node->end_) {
    overlapping.push_back(node->variable_);
  }

  if (node->left_ != nullptr && node->left_->maxEnd_ >= start) {
    overlaps(node->left_, start, end, overlapping);
  }

  overlaps(node->right_, start, end, overlapping);
}
}  // namespace machine_code