#include "../include/vertex_order.hpp"

VertexOrder::VertexOrder(Digraph* graph) : order(graph->vertices())
{
    for (int64_t i = 0; i < order.size(); i++)
        order[i] = i;
}

std::vector<int64_t>::const_iterator VertexOrder::cbegin()
{
    return order.cbegin();
}

std::vector<int64_t>::const_iterator VertexOrder::cend()
{
    return order.cend();
}
