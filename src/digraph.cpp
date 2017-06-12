#include "../include/digraph.hpp"

// PUBLIC

Digraph::Digraph(int64_t n_vert) :
    vert_edges(new std::vector<std::vector<Edge>>(n_vert)),
    reverse_vert_edges(new std::vector<std::vector<Edge>>(n_vert))
{}

Digraph::~Digraph()
{
    vert_edges.reset();
    reverse_vert_edges.reset();
}

Digraph* Digraph::reversed()
{
    return new Digraph(reverse_vert_edges, vert_edges);
}

Digraph* Digraph::copy()
{
    Digraph *graph = new Digraph(0);
    graph->vert_edges = vert_edges;
    graph->reverse_vert_edges = reverse_vert_edges;
    return graph;
}

void Digraph::addEdge(int64_t from, int64_t to, int64_t weight)
{
    (*vert_edges)[from].push_back(Edge(from, to, weight));
    (*reverse_vert_edges)[to].push_back(Edge(to, from, weight));
}

void Digraph::removeVertex(int64_t v)
{
    (*vert_edges)[v].clear();
    (*reverse_vert_edges)[v].clear();
}

void Digraph::leaveUpwardEdges(const VertexOrder &order)
{
    std::vector<int64_t> vert_index(order.size());
    for (int64_t i = 0; i < order.size(); i++)
        vert_index[order[i]] = i;

    for (int64_t i = 0; i < vert_edges->size(); i++)
    {
        std::vector<Digraph::Edge> up_edges;
        for (const Digraph::Edge &e : (*vert_edges)[i])
            if (vert_index[e.from] < vert_index[e.to])
                up_edges.push_back(e);

        (*vert_edges)[i] = up_edges;
        (*reverse_vert_edges)[i].clear();
        for (const Digraph::Edge &e : (*vert_edges)[i])
            (*reverse_vert_edges)[i].push_back(e.reversed());
    }
}

std::vector<Digraph::Edge>::const_iterator Digraph::adj_cbegin(int64_t vert) const
{
    return (*vert_edges)[vert].cbegin();
}

std::vector<Digraph::Edge>::const_iterator Digraph::adj_cend(int64_t vert) const
{
    return (*vert_edges)[vert].cend();
}

int64_t Digraph::vertices()
{
    return vert_edges->size();
}

std::istream& operator>>(std::istream &cin, Digraph &graph)
{
    std::string word;
    int64_t n_edges = 1;
    while (n_edges)
    {
        cin >> word;
        if (word.compare("p") == 0)
        {
            int64_t n_vert;
            cin >> word >> n_vert >> n_edges;
            graph.vert_edges->resize(n_vert);
            graph.reverse_vert_edges->resize(n_vert);
        }
        else if (word.compare("a") == 0)
        {
            int64_t v1, v2, w;
            cin >> v1 >> v2 >> w;
            graph.addEdge(v1-1, v2-1, w);
            n_edges--;
        }
        else
            std::getline(cin, word);
    }

    return cin;
}

// PRIVATE

Digraph::Digraph(std::shared_ptr< std::vector< std::vector<Edge> > > vert_edges,
        std::shared_ptr< std::vector< std::vector<Edge> > > reverse_vert_edges)
    : vert_edges(vert_edges), reverse_vert_edges(reverse_vert_edges)
{}
