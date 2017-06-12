#include "../include/contraction_hierarchies.hpp"


ContractionHierarchies::ContractionHierarchies(Digraph* source_graph)
{
    VertexOrder order(source_graph);

    graph = source_graph->copy();

    Digraph *tmp_graph = source_graph->copy();
    Digraph *tmp_regraph = tmp_graph->reversed();
    DijkstraWitness witness(tmp_graph, WITNESS_MAX_HOPS);

    for (const int64_t &v : order)
    {
        for (auto pred_it = tmp_regraph->adj_cbegin(v); pred_it < tmp_regraph->adj_cend(v); ++pred_it)
        {
            Digraph::Edge pred_edge = pred_it->reversed();
            std::vector<int64_t> dst;
            int64_t dist_limit = INFTY;

            for (auto suc_it = tmp_graph->adj_cbegin(v); suc_it < tmp_graph->adj_cend(v); ++suc_it)
            {
                Digraph::Edge suc_edge = *suc_it;
                dist_limit = std::min(dist_limit, pred_edge.weight + suc_edge.weight);
                dst.push_back(suc_edge.to);
            }

            std::vector<int64_t> dist_to = witness.query(pred_edge.from, dst, dist_limit);

            int64_t i = 0;
            for (auto suc_it = tmp_graph->adj_cbegin(v); suc_it < tmp_graph->adj_cend(v); ++suc_it)
            {
                Digraph::Edge suc_edge = *suc_it;
                if (dist_to[i] == INFTY || dist_to[i] > suc_edge.weight + pred_edge.weight)
                {
                    tmp_graph->addEdge(pred_edge.from, suc_edge.to, pred_edge.weight + suc_edge.weight);
                    graph->addEdge(pred_edge.from, suc_edge.to, pred_edge.weight + suc_edge.weight);
                }
                i++;
            }
        }
        
        tmp_graph->removeVertex(v);
    }

    delete tmp_graph;
    delete tmp_regraph;

    Digraph *t = regraph->reversed();
    regraph = t->copy();
    delete t;

    graph->leaveUpwardEdges(order);
    regraph->leaveUpwardEdges(order);
}

ContractionHierarchies::~ContractionHierarchies()
{
    delete graph;
    delete regraph;
}

int64_t ContractionHierarchies::query(int64_t src, int64_t dst)
{
    return -1;
}
