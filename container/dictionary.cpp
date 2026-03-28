
namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> & container) {
    bool areAllInserted = true;

    container.Traverse(
        [this, &areAllInserted] (const Data & data) {
            areAllInserted &= Insert(data);
        }
    );

    return areAllInserted;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> && container) {
    bool areAllInserted = true;

    container.Map(
        [this, &areAllInserted] (Data & data) {
            areAllInserted &= Insert(std::move(data));
        }
    );

    return areAllInserted;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> & container) {
    bool areAllRemoved = true;

    container.Traverse(
        [this, &areAllRemoved] (const Data & data) {
            areAllRemoved &= Remove(data);
        }
    );

    return areAllRemoved;
}

/* ************************************************************************** */

template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> & container) {
    bool areSomeInserted = false;

    container.Traverse(
        [this, &areSomeInserted] (const Data & data) {
            areSomeInserted |= Insert(data);
        }
    );

    return areSomeInserted;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> && container) {
    bool areSomeInserted = false;

    container.Map(
        [this, &areSomeInserted] (Data & data) {
            areSomeInserted |= Insert(std::move(data));
        }
    );

    return areSomeInserted;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> & container) {
    bool areSomeRemoved = false;

    container.Traverse(
        [this, &areSomeRemoved] (const Data & data) {
            areSomeRemoved |= Remove(data);
        }
    );

    return areSomeRemoved;
}

/* ************************************************************************** */

template<typename Data>
inline Data OrderedDictionaryContainer<Data>::MinNRemove() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    Data min = Min();
    this -> Remove(min);

    return min;
};

template<typename Data>
inline void OrderedDictionaryContainer<Data>::RemoveMin() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    this -> Remove(Min());
};

template<typename Data>
inline Data OrderedDictionaryContainer<Data>::MaxNRemove() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    Data max = Max();
    this -> Remove(max);

    return max;
}

template<typename Data>
inline void OrderedDictionaryContainer<Data>::RemoveMax() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    this -> Remove(Max());
}

template<typename Data>
inline Data OrderedDictionaryContainer<Data>::PredecessorNRemove(const Data & data) {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    Data predecessor = Predecessor(data);
    this -> Remove(predecessor);

    return predecessor;
}

template<typename Data>
inline void OrderedDictionaryContainer<Data>::RemovePredecessor(const Data & data) {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    this -> Remove(Predecessor(data));
}

template<typename Data>
inline Data OrderedDictionaryContainer<Data>::SuccessorNRemove(const Data & data) {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    Data successor = Successor(data);
    this -> Remove(successor);

    return successor;
}

template<typename Data>
inline void OrderedDictionaryContainer<Data>::RemoveSuccessor(const Data & data) {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    this -> Remove(Successor(data));
}

/* ************************************************************************** */

}
