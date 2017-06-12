#ifndef CONTRACTION_H
#define CONTRACTION_H

#include "bidijkstra.hpp"
#include "vertex_order.hpp"


class ContractionHierarchies
{
public:
    ContractionHierarchies(Digraph* graph);
    int64_t query(int64_t src, int64_t dst);

private:
    Digraph* graph;

    Digraph* makeContractionGraph(Digraph* graph, const VertexOrder &order);
};

#endif // CONTRACTION_H
