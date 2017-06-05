#include "intheap.hpp"
#include "digraph.hpp"

#define INFTY 2305843009213693952

class Bidijkstra
{
public:

    Bidijkstra(Digraph *graph);

    int64_t query(int64_t src, int64_t dst);

private:

    Digraph *graph, *regraph;
    std::vector<int64_t> dist_fwd, dist_bwd, workset;
    IntHeap queue_fwd, queue_bwd;

    bool dijkstra_step(const Digraph &gr, IntHeap &queue, std::vector<int64_t> &dist,
                       const std::vector<int64_t> &other_dist);

};
