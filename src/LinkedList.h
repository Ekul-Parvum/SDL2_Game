#ifndef EKUL_LINKED_LIST_H
#define EKUL_LINKED_LIST_H

namespace Ekul {

    template <typename T>
    class Node {
        public:
        T mItem;

        Node* mNext;
        Node* mPrevious;

        Node(T item);
    };

    template <typename T>
    class LinkedList {
        public:
        LinkedList();

        ~LinkedList();

        void insertAtHead(T item);

        void append(T item);

        void popTail();

        void popHead();

        void free();

        Node<T>* getHead();

        Node<T>* getTail();

        private:
        Node<T>* mHead;
        Node<T>* mTail;
    };
}

#include "LinkedList.tpp"

#endif