class VertexOrder;

#ifndef VERTEXORDER_H
#define VERTEXORDER_H

#include "digraph.hpp"


class VertexOrder
{
public:
    VertexOrder(Digraph *graph);
    std::vector<int64_t>::const_iterator begin() const;
    std::vector<int64_t>::const_iterator end() const;
    int64_t size() const;
    int64_t operator[](int64_t i) const;

private:
    std::vector<int64_t> order;
};

#endif // VERTEXORDER_H
