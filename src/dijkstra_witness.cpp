#include "../include/dijkstra_witness.hpp"


DijkstraWitness::DijkstraWitness(Digraph *graph, int64_t max_hops)
    : graph(graph), max_hops(max_hops)
{

}


std::vector<int64_t> DijkstraWitness::query(int64_t src, std::vector<int64_t> dst, int64_t max_dist)
{
    std::vector<int64_t> result(dst.size(), INFTY);
    return result;
}
