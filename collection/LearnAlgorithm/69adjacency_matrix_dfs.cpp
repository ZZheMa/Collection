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

typedef std::vector<std::vector<int>> AdjacencyMatrix;

const std::size_t N = 4;

void Dfs(const AdjacencyMatrix& adjacency_matrix, int node, std::vector<int>& visit) {
  visit[node] = 1;

  std::cout << node << std::endl;

  for (std::size_t i = 0; i < N; i++) {
    if (visit[i] ==0 && adjacency_matrix[node][i] == 1) {
      Dfs(adjacency_matrix, i, visit);
    }
  }
}

void PrintAdjacencyMatrix(const AdjacencyMatrix& adjacency_matrix) {
  for (const auto& line : adjacency_matrix) {
    for (auto num : line) {
      std::cout << num << " ";
    }

    std::cout << std::endl;
  }
}

int main() {
  AdjacencyMatrix adjacency_matrix(N, std::vector<int>(N, 0));
  adjacency_matrix[0][0] = 1;
  adjacency_matrix[1][1] = 1;
  adjacency_matrix[2][2] = 1;
  adjacency_matrix[3][3] = 1;

  adjacency_matrix[0][1] = 1;
  adjacency_matrix[1][0] = 1;
  adjacency_matrix[1][2] = 1;
  adjacency_matrix[2][1] = 1;

  PrintAdjacencyMatrix(adjacency_matrix);

  std::cout << std::endl;

  std::vector<int> visit(N, 0);
  for (std::size_t i = 0; i < N; ++i) {
    if (visit[i] == 1) {
      continue;
    }

    Dfs(adjacency_matrix, i, visit);
  }

  return 0;
}
