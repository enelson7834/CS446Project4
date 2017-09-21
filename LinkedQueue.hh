/**<
@file LinkedQueue.h

@brief Implaments the linked queue class and all member functions

@author Eugene Nelson

@version    1.0 Eugene Nelson
        Originally developed ( 11 - 14 - 16 )
*/
/////////////////////////////////////////////////////////////////////////////
// PRECOMPILER DIRECTIVES 
/////////////////////////////////////////////////////////////////////////////
#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

/////////////////////////////////////////////////////////////////////////////
// HEADER FILES
/////////////////////////////////////////////////////////////////////////////
#include "Node.hh"

/////////////////////////////////////////////////////////////////////////////
// CLASS DEFINITION 
/////////////////////////////////////////////////////////////////////////////
template <class ItemType>
class LinkedQueue
{
    public: 
        LinkedQueue();
        LinkedQueue( const LinkedQueue<ItemType>& source );
        ~LinkedQueue();
        
        bool IsEmpty() const;
        bool Enqueue( const ItemType& newEntry );
        bool Dequeue();
        ItemType* PeekFront();
        int GetSize();
    private:
        Node<ItemType>* front;
        Node<ItemType>* rear;
        
        int size;
};

/**<
Default constructor for linked queue
****************************************************************************/
template <class ItemType>
LinkedQueue<ItemType>::LinkedQueue()
{
    front = NULL;
    rear = NULL;
    
    size = 0;
}

/**<
Copy constructor for Linked queue class
****************************************************************************/
template <class ItemType>
LinkedQueue<ItemType>::LinkedQueue( const LinkedQueue<ItemType>& source )
{
    size = source.size;
    Node<ItemType>* temp = source.front;
    
    while( temp != NULL )
    {
        Enqueue( *( temp->getData() ) );
        temp = temp->getNext();
    }
    temp = NULL;
}

/**<
Deconstructor for linked queue class
****************************************************************************/
template <class ItemType>
LinkedQueue<ItemType>::~LinkedQueue()
{
    while( !IsEmpty() )
    {
        Dequeue();
    }
    size = 0;
}

/**<
Checks if linked queue is empty

@return succes status of function
****************************************************************************/
template <class ItemType>
bool LinkedQueue<ItemType>::IsEmpty() const
{
    if( front == NULL && rear == NULL )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**<
Adds new element into the queue

@return success status of function
****************************************************************************/
template <class ItemType>
bool LinkedQueue<ItemType>::Enqueue( const ItemType& newEntry )
{
    if( IsEmpty() )
    {
        Node<ItemType>* temp = new Node<ItemType>( newEntry, NULL );
        front = rear = temp;
        temp = NULL;
    }
    else
    {
        Node<ItemType>* temp = new Node<ItemType>( newEntry, NULL );
        rear->setNext( temp );
        rear = temp;
        temp = NULL;
    }
    
    size++;
    
    return true;
}

/**<
Removes an element from the front of the queue

@return success status of the function
****************************************************************************/
template <class ItemType>
bool LinkedQueue<ItemType>::Dequeue()
{
    if( IsEmpty() )
    {
        return false;
    }
    else if( rear == front )
    {
        delete front;
        front = rear = NULL;
        size = 0;
        
        return true;
    }
    else
    {
        Node<ItemType>* temp = front;
        front = front->getNext();
        delete temp;
        temp = NULL;
        
        size--;
        
        return true;
    }
}

/**<
Peeks at the front element of the queue

@return poiner to element at front of queue
****************************************************************************/
template <class ItemType>
ItemType* LinkedQueue<ItemType>::PeekFront()
{
    if( IsEmpty() )
    {
        return NULL;
    }
    
    return front->getData();
}

/**<
Returns the number of elements in the queue

@return the size of the queue
****************************************************************************/
template <class ItemType>
int LinkedQueue<ItemType>::GetSize()
{
    return size;
}

#endif
