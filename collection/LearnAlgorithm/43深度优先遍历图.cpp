#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

struct GraphNode {
  int label;
  std::vector<GraphNode*> neighbours;

  GraphNode(int val) : label(val) {}
};

void DfsGraph(GraphNode* graph_node, std::vector<int>& visit) {
  if (graph_node == NULL) {
    return;
  }

  std::cout << "->" << graph_node->label;
  visit[graph_node->label] = 1;

  for (GraphNode* neighbour : graph_node->neighbours) {
    if (visit[neighbour->label] == 0) {
      DfsGraph(neighbour, visit);
    }
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

  std::vector<int> visit(graph_nodes.size(), 0);

  for (auto graph_node : graph_nodes) {
    if (visit[graph_node->label] == 0) {
      std::cout << "From Node " << graph_node->label << ": ";
      DfsGraph(graph_node, visit);
      std::cout << std::endl;
    }
  }

  for (auto graph_node : graph_nodes) {
    delete graph_node;
  }

  return 0;
}
