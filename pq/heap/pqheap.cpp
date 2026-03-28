
namespace lasd {

/* ************************************************************************** */

template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data> & traversableContainer) : Vector<Data>(traversableContainer) {
    capacity = size;

    if (capacity < 16)
        Resize(16);

    HeapVec<Data>::Heapify();
}

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data> && mappableContainer) noexcept : Vector<Data>(std::move(mappableContainer)) {
    capacity = size;

    if (capacity < 16)
        Resize(16);

    HeapVec<Data>::Heapify();
}

/* ************************************************************************** */

template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap & copyPQHeap) {
    size = copyPQHeap.size;
    capacity = copyPQHeap.capacity;
    Elements = new Data[capacity] {};
    
    for (unsigned long index = 0; index < size; index++)
        Elements[index] = copyPQHeap.Elements[index];
}

template <typename Data>
PQHeap<Data>::PQHeap(PQHeap && movePQHeap) noexcept {
    std::swap(size, movePQHeap.size);
    std::swap(capacity, movePQHeap.capacity);
    std::swap(Elements, movePQHeap.Elements);
}

/* ************************************************************************** */

template <typename Data>
PQHeap<Data> & PQHeap<Data>::operator = (const PQHeap & copyPQHeap) {
    PQHeap<Data> tempPQHeap(copyPQHeap);
    std::swap(*this, tempPQHeap);

    return *this;
}

template <typename Data>
PQHeap<Data> & PQHeap<Data>::operator = (PQHeap && movePQHeap) noexcept {
    std::swap(size, movePQHeap.size);
    std::swap(capacity, movePQHeap.capacity);
    std::swap(Elements, movePQHeap.Elements);

    return *this;
}

/* ************************************************************************** */

template <typename Data>
void PQHeap<Data>::RemoveTip() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    std::swap(Elements[0], Elements[size - 1]);

    size--;

    HeapifyDown(0);

    if (isEligibleForReduce())
        Resize(capacity >> 1);
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    Data data = Elements[0];

    RemoveTip();

    return data;
}

/* ************************************************************************** */

template <typename Data>
void PQHeap<Data>::Insert(const Data & element) {
    if (PQHeapIsFull())
        Resize(capacity << 1);

    Elements[size] = element;
    size++;

    HeapifyUp(size - 1);
}

template <typename Data>
void PQHeap<Data>::Insert(Data && element) {
    if (PQHeapIsFull())
        Resize(capacity << 1);

    Elements[size] = std::move(element);
    size++;

    HeapifyUp(size - 1);
}

/* ************************************************************************** */

template <typename Data>
void PQHeap<Data>::HeapifyUp(const unsigned long index) noexcept {
    if (index == 0)
        return;

    if (Elements[index] > Elements[FatherNode(index)]) {
        std::swap(Elements[index], Elements[FatherNode(index)]);
        HeapifyUp(FatherNode(index));
    }
}

/* ************************************************************************** */

template <typename Data>
inline void PQHeap<Data>::Change(const unsigned long index, const Data & element) {
    if (Vector<Data>::operator[](index) > element) {
        Elements[index] = element;
        HeapifyDown(index);
    } else if (Elements[index] < element) {
        Elements[index] = element;
        HeapifyUp(index);
    }
}

template <typename Data>
inline void PQHeap<Data>::Change(const unsigned long index, Data && element) {
    if (Vector<Data>::operator[](index) > element) {
        Elements[index] = std::move(element);
        HeapifyDown(index);
    } else if (Elements[index] < element) {
        Elements[index] = std::move(element);
        HeapifyUp(index);
    }
}

/* ************************************************************************** */

template <typename Data>
void PQHeap<Data>::Clear() {
    if (capacity != 16) {
        delete[] Elements;
        capacity = 16;
        Elements = new Data[capacity] {};
    }

    size = 0;
}

/* ************************************************************************** */

template <typename Data>
void PQHeap<Data>::Resize(const unsigned long newCapacity) {
    PQHeap<Data> tempPQHeap(newCapacity);

    for (unsigned long index = 0; index < size; index++)
        std::swap(Elements[index], tempPQHeap.Elements[index]);

    std::swap(Elements, tempPQHeap.Elements);
    capacity = newCapacity;
}

/* ************************************************************************** */

}
