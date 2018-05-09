#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

struct GraphNode {
  int label;
  std::vector<GraphNode*> neighbours;

  GraphNode(int val) : label(val) {}
};

void BfsGraph(const std::vector<GraphNode*>& graph_nodes) {
  std::vector<int> visit(graph_nodes.size(), 0);

  for (GraphNode* graph_node : graph_nodes) {
    std::queue<GraphNode*> node_queue;

    if (visit[graph_node->label] == 1) {
      return;
    }

    node_queue.push(graph_node);
    visit[graph_node->label] = 1;

    std::cout << "From Node " << graph_node->label << ": ";

    while (!node_queue.empty()) {
      GraphNode* node = node_queue.front();
      node_queue.pop();

      std::cout << "->" << node->label;

      for (GraphNode* neighbour : node->neighbours) {
        if (visit[neighbour->label] == 1) {
          continue;
        }

        node_queue.push(neighbour);
        visit[neighbour->label] = 1;
      }
    }

    std::cout << std::endl;
  }
}

int main() {
  std::vector<GraphNode*> graph_nodes;
  graph_nodes.push_back(new GraphNode(0));
  graph_nodes.push_back(new GraphNode(1));
  graph_nodes.push_back(new GraphNode(2));
  graph_nodes.push_back(new GraphNode(3));
  graph_nodes.push_back(new GraphNode(4));

  graph_nodes[0]->neighbours.push_back(graph_nodes[2]);
  graph_nodes[0]->neighbours.push_back(graph_nodes[4]);
  graph_nodes[1]->neighbours.push_back(graph_nodes[0]);
  graph_nodes[1]->neighbours.push_back(graph_nodes[2]);
  graph_nodes[2]->neighbours.push_back(graph_nodes[3]);
  graph_nodes[3]->neighbours.push_back(graph_nodes[4]);
  graph_nodes[4]->neighbours.push_back(graph_nodes[3]);

  BfsGraph(graph_nodes);

  for (auto graph_node : graph_nodes) {
    delete graph_node;
  }

  return 0;
}
