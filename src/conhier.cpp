#include <iostream>
#include "../include/contraction_hierarchies.hpp"

int32_t main()
{
    Digraph graph;
    std::cin >> graph;

    ContractionHierarchies cont(&graph);

    std::cout << "Ready" << std::endl;
    std::cout.flush();

    int64_t n_queries;
    std::cin >> n_queries;
    for (int64_t i = 0; i < n_queries; i++)
    {
        int64_t src, dst, dist;
        std::cin >> src >> dst;
        dist = cont.query(src-1, dst-1);
        if (dist == INFTY)
            std::cout << -1 << std::endl;
        else
            std::cout << dist << std::endl;
    }

    return 0;
}
