#include "../include/vertex_order.hpp"

VertexOrder::VertexOrder(Digraph* graph) : order(graph->vertices())
{
    for (int64_t i = 0; i < order.size(); i++)
        order[i] = i;
}

std::vector<int64_t>::const_iterator VertexOrder::begin() const
{
    return order.cbegin();
}

std::vector<int64_t>::const_iterator VertexOrder::end() const
{
    return order.cend();
}

int64_t VertexOrder::operator[](int64_t i) const
{
    return order[i];
}

int64_t VertexOrder::size() const
{
    return order.size();
}
