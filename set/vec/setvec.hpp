
#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec: virtual public Set<Data>, virtual protected ResizableContainer {
  // Must extend Set<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  // using Container::???;
  using Container::size;
  using LinearContainer<Data>::invalidIndex;
  Data * Elements = nullptr;
  unsigned long capacity = 0;
  unsigned long head = 0;

public:

  // Default constructor
  // SetVec() specifiers;
  SetVec() : SetVec<Data>(16) {}

  /* ************************************************************************ */

  // Specific constructors
  // SetVec(argument) specifiers; // A set obtained from a TraversableContainer
  SetVec(const TraversableContainer<Data> &);
  // SetVec(argument) specifiers; // A set obtained from a MappableContainer
  SetVec(MappableContainer<Data> &&) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  // SetVec(argument) specifiers;
  SetVec(const SetVec & copySet);

  // Move constructor
  // SetVec(argument) specifiers;
  SetVec(SetVec && moveSet) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~SetVec() specifiers;
  virtual ~SetVec() { delete[] Elements; }

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  SetVec & operator = (const SetVec &);

  // Move assignment
  // type operator=(argument) specifiers;
  SetVec & operator = (SetVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  bool operator == (const SetVec &) const noexcept;
  inline bool operator != (const SetVec & setVector) const noexcept { return !( *(this) == setVector); }

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  // type Min(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  inline const Data & Min() const override;
  // type MinNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MinNRemove() override;
  // type RemoveMin(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMin() override;

  // type Max(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  inline const Data & Max() const override;
  // type MaxNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MaxNRemove() override;
  // type RemoveMax(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMax() override;

  // type Predecessor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  const Data & Predecessor(const Data &) const override;
  // type PredecessorNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data &) override;
  // type RemovePredecessor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data &) override;

  // type Successor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  const Data & Successor(const Data &) const override;
  // type SuccessorNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data &) override;
  // type RemoveSuccessor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data &) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  // type Insert(argument) specifiers; // Override DictionaryContainer member (copy of the value)
  bool Insert(const Data &) override;
  // type Insert(argument) specifiers; // Override DictionaryContainer member (move of the value)
  bool Insert(Data &&) override;
  // type Remove(argument) specifiers; // Override DictionaryContainer member
  bool Remove(const Data &) noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // type operator[](argument) specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)
  const Data & operator[](const unsigned long) const override;

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  // type Exists(argument) specifiers; // Override TestableContainer member
  bool Exists(const Data &) const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
  inline void Clear() override;

protected:

  // Auxiliary functions, if necessary!

  SetVec(const unsigned long);

  const unsigned long Search(const Data &) const noexcept;

  void Resize(const unsigned long nuovaDimensione) override;

  inline void InsertAtBack(const Data &) noexcept;

  inline void InsertAtFront(const Data &) noexcept;

  inline void InsertLeftHalf(const unsigned long, const Data &) noexcept;

  inline void InsertRightHalf(const unsigned long, const Data &) noexcept;

  inline void InsertAtBack(const Data &&) noexcept;

  inline void InsertAtFront(const Data &&) noexcept;

  inline void InsertLeftHalf(const unsigned long, const Data &&) noexcept;

  inline void InsertRightHalf(const unsigned long, const Data &&) noexcept;

  void Remove(const unsigned long) noexcept;

  inline void LeftShift(const unsigned long, const unsigned long) noexcept;

  inline void RightShift(const unsigned long, const unsigned long) noexcept;

  inline void incrementHead() noexcept { (head == capacity - 1) ? head = 0 : head++; }
  
  inline void decrementHead() noexcept { (head == 0) ? head = capacity - 1 : head--; }
  
  inline const unsigned long getSetIndex(const unsigned long index) const noexcept { return (head + index) % capacity; }
  
  inline const bool isValidIndex(const unsigned long index) const noexcept { return index != invalidIndex; }

  inline const bool containsElement(const unsigned long index, const Data & element) const noexcept {return (operator[](index) == element); }

  inline const bool hasLessElementsBefore(const unsigned long index) const noexcept { return index < (size >> 1); }

  inline const bool isGreatestInSet(const unsigned long index) const noexcept { return index == size - 1; }

  inline const bool isntValidPredecessor(const unsigned long index, const Data & element) const noexcept { return index == 0 && operator[](index) == element; }

  inline const bool setIsFull() const noexcept { return size == capacity; }

  inline const bool isEligibleForReduce() const noexcept { return size <= (capacity >> 2) && (capacity >> 1) >= 16; }

};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif
