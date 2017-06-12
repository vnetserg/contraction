#include "../include/contraction_hierarchies.hpp"


ContractionHierarchies::ContractionHierarchies(Digraph* graph)
{
    VertexOrder order(graph);
    this->graph = makeContractionGraph(graph, order);
}

Digraph* ContractionHierarchies::makeContractionGraph(Digraph* graph, const VertexOrder &order)
{
    return graph;
}

int64_t ContractionHierarchies::query(int64_t src, int64_t dst)
{
    return -1;
}
