#ifndef INTERVAL_TREE_HPP
#define INTERVAL_TREE_HPP

#include <string>
#include <vector>

namespace machine_code {
class IntervalTree {
 public:
  IntervalTree() = default;

  IntervalTree(const IntervalTree&) = delete;
  IntervalTree(IntervalTree&&) = default;

  IntervalTree& operator=(const IntervalTree&) = delete;
  IntervalTree& operator=(IntervalTree&&) = default;

  ~IntervalTree() = default;

  void insert(const std::string& variable, std::size_t start, std::size_t end) { root_ = insert(root_, variable, start, end); }
  void remove(std::size_t start, std::size_t end) { root_ = remove(root_, start, end); }
  void overlaps(std::size_t start, std::size_t end, std::vector<std::string>& overlapping) const { overlaps(root_, start, end, overlapping); }

 private:
  struct Node {
    std::string variable_;
    std::size_t start_;
    std::size_t end_;
    std::size_t maxEnd_;
    Node* left_;
    Node* right_;

    Node(const std::string& variable, std::size_t start, std::size_t end) : variable_{variable}, start_{start}, end_{end}, maxEnd_{end}, left_{nullptr}, right_{nullptr} {}
  };

  Node* root_ = nullptr;

  Node* insert(Node* node, const std::string& variable, std::size_t start, std::size_t end);
  Node* remove(Node* node, std::size_t start, std::size_t end);
  void overlaps(Node* node, std::size_t start, std::size_t end, std::vector<std::string>& overlapping) const;
};
}  // namespace machine_code

#endif  // INTERVAL_TREE_HPP