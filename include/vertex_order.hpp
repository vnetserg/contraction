#ifndef VERTEXORDER_H
#define VERTEXORDER_H

#include "digraph.hpp"


class VertexOrder
{
public:
    VertexOrder(Digraph* graph);
    std::vector<int64_t>::const_iterator cbegin();
    std::vector<int64_t>::const_iterator cend();

private:
    std::vector<int64_t> order;
};

#endif // VERTEXORDER_H
