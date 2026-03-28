
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec: virtual public Heap<Data>, virtual protected Vector<Data> {
  // Must extend Heap<Data>,
  // Could extend Vector<Data>

private:

  // ...

protected:

  // using Container::???;
  using Container::size;
  using Vector<Data>::Elements;
  using LinearContainer<Data>::invalidIndex;
  // ...

public:

  // Default constructor
  // HeapVec() specifiers;
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  // HeapVec(argument) specifiers; // A heap obtained from a TraversableContainer
  HeapVec(const TraversableContainer<Data> & traversableContainer) : Vector<Data>(traversableContainer) { Heapify(); }
  // HeapVec(argument) specifiers; // A heap obtained from a MappableContainer
  HeapVec(MappableContainer<Data> && mappableContainer) noexcept : Vector<Data>(std::move(mappableContainer)) { Heapify(); }

  /* ************************************************************************ */

  // Copy constructor
  // HeapVec(argument) specifiers;
  HeapVec(const HeapVec & copyHeapVec) : Vector<Data>(copyHeapVec) {}

  // Move constructor
  // HeapVec(argument) specifiers;
  HeapVec(HeapVec && moveHeapVec) noexcept : Vector<Data>(std::move(moveHeapVec)) {}

  /* ************************************************************************ */

  // Destructor
  // ~HeapVec() specifiers;
  virtual ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  HeapVec & operator = (const HeapVec &);

  // Move assignment
  // type operator=(argument) specifiers;
  HeapVec & operator = (HeapVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  bool operator == (const HeapVec & heapVec) const noexcept { return Vector<Data>::operator == (heapVec); }
  inline bool operator != (const HeapVec & heapVec) const noexcept { return !( *(this) == heapVec ); }

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  // type IsHeap(argument) specifiers; // Override Heap member
  virtual const bool IsHeap() const noexcept override;

  // type Heapify(argument) specifiers; // Override Heap member
  virtual inline void Heapify() noexcept override { for (unsigned long index = (size >> 1); index > 0; Heapify(size, --index)); }

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  // type Sort(argument) specifiers; // Override SortableLinearContainer member
  virtual inline void Sort() noexcept override;

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
  using Vector<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

  inline const unsigned long LeftNode(const unsigned long index) const noexcept { return (2 * index) + 1; }
  
  inline const unsigned long RightNode(const unsigned long index) const noexcept { return (2 * index) + 2; }

  virtual void Heapify(const unsigned long, const unsigned long) noexcept;

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
