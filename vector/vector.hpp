
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector: virtual public MutableLinearContainer<Data>, virtual public ResizableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  // using Container::???;
  using Container::size;

  Data *Elements = nullptr;

public:

  // Default constructor
  // Vector() specifiers;
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  // Vector(argument) specifiers; // A vector with a given initial dimension
  Vector(const unsigned long &);
  // Vector(argument) specifiers; // A vector obtained from a TraversableContainer
  Vector(const TraversableContainer<Data> &);
  // Vector(argument) specifiers; // A vector obtained from a MappableContainer
  Vector(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  // Vector(argument) specifiers;
  Vector(const Vector &);

  // Move constructor
  // Vector(argument) specifiers;
  Vector(Vector &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~Vector() specifiers;
  virtual ~Vector() { delete[] Elements; }

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  Vector &operator = (const Vector &);

  // Move assignment
  // type operator=(argument) specifiers;
  Vector &operator = (Vector &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator == (const Vector &) const noexcept;
  // type operator!=(argument) specifiers;
  inline bool operator != (const Vector & vector) const noexcept { return !( *(this) == vector ); }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  // type operator[](argument) specifiers; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)
  inline Data & operator[](const unsigned long) override;

  // type Front() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
  inline Data & Front() override;

  // type Back() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
  inline Data & Back() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // type operator[](argument) specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)
  inline const Data & operator[](const unsigned long) const override;

  // type Front() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
  inline const Data & Front() const override;

  // type Back() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
  inline const Data & Back() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  // type Resize(argument) specifiers; // Override ResizableContainer member
  void Resize(const unsigned long) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
  inline void Clear() override;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector: virtual public Vector<Data>, virtual public SortableLinearContainer<Data> {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  // using Container::???;
  using Container::size;

  // ...

public:

  // Default constructor
  // SortableVector() specifiers;
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  // SortableVector(argument) specifiers; // A vector with a given initial dimension
  SortableVector(const unsigned long & size) : Vector<Data>(size) {}
  // SortableVector(argument) specifiers; // A vector obtained from a TraversableContainer
  SortableVector(const TraversableContainer<Data> & traversableContainer) : Vector<Data>(traversableContainer) {}
  // SortableVector(argument) specifiers; // A vector obtained from a MappableContainer
  SortableVector(MappableContainer<Data> && mappableContainer) : Vector<Data>(std::move(mappableContainer)) {}

  /* ************************************************************************ */

  // Copy constructor
  // SortableVector(argument) specifiers;
  SortableVector(const SortableVector & copyVector) : Vector<Data>(copyVector) {}

  // Move constructor
  // SortableVector(argument) specifiers;
  SortableVector(SortableVector && moveVector) noexcept : Vector<Data>(std::move(moveVector)) {}

  /* ************************************************************************ */

  // Destructor
  // ~SortableVector() specifiers;
  virtual ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  SortableVector & operator = (const SortableVector &);

  // Move assignment
  // type operator=(argument) specifiers;
  SortableVector & operator = (SortableVector &&) noexcept;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
