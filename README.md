
# Data Structures and Algorithms

A project that implements various data structures in C++, with the aim of providing a simple and intuitive interface for each structure.
## About

This repository includes implementations of the following fundamental and common data structures:

- **Heap**: Implementation of a binary heap, useful for sorting algorithms and other operations on structured data.
- **Lists**: Singly linked list implementation.
- **Priority** Queues: Implementation of a priority queue, used in scheduling algorithms and event management.
- **Set**: A data structure that manages sets of unique data, without duplicates.
- **Vectors**: A simple implementation of dynamic arrays, with operations for access, insertion, and deletion.

Each data structure includes methods for common operations like insertion, removal, search, and other operations specific to the structure.
## Tech Stack

- C++
- Object-Oriented Programming (OOP)
- Generic Programming with Templates
- Standard Template Library (STL) utilities
- Dynamic Memory Management
- Abstract Data Types (ADT) implementation
## Architecture

The project follows a hierarchical architecture based on abstraction and inheritance.

The design is organized around common interfaces and reusable components, allowing different data structures to share behavior while providing their own specialized implementations.

Key architectural principles include:

- **Abstraction**: Common operations are defined through abstract interfaces.
- **Inheritance**: Specialized data structures extend base classes when appropriate.
- **Encapsulation**: Internal implementation details are hidden behind public methods.
- **Generic Programming**: Templates enable data structures to operate on different data types.
- **Modularity**: Each data structure is implemented independently, promoting maintainability and reuse.
## Repository Structure

- `heap/` → Binary heap implementation and related operations.
- `list/` → Double linked list implementation.
- `pq/` → Priority queue implementation based on heap structures.
- `set/` → Set implementation supporting unique elements.
- `vector/` → Dynamic array implementation with insertion, deletion, and access operations.
- `zlasdtest/` → Test cases used to validate the correctness of the data structures.
- `zmytest/` → Test cases used to validate the correctness of the data structures.
## License

This project is licensed under the [MIT](https://choosealicense.com/licenses/mit/) License.


## Authors

- GitHub: [@RiuHz](https://www.github.com/RiuHz)
