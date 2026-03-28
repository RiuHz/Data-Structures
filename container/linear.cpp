
namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool LinearContainer<Data>::operator == (const LinearContainer<Data> & container) const noexcept {
  if (size != container.size)
    return false;

  for (unsigned long index = 0; index < size; index++)
    if (operator[](index) != container[index])
      return false;

  return true;
}

/* ************************************************************************** */

template <typename Data>
inline const Data & LinearContainer<Data>::Front() const {
  if (this -> Empty())
    throw std::length_error("Struttura vuota");

  return operator[](0);
}

template <typename Data>
inline const Data & LinearContainer<Data>::Back() const {
  if (this -> Empty())
    throw std::length_error("Struttura vuota");

  return operator[](size - 1);
}

/* ************************************************************************** */

template <typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun traverseFunction) const {
  if ( !(this -> Empty()) )
    for (unsigned long index = 0; index < size; traverseFunction(operator[](index++)));
}

template <typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun traverseFunction) const {
  if ( !(this -> Empty()) )
    for (unsigned long index = size; index > 0; traverseFunction(operator[](--index)));
}

/* ************************************************************************** */

template <typename Data>
inline Data & MutableLinearContainer<Data>::Front() {
  if (this -> Empty())
    throw std::length_error("Struttura vuota");

  return operator[](0);
}

template <typename Data>
inline Data & MutableLinearContainer<Data>::Back() {
  if (this -> Empty())
    throw std::length_error("Struttura vuota");

  return operator[](size - 1);
}

/* ************************************************************************** */

template <typename Data>
inline void MutableLinearContainer<Data>::PreOrderMap(MapFun mapFunction) {
  if ( !(this -> Empty()) )
    for (unsigned long index = 0; index < size; mapFunction(operator[](index++)));
}

template <typename Data>
inline void MutableLinearContainer<Data>::PostOrderMap(MapFun mapFunction) {
  if ( !(this -> Empty()) )
    for (unsigned long index = size; index > 0; mapFunction(operator[](--index)));
}

/* ************************************************************************** */

template <typename Data>
void SortableLinearContainer<Data>::InsertionSort() noexcept {
  for (unsigned long j = 1; j < size; j++) {
    Data pivot = std::move(this -> operator[](j));

    unsigned long i = j - 1;

    while (i != invalidIndex && this -> operator[](i) > pivot) {
      this -> operator[](i + 1) = std::move(this -> operator[](i));

      i--;
    }
    
    this -> operator[](i + 1) = std::move(pivot);
  }
}

/* ************************************************************************** */

}
