
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List: virtual public MutableLinearContainer<Data>, virtual public ClearableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ClearableContainer

private:

  // ...

protected:

  // using Container::???;
  using Container::size;

  struct Node {

    // Data
    // ...
    Data element = Data();
    Node *next = nullptr;

    /* ********************************************************************** */

    // Specific constructors
    // ...
    Node() = default;
    Node(const Data &);
    Node(Data &&) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    // ...
    Node(const Node &);
  
    // Move constructor
    // ...
    Node(Node &&) noexcept;

    /* ********************************************************************** */

    // Destructor
    // ...
    virtual ~Node() { delete next; }

    /* ********************************************************************** */

    // Comparison operators
    // ...
    bool operator == (const Node &) const noexcept;
    inline bool operator != (const Node & node) const noexcept { return !( *(this) == node ); } 

    /* ********************************************************************** */

    // Specific member functions
    // ...

  };

  // ...

  Node *head = nullptr;
  Node *tail = nullptr;

public:

  // Default constructor
  // List() specifiers;
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  // List(argument) specifiers; // A list obtained from a TraversableContainer
  List(const TraversableContainer<Data> &);
  // List(argument) specifiers; // A list obtained from a MappableContainer
  List(MappableContainer<Data> &&) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  // List(argument) specifiers;
  List(const List &);

  // Move constructor
  // List(argument) specifiers;
  List(List &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~List() specifiers;
  virtual ~List() { delete head; }

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  List &operator = (const List &);

  // Move assignment
  // type operator=(argument) specifiers;
  List &operator = (List &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  inline bool operator == (const List &) const noexcept;
  // type operator!=(argument) specifiers;
  inline bool operator != (const List & list) const noexcept { return !( *(this) == list ); }

  /* ************************************************************************ */

  // Specific member functions

  // type InsertAtFront(argument) specifier; // Copy of the value
  void InsertAtFront(const Data &);
  // type InsertAtFront(argument) specifier; // Move of the value
  void InsertAtFront(Data &&);
  // type RemoveFromFront() specifier; // (must throw std::length_error when empty)
  void RemoveFromFront();
  // type FrontNRemove() specifier; // (must throw std::length_error when empty)
  Data FrontNRemove();

  // type InsertAtBack(argument) specifier; // Copy of the value
  void InsertAtBack(const Data &);
  // type InsertAtBack(argument) specifier; // Move of the value
  void InsertAtBack(Data &&);
  // type RemoveFromBack() specifier; // (must throw std::length_error when empty)
  void RemoveFromBack();
  // type BackNRemove() specifier; // (must throw std::length_error when empty)
  Data BackNRemove();

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  // type operator[](argument) specifiers; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)
  Data & operator[](const unsigned long) override;

  // type Front() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
  inline Data & Front() override;

  // type Back() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
  inline Data & Back() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // type operator[](argument) specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)
  const Data & operator[](const unsigned long) const override;

  // type Front() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
  inline const Data & Front() const override;

  // type Back() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
  inline const Data & Back() const override;

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
  inline void PostOrderMap(MapFun mapFunction) override { PostOrderMap(mapFunction, head); }

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // using typename TraversableContainer<Data>::TraverseFun;
  using typename TraversableContainer<Data>::TraverseFun;

  // type Traverse(arguments) specifiers; // Override TraversableContainer member
  inline void Traverse(TraverseFun traverseFunction) const override { PreOrderTraverse(traverseFunction); }

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  // type PreOrderTraverse(arguments) specifiers; // Override PreOrderTraversableContainer member
  inline void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  // type PostOrderTraverse(arguments) specifiers; // Override PostOrderTraversableContainer member
  inline void PostOrderTraverse(TraverseFun traverseFunction) const override { PostOrderTraverse(traverseFunction, head); }

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
  inline void Clear() override;

protected:

  // Auxiliary functions, if necessary!

  void PostOrderMap(MapFun, Node * );

  void PostOrderTraverse(TraverseFun, const Node * ) const;

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
