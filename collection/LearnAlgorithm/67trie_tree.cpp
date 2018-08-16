#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>
#include <array>

// 208. Implement Trie (Prefix Tree)
// 211. Add and Search Word - Data structure design

// 字典树，该实现只能接收26个小写字母。用于统计单词，实现自动补全等。

class TrieTree {
public:
  TrieTree() = default;

  ~TrieTree();

  TrieTree(const TrieTree&) = delete;
  TrieTree& operator=(const TrieTree&) = delete;

  void InsertWord(const std::string& word);

  bool SearchWord(const std::string& word) const;

  // '.' means it can represent any one letter.
  bool SearchWord2(const std::string& word) const;

  bool StartWith(const std::string& prefix) const;

  std::list<std::string> GetWords() const;

  void PrintWords() const;

  void PreOrderPrint() const;

private:
  struct TrieNode {
    enum {
      CAHR_COUNT = 26,
    };

    // 字符哈希的方法，直接定址法来确定数据位置，提高访问效率。
    // 每个位置都代表一个字母，每个位置都是相对于'a'的偏移量。也就是说结点'a'放在children[0]处。
    std::array<TrieNode*, CAHR_COUNT> children;
    bool is_end_;

    TrieNode() : is_end_(false) {
      for (TrieNode*& node : children) {
        node = nullptr;
      }
    }
  };

private:
  TrieNode root_;  // Empty head node.
  std::list<TrieNode*> trie_nodes_;
};

//--------------------------------------------------------

TrieTree::~TrieTree() {
  for (auto* node : trie_nodes_) {
    delete node;
  }
}

void TrieTree::InsertWord(const std::string& word) {
  TrieNode* node = &root_;

  for (auto c : word) {
    std::size_t offset = static_cast<std::size_t>(c - 'a');

    if (node->children[offset] == nullptr) {
      TrieNode* new_node = new TrieNode;
      node->children[offset] = new_node;
      trie_nodes_.push_back(new_node);
    }

    node = node->children[offset];
  }

  node->is_end_ = true;
}

bool TrieTree::SearchWord(const std::string& word) const {
  const TrieNode* node = &root_;

  for (char c : word) {
    std::size_t offset = static_cast<std::size_t>(c - 'a');
    node = node->children[offset];

    if (node == nullptr) {
      return false;
    }
  }

  return node->is_end_;
}

// '.' means it can represent any one letter.
bool TrieTree::SearchWord2(const std::string& word) const {
  if (word.empty()) {
    return false;
  }

  std::function<bool(const TrieNode*, std::size_t pos)> func;

  func = [&func, word](const TrieNode* root, std::size_t pos) {
    if (root == nullptr) {
      return false;
    }

    if (pos >= word.size()) {
      return root->is_end_;
    }

    if (word[pos] == '.') {
      for (std::size_t i = 0; i < TrieNode::CAHR_COUNT; ++i) {
        TrieNode* node = root->children[i];
        if (node == nullptr) {
          continue;
        }

        if (func(node, pos + 1)) {
          return true;
        }
      }
    } else {
      std::size_t offset = static_cast<std::size_t>(word[pos] - 'a');
      TrieNode* node = root->children[offset];
      return func(node, pos + 1);
    }

    return false;
  };

  return func(&root_, 0);
}

bool TrieTree::StartWith(const std::string& prefix) const {
  const TrieNode* node = &root_;

  for (char c : prefix) {
    std::size_t offset = static_cast<std::size_t>(c - 'a');
    node = node->children[offset];

    if (node == nullptr) {
      return false;
    }
  }

  return true;
}

std::list<std::string> TrieTree::GetWords() const {
  std::list<std::string> words;
  std::string word;

  std::function<void(const TrieNode*)> func;

  func = [&func, &word, &words](const TrieNode* parent_node) {
    if (parent_node == nullptr) {
      return;
    }

    for (std::size_t i = 0; i < TrieNode::CAHR_COUNT; ++i) {
      TrieNode* node = parent_node->children[i];
      if (node == nullptr) {
        continue;
      }

      char c = static_cast<char>('a' + i);
      word.push_back(c);

      if (node->is_end_) {
        words.push_back(word);
      }

      func(node);
      word.pop_back();
    }
  };

  func(&root_);

  return words;
}

void TrieTree::PrintWords() const {
  std::list<std::string> words = GetWords();
  for (const auto& word : words) {
    std::cout << word << std::endl;
  }
}

void TrieTree::PreOrderPrint() const {
  std::function<void(const TrieNode*)> traverse_func;

  // lambda表达式实现递归，需要捕获函数自己，才能调用自己。
  traverse_func = [&traverse_func](const TrieNode* parent_node) {
    if (parent_node == nullptr) {
      return;
    }

    for (std::size_t i = 0; i < TrieNode::CAHR_COUNT; ++i) {
      TrieNode* node = parent_node->children[i];

      if (node == nullptr) {
        continue;
      }

      char c = static_cast<char>('a' + i);
      std::cout << c << ", ";

      traverse_func(node);
    }
  };

  traverse_func(&root_);
  std::cout << std::endl;
}


int main() {
  TrieTree trie_tree;
  trie_tree.InsertWord("console");
  //trie_tree.PreOrderPrint();
  trie_tree.InsertWord("hello");
  trie_tree.InsertWord("abc");
  trie_tree.InsertWord("abcd");
  trie_tree.InsertWord("abcdefg");

  //trie_tree.PreOrderPrint();

  std::cout << std::endl;

  trie_tree.PrintWords();

  std::cout << std::endl;

  std::cout << trie_tree.SearchWord("a") << std::endl;
  std::cout << trie_tree.SearchWord("helloa") << std::endl;
  std::cout << trie_tree.SearchWord("abc") << std::endl;
  std::cout << trie_tree.SearchWord("hello") << std::endl;

  std::cout << std::endl;

  std::cout << trie_tree.StartWith("a") << std::endl;
  std::cout << trie_tree.StartWith("abc") << std::endl;
  std::cout << trie_tree.StartWith("abcf") << std::endl;

  std::cout << std::endl;

  std::cout << trie_tree.SearchWord2("a") << std::endl;
  std::cout << trie_tree.SearchWord2("abc") << std::endl;
  std::cout << trie_tree.SearchWord2("ancde") << std::endl;


  return 0;
}
