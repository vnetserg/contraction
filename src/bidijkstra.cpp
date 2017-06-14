#include "../include/bidijkstra.hpp"


Bidijkstra::Bidijkstra(Digraph *graph) : graph(graph), regraph(graph->reversed()),
    dist_fwd(graph->vertices(), INFTY), dist_bwd(graph->vertices(), INFTY),
    queue_fwd(graph->vertices()), queue_bwd(graph->vertices())
{
    workset.reserve(graph->vertices());
}

int64_t Bidijkstra::query(int64_t src, int64_t dst)
{
    if (src == dst)
        return 0;

    // Clear last query
    clearLastQuery();

    // Add starting points
    queue_fwd.push(src, 0);
    queue_bwd.push(dst, 0);

    bool collision = false;
    while (!collision)
    {
        collision |= dijkstra_step(*graph, queue_fwd, dist_fwd, dist_bwd);
        collision |= dijkstra_step(*regraph, queue_bwd, dist_bwd, dist_fwd);
    }

    int64_t min_dist = INFTY;
    for (auto it = queue_fwd.cbegin(); it < queue_fwd.cend(); it++)
    {
        int64_t vert = it->el, dist = it->prio;
        int64_t cand_dist = dist + dist_bwd[vert];
        if (min_dist > cand_dist)
            min_dist = cand_dist;
    }

    return min_dist;
}

// PRIVATE

void Bidijkstra::clearLastQuery()
{
    for (int64_t &v : workset)
    {
        dist_fwd[v] = INFTY;
        dist_bwd[v] = INFTY;
    }
    queue_fwd.clear();
    queue_bwd.clear();
    workset.clear();
}


bool Bidijkstra::dijkstra_step(const Digraph &gr, IntHeap &queue,
                               std::vector<int64_t> &dist,
                               const std::vector<int64_t> &other_dist)
{
    if (queue.empty())
        return true;

    int64_t vert_dist = queue.top().prio, vert = queue.top().el;
    if (other_dist[vert] < INFTY)
        return true;
    queue.pop();

    workset.push_back(vert);
    dist[vert] = vert_dist;
    for (auto it = gr.adj_cbegin(vert); it < gr.adj_cend(vert); it++)
    {
        int64_t new_prio = vert_dist + it->weight;
        if (dist[it->to] != INFTY)
            continue;
        else if (!queue.hasElement(it->to))
            queue.push(it->to, new_prio);
        else if (queue.priority(it->to) > new_prio)
            queue.decreasePriority(it->to, new_prio);
    }

    return false;
}
