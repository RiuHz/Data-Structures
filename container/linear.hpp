
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"
#include <limits.h>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer: virtual public PreOrderTraversableContainer<Data>, virtual public PostOrderTraversableContainer<Data> {
  // Must extend PreOrderTraversableContainer<Data>,
  //             PostOrderTraversableContainer<Data>

private:

protected:

  using Container::size;
  static constexpr auto invalidIndex = ULONG_MAX;
  // ...

public:

  // Destructor
  // ~LinearContainer() specifiers
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  LinearContainer &operator = (const LinearContainer &) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  LinearContainer &operator = (LinearContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types is possible.
  bool operator == (const LinearContainer &) const noexcept;
  inline bool operator != (const LinearContainer & container) const noexcept { return !( *(this) == container ); }
  
  /* ************************************************************************ */

  // Specific member functions

  // type operator[](argument) specifiers; // (non-mutable version; concrete function must throw std::out_of_range when out of range)
  virtual const Data & operator[](const unsigned long) const = 0;

  // type Front() specifiers; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual inline const Data & Front() const;

  // type Back() specifiers; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual inline const Data & Back() const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // using typename TraversableContainer<Data>::TraverseFun;
  using typename TraversableContainer<Data>::TraverseFun;

  // type Traverse(argument) specifiers; // Override TraversableContainer member
  inline void Traverse(TraverseFun traverseFunction) const override { PreOrderTraverse(traverseFunction); }

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  // type PreOrderTraverse(argument) specifiers; // Override PreOrderTraversableContainer member
  inline void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  // type PostOrderTraverse(argument) specifiers; // Override PostOrderTraversableContainer member
  inline void PostOrderTraverse(TraverseFun) const override;

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer: virtual public LinearContainer<Data>, virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data> {
  // Must extend LinearContainer<Data>,
  //             PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>

private:

  // ...

protected:

  using Container::size;

  // ...

public:

  // Destructor
  // ~MutableLinearContainer() specifiers
  virtual ~MutableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  MutableLinearContainer &operator = (const MutableLinearContainer &) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  MutableLinearContainer &operator = (MutableLinearContainer &&) noexcept = delete;
  /* ************************************************************************ */

  // type operator[](argument) specifiers; // (non-mutable version; concrete function must throw std::out_of_range when out of range)
  using LinearContainer<Data>::operator[];

  // type Front() specifiers; // (non-mutable version; concrete function must throw std::length_error when empty)
  using LinearContainer<Data>::Front;

  // type Back() specifiers; // (non-mutable version; concrete function must throw std::length_error when empty)
  using LinearContainer<Data>::Back;

  /* ************************************************************************ */

  // Specific member functions

  // type operator[](argument) specifiers; // (mutable version; concrete function must throw std::out_of_range when out of range)
  virtual Data & operator[](const unsigned long) = 0;

  // type Front() specifiers; // (mutable version; concrete function must throw std::length_error when empty)
  virtual inline Data & Front();

  // type Back() specifiers; // (mutable version; concrete function must throw std::length_error when empty)
  virtual inline Data & Back();

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  // using typename MappableContainer<Data>::MapFun;
  using typename MappableContainer<Data>::MapFun;

  // type Map(argument) specifiers; // Override MappableContainer member
  inline void Map(MapFun mapFunction) override { PreOrderMap(mapFunction); }

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  // type PreOrderMap(argument) specifiers; // Override PreOrderMappableContainer member
  inline void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  // type PostOrderMap(argument) specifiers; // Override PostOrderMappableContainer member
  inline void PostOrderMap(MapFun) override;

};

template <typename Data>
class SortableLinearContainer: virtual public MutableLinearContainer<Data> {
  // Must extend MutableLinearContainer<Data>

private:

  // ...

protected:

  using Container::size;
  using LinearContainer<Data>::invalidIndex;

  // ...

public:

  // Destructor
  // ~SortableLinearContainer() specifiers
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  SortableLinearContainer &operator = (const SortableLinearContainer &) = delete; 

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not be possible.
  SortableLinearContainer &operator = (SortableLinearContainer &&) = delete;

  /* ************************************************************************ */

  // Specific member function

  // type Sort() specifiers;
  virtual inline void Sort() noexcept { InsertionSort(); }

protected:

  // Auxiliary member functions

  void InsertionSort() noexcept;

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
