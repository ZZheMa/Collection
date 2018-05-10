#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <utility>
#include <queue>
#include <cassert>

// 207. Course Schedule

struct GraphNode {
  int label;
  std::vector<GraphNode*> neighbours;

  GraphNode(int val) : label(val) {}
};

// 使用广度优先遍历实现的拓扑排序来求图是否有环。
bool canFinish(int numCourses, std::vector<std::pair<int, int>>& prerequisites) {
  std::vector<int> degrees(numCourses, 0);

  std::vector<GraphNode*> graph_nodes;
  for (int i = 0; i < numCourses; i++) {
    graph_nodes.push_back(new GraphNode(i));
  }

  for (const auto& prerequisite : prerequisites) {
    GraphNode* begin_node = graph_nodes[prerequisite.second];
    GraphNode* end_node = graph_nodes[prerequisite.first];

    begin_node->neighbours.push_back(end_node);
    ++degrees[end_node->label];
  }

  // 遍历每个入度为零的节点，将入度为零的节点指向其他节点的边都去掉，也就是将指向的节点的入度减一。
  std::queue<GraphNode*> node_queue;
  for (int i = 0; i < numCourses; i++) {
    if (degrees[i] == 0) {
      node_queue.push(graph_nodes[i]);
    }
  }

  while (!node_queue.empty()) {
    GraphNode* top_node = node_queue.front();
    //std::cout << top_node->label << " "; // 输出拓扑序列。
    node_queue.pop();

    for (auto neighbour : top_node->neighbours) {
      --degrees[neighbour->label];
      if (degrees[neighbour->label] == 0) {
        node_queue.push(neighbour);
      }
    }
  }

  for (auto degree : degrees) {
    if (degree != 0) {
      return false;
    }
  }

  return true;
}

int main() {
  std::vector<std::pair<int, int>> prerequisites;
  prerequisites.push_back(std::make_pair(1, 0));
  prerequisites.push_back(std::make_pair(0, 1));


  std::cout << canFinish(2, prerequisites) << std::endl;



  return 0;
}
