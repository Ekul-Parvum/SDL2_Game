#include "LinkedList.h"

using namespace Ekul;

#pragma region Node
template <typename T>
Node<T>::Node(T item) {
    mItem = item;
    mNext = nullptr;
    mPrevious = nullptr;
}
#pragma endregion

#pragma region LinkedList

template <typename T>
LinkedList<T>::LinkedList()
{
    mHead = nullptr;
    mTail = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    free();
}

template <typename T>
void LinkedList<T>::insertAtHead(T item)
{
    // Make new node
    Node<T>* newNode = new Node<T>(item);

    // New node should point to current head as next
    newNode->mNext = mHead;

    if (mHead != nullptr)
    {
        // Head's previous should point to the new node
        mHead->mPrevious = newNode;
    }
    else
    {
        // if mHead is nullptr, then newNode will be the only node in the list
        // So it should be both head & tail
        mTail = newNode;
    }

    // mHead should now be the new Node
    mHead = newNode;
}

template <typename T>
void LinkedList<T>::append(T item)
{
    // Make new node
    Node<T>* newNode = new Node<T>(item);

    // New node should point to current tail as previous
    newNode->mPrevious = mTail;

    if (mTail != nullptr)
    {
        // Tail's next should point to the new node
        mTail->mNext = newNode;
    }
    else
    {
        // if mTail is nullptr, then newNode will be the only node in the list
        // So it should be both head & tail
        mHead = newNode;
    }

    // mTail should now be the new Node
    mTail = newNode;
}

template <typename T>
void LinkedList<T>::popTail()
{
    if (mTail != nullptr)
    {
        Node<T>* toDelete = mTail;
        mTail = mTail->mPrevious;

        if (mTail != nullptr)
        {
            mTail->mNext = nullptr;
        }
        else
        {
            mHead = nullptr;
        }

        delete toDelete;
    }
}

template <typename T>
void LinkedList<T>::popHead()
{
    if (mHead != nullptr)
    {
        Node<T>* toDelete = mHead;
        mHead = mHead->mNext;

        if (mHead != nullptr)
        {
            mHead->mPrevious = nullptr;
        }
        else
        {
            mTail = nullptr;
        }

        delete toDelete;
    }
}

template <typename T>
void LinkedList<T>::free()
{
    Node<T>* currentNode = mHead;
    while (currentNode != nullptr)
    {
        Node<T>* nextNode = currentNode->mNext;
        delete currentNode;
        currentNode = nextNode;
    } 
    mHead = nullptr;
    mTail = nullptr;
}

template <typename T>
Node<T>* LinkedList<T>::getHead()
{
    return mHead;
}

template <typename T>
Node<T>* LinkedList<T>::getTail()
{
    return mTail;
}

#pragma endregion

