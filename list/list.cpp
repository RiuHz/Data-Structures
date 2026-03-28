
namespace lasd {

/* ************************************************************************** */

template <typename Data>
List<Data>::Node::Node(const Data & data) {
    element = data;
}

template <typename Data>
List<Data>::Node::Node(Data && data) noexcept {
    std::swap(element, data);
}

/* ********************************************************************** */

template <typename Data>
List<Data>::Node::Node(const List<Data>::Node & copyNode) {
    element = copyNode.element;
}

template <typename Data>
List<Data>::Node::Node(List<Data>::Node && moveNode) noexcept {
    std::swap(element, moveNode.element);
    std::swap(next, moveNode.next);
};

/* ********************************************************************** */

template <typename Data>
bool List<Data>::Node::operator == (const List<Data>::Node & node) const noexcept {
    return (element == node.element) && 
    ((next == nullptr && node.next == nullptr) ||
    ((next != nullptr && node.next != nullptr) && (*(next) == *(node.next))));
}

/* ************************************************************************** */

template <typename Data>
List<Data>::List(const TraversableContainer<Data> & container) {
    container.Traverse(
        [this] (const Data & data) {
            InsertAtBack(data);
        }
    );
}

template <typename Data>
List<Data>::List(MappableContainer<Data> && container) noexcept {
    container.Map(
        [this] (Data & data) {
            InsertAtBack(std::move(data));
        }
    );
}

/* ********************************************************************** */

template <typename Data>
List<Data>::List(const List<Data> & copyList) {
    copyList.PreOrderTraverse(
        [this] (const Data & data) {
            InsertAtBack(data);
        }
    );
}

template <typename Data>
List<Data>::List(List<Data> && moveList) noexcept {
    std::swap(size, moveList.size);
    std::swap(head, moveList.head);
    std::swap(tail, moveList.tail);
}

/* ********************************************************************** */

template <typename Data>
List<Data> & List<Data>::operator = (const List<Data> & copyList) {
    if (copyList.Empty())
        Clear();
    else if (size <= copyList.size) {
        Node * copyNode = copyList.head;

        for (Node * node = head; node != nullptr; node = node -> next, copyNode = copyNode -> next)
            node -> element = copyNode -> element;

        while (copyNode != nullptr) {
            InsertAtBack(copyNode -> element);
            copyNode = copyNode -> next;
        }
                
    } else {
        Node * node = head;

        for (Node * copyNode = copyList.head; copyNode != nullptr; node = node -> next, copyNode = copyNode -> next)
            node -> element = copyNode -> element;

        tail = head;

        while (tail -> next != node)
            tail = tail -> next;

        tail -> next = nullptr;
        delete node;
    }

    size = copyList.size;

    return *this;
}

template <typename Data>
List<Data> & List<Data>::operator = (List<Data> && moveList) noexcept {
    std::swap(size, moveList.size);
    std::swap(head, moveList.head);
    std::swap(tail, moveList.tail);

    return *this;
}

/* ********************************************************************** */

template <typename Data>
inline bool List<Data>::operator == (const List<Data> & list) const noexcept {
    return (size == list.size) && 
    ((head == nullptr && list.head == nullptr) ||
    ((head != nullptr && list.head != nullptr) && (*(head) == *(list.head))));
}

/* ********************************************************************** */

template <typename Data>
void List<Data>::InsertAtFront(const Data & data) {
    Node * newNode = new Node(data);

    newNode -> next = head;
    head = newNode;

    if (this -> Empty())
        tail = newNode;
    
    size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data && data) {
    Node * newNode = new Node(std::move(data));

    newNode -> next = head;
    head = newNode;

    if (this -> Empty())
        tail = newNode;
    
    size++;
}

template <typename Data>
void List<Data>::RemoveFromFront() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    Node *removeNode = head;

    if (size == 1)
        head = tail = nullptr;
    else
        head = head -> next;
    
    size--;

    removeNode -> next = nullptr;
    delete removeNode;
}

template <typename Data>
Data List<Data>::FrontNRemove() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    Data data = std::move(head -> element);

    RemoveFromFront();

    return data;
}

/* ********************************************************************** */

template <typename Data>
void List<Data>::InsertAtBack(const Data & data) {
    Node * newNode = new Node(data);

    if (this -> Empty())
        head = newNode;
    else
        tail -> next = newNode;
    
    tail = newNode;
    
    size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data && data) {
    Node * newNode = new Node(std::move(data));

    if (this -> Empty())
        head = newNode;
    else
        tail -> next = newNode;
    
    tail = newNode;
    
    size++;
}

template <typename Data>
void List<Data>::RemoveFromBack() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    Node *removeNode = tail;

    if (size == 1)
        head = tail = nullptr;
    else {
        tail = head;

        while (tail -> next != removeNode)
            tail = tail -> next;

        tail -> next = nullptr;
    }
    
    size--;

    delete removeNode;
}

template <typename Data>
Data List<Data>::BackNRemove() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    Data data = std::move(tail -> element);

    RemoveFromBack();

    return data;
}

/* ********************************************************************** */

template <typename Data>
Data & List<Data>::operator[](const unsigned long index) {
    if (index >= size)
        throw std::out_of_range("Indice non valido");

    Node *searchNode = head;

    for (unsigned long j = 0; j < index; j++)
        searchNode = searchNode -> next;

    return searchNode -> element;
}

template <typename Data>
inline Data & List<Data>::Front() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    return head -> element;
}

template <typename Data>
inline Data & List<Data>::Back() {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    return tail -> element;
}

/* ********************************************************************** */

    template <typename Data>
const Data & List<Data>::operator[](const unsigned long index) const {
    if (index >= size)
        throw std::out_of_range("Indice non valido");

    Node *searchNode = head;

    for (unsigned long j = 0; j < index; j++)
        searchNode = searchNode -> next;

    return searchNode -> element;
}

template <typename Data>
inline const Data & List<Data>::Front() const {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    return head -> element;
}

template <typename Data>
inline const Data & List<Data>::Back() const {
    if (this -> Empty())
        throw std::length_error("Struttura vuota");

    return tail -> element;
}

/* ********************************************************************** */

template <typename Data>
inline void List<Data>::PreOrderMap(MapFun mapFunction) {
    Node *node = head;

    while (node != nullptr) {
        mapFunction(node -> element);
        node = node -> next;
    }
}

template <typename Data>
void List<Data>::PostOrderMap(MapFun mapFunction, List<Data>::Node * node) {
    if (node == nullptr)
        return;

    PostOrderMap(mapFunction, node -> next);
    mapFunction(node -> element);
}

/* ********************************************************************** */

template <typename Data>
inline void List<Data>::PreOrderTraverse(TraverseFun traverseFunction) const {
    Node *node = head;

    while (node != nullptr) {
        traverseFunction(node -> element);
        node = node -> next;
    }
}

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun traverseFunction, const List<Data>::Node * node) const {
    if (node == nullptr)
        return;

    PostOrderTraverse(traverseFunction, node -> next);
    traverseFunction(node -> element);
}

/* ********************************************************************** */

template <typename Data>
inline void List<Data>::Clear() {
    delete head;
    head = tail = nullptr;
    size = 0;
}

/* ********************************************************************** */

}
