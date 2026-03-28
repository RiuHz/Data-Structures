
namespace lasd {

/* ************************************************************************** */

template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const {

    Traverse(
        [foldFunction, &accumulator] (const Data & value) {
            accumulator = foldFunction(value, accumulator);
        }
    );

    return accumulator;
}

template <typename Data>
inline bool TraversableContainer<Data>::Exists(const Data & data) const noexcept {
    bool dataExists = false;
    
    Traverse(
        [&dataExists, data] (const Data & value) {
            dataExists |= (data == value);
        }
    );

    return dataExists;
}

/* ************************************************************************** */

template <typename Data>
template <typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const {

    PreOrderTraverse(
        [foldFunction, &accumulator] (const Data & value) {
            accumulator = foldFunction(value, accumulator);
        }
    );

    return accumulator;
}

/* ************************************************************************** */

template <typename Data>
template <typename Accumulator>
inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const {

    PostOrderTraverse(
        [foldFunction, &accumulator] (const Data & value) {
            accumulator = foldFunction(value, accumulator);
        }
    );

    return accumulator;
}

}
