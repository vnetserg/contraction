class DijkstraWitness;

#ifndef WITNESS_H
#define WITNESS_H

#include "digraph.hpp"


class DijkstraWitness
{
public:
    DijkstraWitness(Digraph *graph, int64_t max_hops);

    std::vector<int64_t> query(int64_t src, std::vector<int64_t> dst, int64_t max_dist);

private:
    Digraph *graph;
    int64_t max_hops;
};

#endif // WITNESS_H
