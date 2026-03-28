
namespace lasd {

/* ************************************************************************** */

template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data> & container) : SetVec<Data>() {
    container.Traverse(
        [this] (const Data & element) {
            Insert(element);
        }
    );
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data> && container) noexcept : SetVec<Data>() {
    container.Map(
        [this] (Data & element) {
            Insert(std::move(element));
        }
    );
}

/* ************************************************************************** */

template <typename Data>
SetVec<Data>::SetVec(const SetVec & copySet) {
    head = copySet.head;
    size = copySet.size;
    capacity = copySet.capacity;
    Elements = new Data[capacity] {};

    for (unsigned long index = 0; index < size; index++)
        Elements[getSetIndex(index)] = copySet.Elements[getSetIndex(index)];
}

template <typename Data>
SetVec<Data>::SetVec(SetVec && moveSet) noexcept {
    std::swap(size, moveSet.size);
    std::swap(Elements, moveSet.Elements);
    std::swap(capacity, moveSet.capacity);
    std::swap(head, moveSet.head);
}

/* ************************************************************************** */

template <typename Data>
SetVec<Data> & SetVec<Data>::operator = (const SetVec & copySet) {
    SetVec<Data> tempSet(copySet);
    std::swap(*this, tempSet);

    return *this;
}

template <typename Data>
SetVec<Data> & SetVec<Data>::operator = (SetVec && moveSet) noexcept {
    std::swap(size, moveSet.size);
    std::swap(Elements, moveSet.Elements);
    std::swap(capacity, moveSet.capacity);
    std::swap(head, moveSet.head);

    return *this;
}

/* ************************************************************************** */

template <typename Data>
bool SetVec<Data>::operator == (const SetVec & setVector) const noexcept {
    if (size != setVector.size)
        return false;
    
    for (unsigned long index = 0; index < size; index++)
        if (operator[](index) != setVector.operator[](index))
            return false;
    
    return true;
}

/* ************************************************************************** */

template <typename Data>
inline const Data & SetVec<Data>::Min() const {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    return operator[](0);
}

template <typename Data>
Data SetVec<Data>::MinNRemove() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    Data element = std::move(Elements[getSetIndex(0)]);
    
    incrementHead();
    size--;

    return element;
}

template <typename Data>
void SetVec<Data>::RemoveMin() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    incrementHead();
    size--;
}

template <typename Data>
inline const Data & SetVec<Data>::Max() const {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    return operator[](size - 1);
}

template <typename Data>
Data SetVec<Data>::MaxNRemove() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    Data element = std::move(Elements[getSetIndex(size - 1)]);
    size--;

    return element;
}

template <typename Data>
void SetVec<Data>::RemoveMax() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    size--;
}

/* ************************************************************************** */

template <typename Data>
const Data & SetVec<Data>::Predecessor(const Data & element) const {
    if (this -> Empty())
        throw std::length_error("Predecessore non trovato");

    unsigned long index = Search(element);

    if (!isValidIndex(index) || isntValidPredecessor(index, element))
        throw std::length_error("Predecessore non trovato");
    
    return (containsElement(index, element) ? operator[](index - 1) : operator[](index));
}

template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data & element) {
    if (this -> Empty())
        throw std::length_error("Predecessore non trovato");

    unsigned long index = Search(element);

    if (!isValidIndex(index) || isntValidPredecessor(index, element))
        throw std::length_error("Predecessore non trovato");

    index = (containsElement(index, element) ? index - 1 : index);

    Data predecessor = std::move(Elements[getSetIndex(index)]);
    Remove(index);

    return predecessor;
}

template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data & element) {
    if (this -> Empty())
        throw std::length_error("Predecessore non trovato");

    unsigned long index = Search(element);

    if (!isValidIndex(index) || isntValidPredecessor(index, element))
        throw std::length_error("Predecessore non trovato");

    index = (containsElement(index, element) ? index - 1 : index);
    Remove(index);
}

template <typename Data>
const Data & SetVec<Data>::Successor(const Data & element) const {
    if (this -> Empty())
        throw std::length_error("Successore non trovato");

    unsigned long index = Search(element);

    if (isGreatestInSet(index))
        throw std::length_error("Successore non trovato");

    return operator[](index + 1);
}

template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data & element) {
    if (this -> Empty())
        throw std::length_error("Successore non trovato");

    unsigned long index = Search(element);

    if (isGreatestInSet(index))
        throw std::length_error("Successore non trovato");

    Data successor = std::move(Elements[getSetIndex(index + 1)]);
    Remove(index + 1);

    return successor;
}

template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data & element) {
    if (this -> Empty())
        throw std::length_error("Successore non trovato");

    unsigned long index = Search(element);

    if (isGreatestInSet(index))
        throw std::length_error("Successore non trovato");

    Remove(index + 1);
}

/* ************************************************************************** */

template<typename Data>
bool SetVec<Data>::Insert(const Data & element){
    unsigned long index = Search(element);

    if (isValidIndex(index) && operator[](index) == element)
        return false;

    if (setIsFull())
        Resize(capacity << 1);

    if (!isValidIndex(index))
        InsertAtBack(element);
    else if (isGreatestInSet(index))
        InsertAtFront(element);
    else if (hasLessElementsBefore(index))
        InsertLeftHalf(index, element);
    else
        InsertRightHalf(index, element);

    size++;
    
    return true;
}

template<typename Data>
bool SetVec<Data>::Insert(Data && element){
    unsigned long index = Search(element);

    if (isValidIndex(index) && operator[](index) == element )
        return false;
    
    if (setIsFull())
        Resize(capacity << 1);

    if (!isValidIndex(index))
        InsertAtBack(std::move(element));
    else if (isGreatestInSet(index))
        InsertAtFront(std::move(element));
    else if (hasLessElementsBefore(index))
        InsertLeftHalf(index, std::move(element));
    else
        InsertRightHalf(index, std::move(element));

    size++;
    
    return true;
}

template <typename Data>
bool SetVec<Data>::Remove(const Data & element) noexcept {
    if (this -> Empty())
        return false;
    
    unsigned long index = Search(element);

    if (!isValidIndex(index) || operator[](index) != element)
        return false;

    Remove(index);

    if (isEligibleForReduce())
        Resize(capacity >> 1);

    return true;
}

/* ************************************************************************** */

template <typename Data>
const Data & SetVec<Data>::operator[](const unsigned long index) const {
    if (index >= size)
        throw std::out_of_range("Indice non valido");

    return Elements[getSetIndex(index)];
}

/* ************************************************************************** */

template<typename Data>
bool SetVec<Data>::Exists(const Data & element) const noexcept{
    unsigned long index = Search(element);

    if (isValidIndex(index) && operator[](index) == element)
        return true;
    
    return false;
}

/* ************************************************************************** */

template <typename Data>
inline void SetVec<Data>::Clear() {
    if (capacity != 16) {
        delete[] Elements;
        capacity = 16;
        Elements = new Data[capacity] {};
    }
    head = size = 0;
}

/* ************************************************************************** */

template <typename Data>
SetVec<Data>::SetVec(const unsigned long newCapacity) {
    capacity = newCapacity;
    Elements = new Data[capacity] {};
}

template <typename Data>
const unsigned long SetVec<Data>::Search(const Data & element) const noexcept {
    unsigned long i = 0;
    unsigned long j = size - 1;
    
    while(i <= j && j != invalidIndex){
        unsigned long q = (i + j) / 2;

        if (operator[](q) == element)
            return q;
        else if(operator[](q) < element)
            i = q + 1;
        else
            j = q - 1;
    }

    return j;
}

template <typename Data>
void SetVec<Data>::Resize(const unsigned long newCapacity) {
    SetVec<Data> tempSet(newCapacity);

    for (unsigned long index = 0; index < size; index++)
        std::swap(Elements[getSetIndex(index)], tempSet.Elements[index]);

    std::swap(Elements, tempSet.Elements);
    capacity = newCapacity;
    head = 0;
}

template <typename Data>
inline void SetVec<Data>::InsertAtBack(const Data & element) noexcept {
    decrementHead();
    Elements[getSetIndex(0)] = element;
}

template <typename Data>
inline void SetVec<Data>::InsertAtFront(const Data & element) noexcept {
    Elements[getSetIndex(size)] = element;
}

template <typename Data>
inline void SetVec<Data>::InsertLeftHalf(const unsigned long index, const Data & element) noexcept {
    decrementHead();
    LeftShift(1, index + 1);
    Elements[getSetIndex(index + 1)] = element;
}

template <typename Data>
inline void SetVec<Data>::InsertRightHalf(const unsigned long index, const Data & element) noexcept {
    RightShift(index + 1, size - 1);
    Elements[getSetIndex(index + 1)] = element;
}

template <typename Data>
inline void SetVec<Data>::InsertAtBack(const Data && element) noexcept {
    decrementHead();
    Elements[getSetIndex(0)] = std::move(element);
}

template <typename Data>
inline void SetVec<Data>::InsertAtFront(const Data && element) noexcept {
    Elements[getSetIndex(size)] = std::move(element);
}

template <typename Data>
inline void SetVec<Data>::InsertLeftHalf(const unsigned long index, const Data && element) noexcept {
    decrementHead();
    LeftShift(1, index + 1);
    Elements[getSetIndex(index + 1)] = std::move(element);
}

template <typename Data>
inline void SetVec<Data>::InsertRightHalf(const unsigned long index, const Data && element) noexcept {
    RightShift(index + 1, size - 1);
    Elements[getSetIndex(index + 1)] = std::move(element);
}

template <typename Data>
void SetVec<Data>::Remove(const unsigned long index) noexcept {
    if (index == 0)
        incrementHead();
    else if (hasLessElementsBefore(index)) {
        RightShift(0, index - 1);
        incrementHead();
    } else
        LeftShift(index + 1, size - 1);

    size--;
}

template <typename Data>
inline void SetVec<Data>::LeftShift(const unsigned long start, const unsigned long end) noexcept {
    for (unsigned long index = start; index <= end; index++)
        std::swap(Elements[getSetIndex(index - 1)], Elements[getSetIndex(index)]);
}

template <typename Data>
inline void SetVec<Data>::RightShift(const unsigned long start, const unsigned long end) noexcept {
    for (unsigned long index = end; index >= start && isValidIndex(index); index--)
        std::swap(Elements[getSetIndex(index + 1)], Elements[getSetIndex(index)]);
}

/* ************************************************************************** */

}
