
namespace lasd {

/* ************************************************************************** */

template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data> & container) {
    container.Traverse(
        [this] (const Data & element) {
            Insert(element);
        }
    );
}

template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data> && container) noexcept {
    container.Map(
        [this] (Data & element) {
            Insert(std::move(element));
        }
    );
}

/* ************************************************************************** */

template <typename Data>
SetLst<Data> & SetLst<Data>::operator = (const SetLst & copySet) {
    List<Data>::operator = (copySet);

    return *this;
}

template <typename Data>
SetLst<Data> & SetLst<Data>::operator = (SetLst && moveSet) noexcept {
    List<Data>::operator = (std::move(moveSet));

    return *this;
}

/* ************************************************************************** */

template <typename Data>
const Data & SetLst<Data>::Predecessor(const Data & element) const {
    if (this -> Empty())
        throw std::length_error("Predecessore non trovato");

    Node * const * predecessor = SearchPredecessor(element);

    return (*predecessor) -> element;
}

template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data & element) {
    if (this -> Empty())
        throw std::length_error("Predecessore non trovato");

    Node ** predecessor = SearchPredecessor(element);
    
    Data data = (*predecessor) -> element;
    Remove(predecessor);
    
    return data;
}

template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data & element) {
    if (this -> Empty())
        throw std::length_error("Predecessore non trovato");

    Node ** predecessor = SearchPredecessor(element);
    
    Remove(predecessor);
}

template <typename Data>
const Data & SetLst<Data>::Successor(const Data & element) const {
    if (this -> Empty())
        throw std::length_error("Successore non trovato");

    Node * const * node = SearchNode(element);

    if (isNodeNull(node) || isntValidSuccessor(node, element))
        throw std::length_error("Successore non trovato");
    else if (elementFound(node, element))
        return (*node) -> next -> element;
    else
        return (*node) -> element;
}

template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data & element) {
    if (this -> Empty())
        throw std::length_error("Successore non trovato");

    Node ** node = SearchNode(element);

    if (isNodeNull(node) || isntValidSuccessor(node, element))
        throw std::length_error("Successore non trovato");
    
    Data data;

    if (elementFound(node, element)) {
        data = (*node) -> next -> element;
        Remove( &( (*node) -> next ) );
    }
    else {
        data = (*node) -> element;
        Remove(node);
    }

    return data;
}

template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data & element) {
    if (this -> Empty())
        throw std::length_error("Successore non trovato");

    Node ** node = SearchNode(element);

    if (isNodeNull(node) || isntValidSuccessor(node, element))
        throw std::length_error("Successore non trovato");
    else if (elementFound(node, element)) 
        Remove( &( (*node) -> next ) );
    else
        Remove(node);
}

/* ************************************************************************** */

template <typename Data>
bool SetLst<Data>::Insert(const Data & element) {
    Node ** node = SearchNode(element);

    if (isNodeNull(node))
        List<Data>::InsertAtBack(element);
    else if (elementFound(node, element))
        return false;
    else if (isSmallestInSet(node))
        List<Data>::InsertAtFront(element);
    else {
        Node * newNode = new Node(element);
        newNode -> next = *node;
        *node = newNode;
        size++;
    }

    return true;
}

template <typename Data>
bool SetLst<Data>::Insert(Data && element) {
    Node ** node = SearchNode(element);

    if (isNodeNull(node))
        List<Data>::InsertAtBack(std::move(element));
    else if (elementFound(node, element))
        return false;
    else if (isSmallestInSet(node))
        List<Data>::InsertAtFront(std::move(element));
    else {
        Node * newNode = new Node(std::move(element));
        newNode -> next = (*node);
        (*node) = newNode;
        size++;
    }

    return true;
}

template <typename Data>
bool SetLst<Data>::Remove(const Data & element) noexcept {
    if (this -> Empty())
        return false;
    
    Node ** node = SearchNode(element);

    if (isNodeNull(node) || !elementFound(node, element))
        return false;

    Remove(node);

    return true;
}

/* ************************************************************************** */

template <typename Data>
bool SetLst<Data>::Exists(const Data & element) const noexcept {
    if (this -> Empty())
        return false;

   Node * const * node = SearchNode(element);

    if (isNodeNull(node) || !elementFound(node, element))
        return false;

    return true;
}

/* ************************************************************************** */

template <typename Data>
List<Data>::Node * const * SetLst<Data>::Reach(Node * const * start, const unsigned long steps) const noexcept {
    if (isNodeNull(start))
        return start;

    for (unsigned long i = 0; i < steps; i++)
        start = &( (*start) -> next );

    return start;
}

template <typename Data>
List<Data>::Node * const * SetLst<Data>::SearchNode(const Data & element) const noexcept {
    unsigned long listSize = size;
    Node * const * start = &head;

    while (listSize > 0) {
        Node * const * mid = Reach(start, listSize / 2);
        listSize /= 2;

        if ( (*mid) != nullptr ) {
            if ( (*mid) -> element < element ) {
                start = &( (*mid) -> next );
                if ( (*start) != nullptr && (*start) -> element >= element )
                    return start;
            } else if ( (*mid) -> element == element )
                return mid;
        } else
            return mid;
    }

    return start;
}

template <typename Data>
List<Data>::Node * const * SetLst<Data>::SearchPredecessor(const Data & element) const {
    Node * const * node = SearchNode(element);

    if (isSmallestInSet(node))
        throw std::length_error("Predecessore non trovato");

    Node * const * predecessor = &head;

    while ( &( (*predecessor) -> next ) != node )
        predecessor = &( (*predecessor) -> next );

    return predecessor;
}

template <typename Data>
inline void SetLst<Data>::Remove(Node ** node) noexcept {
    if (isSmallestInSet(node))
        List<Data>::RemoveFromFront();
    else if (isGreatestInSet(node))
        List<Data>::RemoveFromBack();
    else {
        Node * tempNode = (*node);
        (*node) = tempNode -> next;

        tempNode -> next = nullptr;
        delete tempNode;

        size--;
    }
}

/* ************************************************************************** */

}
