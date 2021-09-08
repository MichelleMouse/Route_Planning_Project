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

// Construct final path found from the A* search.
std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
  distance = 0.0f;
  std::vector<RouteModel::Node> path_found;

  while(current_node->parent != nullptr)
  {
    path_found.push_back(*(current_node));

    auto parent = current_node->parent;
    distance += current_node->distance(*(parent));
    current_node = parent;
  }

  //reverse vector before returning it.
  distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.

  path_found.push_back(*(current_node));
  std::reverse(path_found.begin(),path_found.end());

  return path_found;
}

// A* Search algorithm
void RoutePlanner::AStarSearch() {
  RouteModel::Node *current_node = nullptr;

  start_node->visited = true;
  open_list.push_back(start_node);

  while(open_list.size() > 0)
  {
    current_node = NextNode();

    if(current_node->distance(*end_node) == 0.0)
    {
      m_Model.path = ConstructFinalPath(current_node);
      return;
    } else {
      AddNeighbors(current_node);
    }
  }
}
