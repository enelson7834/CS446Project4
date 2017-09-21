/**
@file LinkedList.h
@author Eugene Nelson
@breif The header/implamentation file for the Linked LinkedList class
@version    1.1 Eugene Nelon ( 9 - 20 - 17 )

            1.0 Eugene Nelson
            Originally developed ( 10 - 15 - 16 )
*/
/////////////////////////////////////////////////////////////////////////////
// Precompiler Directives 
/////////////////////////////////////////////////////////////////////////////
#ifndef linked_list_hh
#define linked_list_hh

/////////////////////////////////////////////////////////////////////////////
// Header files 
/////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Node.hh"

/////////////////////////////////////////////////////////////////////////////
// Class Definition
/////////////////////////////////////////////////////////////////////////////
template <class ItemType>
class LinkedList
{     
    public:
        LinkedList();
        LinkedList( LinkedList<ItemType>& Source );
        ~LinkedList();
        
        bool IsEmpty();
        bool IsFull();
        int GetLength();
        
        bool RemoveEntry( int Position );
        void Clear();
        bool InsertEntry( int Position, const ItemType& Data );
        bool push( const ItemType& Data );
        bool pop();
        ItemType* GetEntry( int Position );
        
        void print();

        
    private:
        Node<ItemType>* Head;
        int Size;
}; //end LinkedList

/**<
Default constructor for LinkedList
****************************************************************************/
template <class ItemType>
LinkedList<ItemType>::LinkedList()
{
    Head = NULL;
    Size = 0;
} // end constructor

/**<
Copy constructor for list
****************************************************************************/
template <class ItemType>
LinkedList<ItemType>::LinkedList( LinkedList& Source )
{
    if( Source.IsEmpty() )
    {
        Head = NULL;
        Size = 0;
    }
    else
    {
        for( int i = 1; i <= Source.Size; i++ )
        {
            InsertEntry( i, *(Source.GetEntry( i )) );
        }
    }
} // end copy constructor

/**<
Deconstructor for LinkedList
****************************************************************************/
template <class ItemType>
LinkedList<ItemType>::~LinkedList()
{
    Clear();
} // end deconstructor

/**<
Checks if the list is empty
@return Success value of function
****************************************************************************/
template <class ItemType>
bool LinkedList<ItemType>::IsEmpty()
{
    if( Head == NULL && Size == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
} // end IsEmpty

/**<
Checks if the list is full
@return Always returns false as linked lists do not have max size
****************************************************************************/
template <class ItemType>
bool LinkedList<ItemType>::IsFull()
{
    return false;
} // end IsFull

/**<
Returns the size of the LinkedList
@returns Number of elements in the list
****************************************************************************/
template <class ItemType>
int LinkedList<ItemType>::GetLength()
{
    return Size;
} // end GetLength

/**<
Removes an element at specified position
@return Returns the Success value for the function
@param  Position The position at which it is desired that an element be
        removed.
@post Element will be deleted from specified position
****************************************************************************/
template <class ItemType>
bool LinkedList<ItemType>::RemoveEntry( int Position )
{
    if( Position > ( Size )  )    
    {
        return false;
    }
    if( Position < 1 )
    {
        return false;
    }
    if( IsEmpty() )
    {
        return false;
    }

    Node<ItemType>* temp = Head->getNext();
    Node<ItemType>* temp2 = Head;
    
    for( int i = 1; i < Position; i++ )
    {
        temp = temp->getNext();
        temp2 = temp2->getNext();
    }
    
    if( Position == 1 )
    {
        Head = Head->getNext();
        delete temp2;
    }
    else if( temp == NULL )
    {
        temp2->setNext( temp );
        delete temp;
    }
    else
    {
        temp2->setNext( temp->getNext() );
        delete temp;
    }
    
    Size--;
    if( Size == 0 )
    {
       Head = NULL;
    }
    
    return true;
} // end RemoveEntry

/**<
Clears the list
@return void
@pre RemoveEntry and IsEmpty functions are working properly
****************************************************************************/
template <class ItemType>
void LinkedList<ItemType>::Clear()
{
    while( !IsEmpty() )
    {
        RemoveEntry(1);
    }
} // end Clear

/**<
Inserts a new element at specified position
@return The success value of the function
@param Position The position where the element will be InsertEntryed
@param Data The data that will be InsertEntryed
****************************************************************************/
template <class ItemType>
bool LinkedList<ItemType>::InsertEntry( int Position, const ItemType& Data )
{
    if( Position > ( Size + 1 ) || Position < 1 )    
    {
        return false;
    }
    
    if( IsEmpty() )
    {
        Head = new Node<ItemType>( Data, NULL );
    }
    else if( Position == 1 )
    {
        Node<ItemType>* temp = new Node<ItemType>( Data, Head );
        Head = temp;
        temp = NULL;
    }
    else
    {
        Node<ItemType>* temp = Head;
        for( int i = 1; i < Position - 1; i++ )
        {
            temp = temp->getNext();
        }
        
        Node<ItemType>* temp2 = new Node<ItemType>( Data, temp->getNext() );
        temp->setNext( temp2 );
        
        temp2 = NULL;
        temp = NULL;
    }
   
    
    Size++;
    return true;
} // end InsertEntry

/**<
Pushes value onto the end of the list
@return The success value of the function
@param Data The data that will be pushed
****************************************************************************/
template <class ItemType>
bool LinkedList<ItemType>::push( const ItemType& Data )
{
    InsertEntry( Size + 1, Data );
    
    return true;
} // end push

/**<
Peeks at the data at a specified position
@return Returns a pointer to the data at specified position
@param Position The position of where to GetEntry
****************************************************************************/
template <class ItemType>
ItemType* LinkedList<ItemType>::GetEntry( int Position )
{
    if( Position > ( Size ) || Position < 1 )    
    {
        return NULL;
    }
    if( IsEmpty() )
    {
        return NULL;
    }
    
    Node<ItemType>* temp = Head;
    for( int i = 1; i < Position; i++ )
    {
        temp = temp->getNext();
    }
    
    return temp->getData();
} // end GetEntry

/**<
Pops data off of last element of list
@return Success value of function
****************************************************************************/
template <class ItemType>
bool LinkedList<ItemType>::pop()
{
    if( IsEmpty() )
    {
        return false;
    }
    else
    {
        RemoveEntry( Size );
        return true;
    }
} // end pop

/**<
Prints all value in the linked list
@return void
****************************************************************************/
template <class ItemType>
void LinkedList<ItemType>::print()
{
    if( IsEmpty() )
    {
        ;
    }
    else
    {
        for( int i = 1; i < Size; i++ )
        {
            std::cout << *( GetEntry( i ) ) << " -> ";
        }
        std::cout << *( GetEntry( Size ) );
    }
} // end print


#endif
