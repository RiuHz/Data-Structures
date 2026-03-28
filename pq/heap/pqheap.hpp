
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap: virtual public PQ<Data>, virtual protected HeapVec<Data> {
  // Must extend PQ<Data>,
  // Could extend HeapVec<Data>

private:

  // ...

protected:

  // using Container::???;
  using Container::size;
  using HeapVec<Data>::Elements;
  unsigned long capacity = 16;
  // ...

public:

  // Default constructor
  // PQHeap() specifiers;
  PQHeap() : PQHeap<Data>(16) {}

  /* ************************************************************************ */

  // Specific constructors
  // PQHeap(argument) specifiers; // A priority queue obtained from a TraversableContainer
  PQHeap(const TraversableContainer<Data> &);
  // PQHeap(argument) specifiers; // A priority queue obtained from a MappableContainer
  PQHeap(MappableContainer<Data> &&) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  // PQHeap(argument) specifiers;
  PQHeap(const PQHeap &);

  // Move constructor
  // PQHeap(argument) specifiers;
  PQHeap(PQHeap &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~PQHeap() specifiers;
  virtual ~PQHeap() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  PQHeap & operator = (const PQHeap &);

  // Move assignment
  // type operator=(argument) specifiers;
  PQHeap & operator = (PQHeap &&) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  // type Tip(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  inline const Data & Tip() override { return Vector<Data>::Front(); }
  // type RemoveTip(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  void RemoveTip() override;
  // type TipNRemove(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  Data TipNRemove() override;

  // type Insert(argument) specifiers; // Override PQ member (Copy of the value)
  void Insert(const Data &) override;
  // type Insert(argument) specifiers; // Override PQ member (Move of the value)
  void Insert(Data &&) override;

  // type Change(argument) specifiers; // Override PQ member (Copy of the value)
  inline void Change(const unsigned long, const Data &) override;
  // type Change(argument) specifiers; // Override PQ member (Move of the value)
  inline void Change(const unsigned long, Data &&) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
  void Clear() override;

protected:

  // Auxiliary functions, if necessary!

  PQHeap(const unsigned long newCapacity) : Vector<Data>(newCapacity) { size = 0; }

  void Resize(const unsigned long) override;

  void HeapifyUp(const unsigned long) noexcept;
  
  inline void HeapifyDown(const unsigned long index) noexcept { HeapVec<Data>::Heapify(size, index); }

  inline const bool PQHeapIsFull() const noexcept { return size == capacity; }

  inline const bool isEligibleForReduce() const noexcept { return size <= (capacity >> 2) && (capacity >> 1) >= 16; }

  inline const unsigned long FatherNode(const unsigned long index) const noexcept { return (index - 1) >> 1; }

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
