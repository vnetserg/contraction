#include <vector>
#include <math.h>

#include "../include/intheap.hpp"

// PUBLIC

IntHeap::IntHeap(int64_t max_size) : pos(max_size, -1)
{
    heap.reserve(sqrt(max_size));
}

void IntHeap::push(int64_t el, int64_t prio)
{
    pos[el] = heap.size();
    heap.push_back(HeapItem(el, prio));
    swim(heap.size()-1);
}

bool IntHeap::hasElement(int64_t el)
{
    return pos[el] != -1;
}

int64_t IntHeap::priority(int64_t el)
{
    return heap[pos[el]].prio;
}

void IntHeap::decreasePriority(int64_t el, int64_t prio)
{
    int64_t p = pos[el];
    heap[p].prio = prio;
    swim(p);
}

void IntHeap::clear()
{
    for (auto &e : heap)
        pos[e.el] = -1;
    heap.clear();
}

void IntHeap::pop()
{
    pos[heap[0].el] = -1;
    if (heap.size() > 1)
    {
        heap[0] = heap[heap.size()-1];
        pos[heap[0].el] = 0;
    }
    heap.pop_back();
    if (!heap.empty())
    {
        sink(0);
    }
}

IntHeap::HeapItem IntHeap::top()
{
    return heap[0];
}

std::vector<IntHeap::HeapItem>::const_iterator IntHeap::cbegin() const
{
    return heap.cbegin();
}

std::vector<IntHeap::HeapItem>::const_iterator IntHeap::cend() const
{
    return heap.cend();
}

bool IntHeap::empty()
{
    return heap.empty();
}


// PRIVATE

void IntHeap::swim(int64_t i)
{
    while (i > 0 && heap[parent(i)].prio > heap[i].prio)
    {
        swap(i, parent(i));
        i = parent(i);
    }
}

void IntHeap::sink(int64_t i)
{
    while(true)
    {
        int64_t c1 = child(i), c2 = c1+1;
        int64_t min = i;
        if (c1 < heap.size() && heap[c1].prio < heap[min].prio)
            min = c1;
        if (c2 < heap.size() && heap[c2].prio < heap[min].prio)
            min = c2;
        if (min != i)
        {
            swap(i, min);
            i = min;
        }
        else
            return;
    }

}

inline int64_t IntHeap::parent(int64_t i)
{
    return (i-1)/2;
}

inline int64_t IntHeap::child(int64_t i)
{
    return 2*i + 1;
}

inline void IntHeap::swap(int64_t i, int64_t j)
{
    pos[heap[i].el] = j;
    pos[heap[j].el] = i;
    std::swap(heap[i], heap[j]);
}
