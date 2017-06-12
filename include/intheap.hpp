#ifndef INTHEAP_H
#define INTHEAP_H

#include <vector>

class IntHeap
{
public:

    struct HeapItem
    {
        int64_t el, prio;
        HeapItem(int64_t el, int64_t prio) : el(el), prio(prio) {}
    };

    IntHeap(int64_t max_size);

    void push(int64_t el, int64_t prio);

    bool hasElement(int64_t el);

    int64_t priority(int64_t el);

    void decreasePriority(int64_t el, int64_t prio);

    void clear();

    void pop();

    HeapItem top();

    std::vector<HeapItem>::const_iterator cbegin() const;

    std::vector<HeapItem>::const_iterator cend() const;

    bool empty();

private:
    std::vector<int64_t> pos;
    std::vector<HeapItem> heap;

    void swim(int64_t i);

    void sink(int64_t i);

    inline int64_t parent(int64_t i);

    inline int64_t child(int64_t i);

    inline void swap(int64_t i, int64_t j);

};

#endif // INTHEAP_H
