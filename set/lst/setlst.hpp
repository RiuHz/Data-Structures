
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetLst: virtual public Set<Data>, virtual protected List<Data> {
  // Must extend Set<Data>,
  //             List<Data>

private:

  // ...

protected:

  // using Container::???;
  using Container::size;
  using List<Data>::head;
  using List<Data>::tail;
  using typename List<Data>::Node;

  // ...

public:

  // Default constructor
  // SetLst() specifiers;
  SetLst() = default;

  /* ************************************************************************ */

  // Specific constructors
  // SetLst(argument) specifiers; // A set obtained from a TraversableContainer
  SetLst(const TraversableContainer<Data> &);
  // SetLst(argument) specifiers; // A set obtained from a MappableContainer
  SetLst(MappableContainer<Data> &&) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  // SetLst(argument) specifiers;
  SetLst(const SetLst & copySet) : List<Data>::List(copySet) {}

  // Move constructor
  // SetLst(argument) specifiers;
  SetLst(SetLst && moveSet) noexcept : List<Data>::List(std::move(moveSet)) {}

  /* ************************************************************************ */

  // Destructor
  // ~SetLst() specifiers;
  virtual ~SetLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  SetLst & operator = (const SetLst &);

  // Move assignment
  // type operator=(argument) specifiers;
  SetLst & operator = (SetLst &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;
  bool operator == (const SetLst & setList) const noexcept { return List<Data>::operator == (setList); }
  bool operator != (const SetLst & setList) const noexcept { return ! ( *(this) == setList ); }

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  // type Min(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  const Data & Min() const override { return List<Data>::Front(); }
  // type MinNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MinNRemove() override { return List<Data>::FrontNRemove(); }
  // type RemoveMin(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMin() override { return List<Data>::RemoveFromFront(); }

  // type Max(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  const Data & Max() const override { return LinearContainer<Data>::Back(); }
  // type MaxNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MaxNRemove() override { return List<Data>::BackNRemove(); }
  // type RemoveMax(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMax() override { return List<Data>::RemoveFromBack(); }

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
  const Data & operator[](const unsigned long index) const override { return List<Data>::operator[](index); };

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  // type Exists(argument) specifiers; // Override TestableContainer member
  bool Exists(const Data &) const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
  void Clear() override { List<Data>::Clear(); }

protected:

  // Auxiliary functions, if necessary!
  List<Data>::Node * const * Reach(Node * const *, const unsigned long) const noexcept;

  List<Data>::Node * const * SearchNode(const Data &) const noexcept;

  List<Data>::Node ** SearchNode(const Data & element) noexcept { return const_cast<Node **>(static_cast<const SetLst<Data> *> (this) -> SearchNode(element) ); }

  List<Data>::Node * const * SearchPredecessor(const Data &) const;

  List<Data>::Node ** SearchPredecessor(const Data & element) { return const_cast<Node **>(static_cast<const SetLst<Data> *> (this) -> SearchPredecessor(element) ); }

  inline void Remove (Node **) noexcept;

  inline const bool isntValidSuccessor(const Node * const * node, const Data & element) const noexcept { return (*node) -> element == element && (*node) -> next == nullptr; }

  inline const bool elementFound(const Node * const * node, const Data & element) const noexcept { return (*node) -> element == element; }

  inline const bool isNodeNull(const Node * const * node) const noexcept { return (*node) == nullptr; }

  inline const bool isSmallestInSet(const Node * const * node) const noexcept { return (*node) == head; }

  inline const bool isGreatestInSet(const Node * const * node) const noexcept { return (*node) == tail; }

};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif
