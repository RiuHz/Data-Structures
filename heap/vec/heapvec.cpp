
namespace lasd {

/* ************************************************************************** */

template <typename Data>
HeapVec<Data> & HeapVec<Data>::operator = (const HeapVec<Data> & copyHeapVec) {
    Vector<Data>::operator = (copyHeapVec);

    return *this;
}

template <typename Data>
HeapVec<Data> & HeapVec<Data>::operator = (HeapVec<Data> && moveHeapVec) noexcept {
    Vector<Data>::operator = (std::move(moveHeapVec));

    return *this;
}

/* ************************************************************************** */

template <typename Data>
const bool HeapVec<Data>::IsHeap() const noexcept {
    for (unsigned long index = 0; index < (size >> 1); index++)
        if ((LeftNode(index) < size && Elements[index] < Elements[LeftNode(index)]) || (RightNode(index) < size && Elements[index] < Elements[RightNode(index)]))
            return false;

    return true;
}

/* ************************************************************************** */

template <typename Data>
void HeapVec<Data>::Heapify(const unsigned long lenght, const unsigned long index) noexcept {
    unsigned long max = index;

    if (LeftNode(index) < lenght && Elements[LeftNode(index)] > Elements[max])
        max = LeftNode(index);

    if (RightNode(index) < lenght && Elements[RightNode(index)] > Elements[max])
        max = RightNode(index);

    if (max != index) {
        std::swap(Elements[max], Elements[index]);
        Heapify(lenght, max);
    }
}

/* ************************************************************************** */

template <typename Data>
inline void HeapVec<Data>::Sort() noexcept {
    Heapify();

    unsigned long length = size;

    for (unsigned long index = size - 1; index > 0 && index != invalidIndex; index--) {
        std::swap(Elements[0], Elements[index]);
        length -= 1;
        Heapify(length, 0);
    }
}

/* ************************************************************************** */

}
