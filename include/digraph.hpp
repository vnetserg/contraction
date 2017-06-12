#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>

class Digraph
{
public:

    struct Edge
    {
        int64_t from, to, weight;

        Edge(int64_t v, int64_t u, int64_t w)
            : from(v), to(u), weight(w) {}
    };

    Digraph(int64_t n_vert = 0);

    ~Digraph();

    Digraph* reversed();

    void addEdge(int64_t from, int64_t to, int64_t weight);

    std::vector<Edge>::const_iterator adj_cbegin(int64_t vert) const;

    std::vector<Edge>::const_iterator adj_cend(int64_t vert) const;

    int64_t vertices();

    friend std::istream& operator>>(std::istream &cin, Digraph &graph);

private:

    Digraph(std::shared_ptr< std::vector< std::vector<Edge> > > vert_edges,
            std::shared_ptr< std::vector< std::vector<Edge> > > reverse_vert_edges);

    std::shared_ptr< std::vector< std::vector<Edge> > > vert_edges, reverse_vert_edges;
};

#endif // DIGRAPH_H
