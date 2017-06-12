class ContractionHierarchies;

#ifndef CONTRACTION_H
#define CONTRACTION_H

#include "bidijkstra.hpp"
#include "vertex_order.hpp"
#include "dijkstra_witness.hpp"

#define WITNESS_MAX_HOPS 10


class ContractionHierarchies
{
public:
    ContractionHierarchies(Digraph* graph);
    ~ContractionHierarchies();
    int64_t query(int64_t src, int64_t dst);

private:
    Digraph *graph, *regraph;
};

#endif // CONTRACTION_H
