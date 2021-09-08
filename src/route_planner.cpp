#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model)
{
  // Convert inputs to percentage:
  start_x *= 0.01;
  start_y *= 0.01;
  end_x *= 0.01;
  end_y *= 0.01;

  // Finds the closest nodes to the starting and ending coordinates.
  start_node = &m_Model.FindClosestNode(start_x, start_y);
  end_node = &m_Model.FindClosestNode(end_x, end_y);
}

// Calculates the h value based on the distance to the end_node.
float RoutePlanner::CalculateHValue(RouteModel::Node const *node)
{
  return this->end_node->distance(*node);
}

// Expands the current node and adds all unvisited neighbors to the open list.
void RoutePlanner::AddNeighbors(RouteModel::Node *current_node)
{
  current_node->FindNeighbors();

  for(int i = 0; i < current_node->neighbors.size(); i++)
  {
    current_node->neighbors[i]->parent = current_node;
    current_node->neighbors[i]->g_value = current_node->g_value + current_node->distance(*current_node->neighbors[i]);
    current_node->neighbors[i]->h_value = CalculateHValue(current_node->neighbors[i]);
    open_list.push_back(current_node->neighbors[i]);
    current_node->neighbors[i]->visited = true;
  }
}

// Compare g+h values of the open_list
bool RoutePlanner::Compare(RouteModel::Node *n1, RouteModel::Node *n2)
{
  float f1 = n1->g_value + n1->h_value;
  float f2 = n2->g_value + n2->h_value;

  return f1 > f2;
}

// Sorts the open list and return the next node.
RouteModel::Node *RoutePlanner::NextNode() {
  std::sort(open_list.begin(), open_list.end(), Compare);

  RouteModel::Node *lowest = open_list.back();
  open_list.pop_back();

  return lowest;
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
  // Create path_found vector
  distance = 0.0f;
  std::vector<RouteModel::Node> path_found;

  // TODO: Implement your solution here.

  //reverse vector before returning it.
  distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
  return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
  RouteModel::Node *current_node = nullptr;

  // TODO: Implement your solution here.

}
