
namespace lasd {

/* ************************************************************************** */

template <typename Data>
Vector<Data>::Vector(const unsigned long & newSize) {
    size = newSize;
    Elements = new Data[size] {};
}

template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data> & container) : Vector<Data>(container.Size()) {
    unsigned long index = 0;

    container.Traverse(
        [this, &index] (const Data & data) {
            Elements[index++] = data;
        }
    );
}

template <typename Data>
Vector<Data>::Vector(MappableContainer<Data> && container) : Vector<Data>(container.Size()) {
    unsigned long index = 0;

    container.Map(
        [this, &index] (Data & data) {
            Elements[index++] = std::move(data);
        }
    );
}

/* ************************************************************************** */

template <typename Data>
Vector<Data>::Vector(const Vector<Data> & copyVector) {
    size = copyVector.size;
    Elements = new Data[size] {};
    std::copy(copyVector.Elements, copyVector.Elements + size, Elements);
}

template <typename Data>
Vector<Data>::Vector(Vector<Data> && moveVector) noexcept {
    std::swap(size, moveVector.size);
    std::swap(Elements, moveVector.Elements);
}

/* ************************************************************************** */

template <typename Data>
Vector<Data> & Vector<Data>::operator = (const Vector<Data> & copyVector) {
    Vector<Data> tempVector(copyVector);
    std::swap(*this, tempVector);

    return *this;
}

template <typename Data>
Vector<Data> & Vector<Data>::operator = (Vector<Data> && moveVector) noexcept {
    std::swap(size, moveVector.size);
    std::swap(Elements, moveVector.Elements);
    
    return *this;
}

/* ************************************************************************** */

template <typename Data>
bool Vector<Data>::operator == (const Vector<Data> & vector) const noexcept {
    if (size != vector.size)
        return false;

    for (unsigned long index = 0; index < size; index++)
        if (Elements[index] != vector.Elements[index])
            return false;

    return true;
}

/* ************************************************************************** */

template <typename Data>
inline Data & Vector<Data>::operator[](const unsigned long index) {
    if (index >= size)
        throw std::out_of_range("Indice non valido");

    return Elements[index];
}

template <typename Data>
inline Data & Vector<Data>::Front() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    return Elements[0];
}

template <typename Data>
inline Data & Vector<Data>::Back() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    return Elements[size - 1];
}

/* ************************************************************************** */

template <typename Data>
inline const Data & Vector<Data>::operator[](const unsigned long index) const {
    if (index >= size)
        throw std::out_of_range("Indice non valido");

    return Elements[index];
}

template <typename Data>
inline const Data & Vector<Data>::Front() const {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    return Elements[0];
}

template <typename Data>
inline const Data & Vector<Data>::Back() const {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    return Elements[size - 1];
}

/* ************************************************************************** */

template <typename Data>
void Vector<Data>::Resize(const unsigned long newSize) {
    if (newSize == 0)
        return Clear();
    else if (size == newSize)
        return;
    
    Vector<Data> tempVec(newSize);
    unsigned long minSize = (size < newSize) ? size : newSize;

    for (unsigned long index = 0; index < minSize; index++)
        std::swap(Elements[index], tempVec[index]);

    std::swap(Elements, tempVec.Elements);
    size = newSize;
}

template <typename Data>
inline void Vector<Data>::Clear() {
    size = 0;
    delete[] Elements;
    Elements = nullptr;
}

/* ************************************************************************** */

template <typename Data>
SortableVector<Data> & SortableVector<Data>::operator = (const SortableVector & vector) {
    Vector<Data>::operator = (vector);
    return *this;
}

template <typename Data>
SortableVector<Data> & SortableVector<Data>::operator = (SortableVector && vector) noexcept {
    Vector<Data>::operator = (std::move(vector));
    return *this;
}

/* ************************************************************************** */

}
