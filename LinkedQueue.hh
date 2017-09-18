/** LinkedQueue ADT header file.
@file LinkedQueue.hh
@author Eugene Nelson
@date 9/17/17
@version 1.0 (Eugene Nelson 9/17/17)

Header file for the LinkedQueue ADT. Describes the memeber functions of the
LinkedQueue ADT and their paramaters/functions.*/

#ifndef linked_queue_h
#define linked_queue_h

#include "Node.hh"

template <class ItemType>
class LinkedQueue
{
	public:
		LinkedQueue( )	{ apListPtr = NULL }
		LinkedQueue( const LinkedQueue<ItemType>& copyList );
		~LinkedQueue( );

        bool IsEmpty( ) const;
        int GetSize( ) const;
        bool Enqueue( const ItemType& newEntry );
        bool Dequeue( );
        ItemType PeekFront( ) const;

	private:
	    LinkedList<ItemType>* 	apListPtr;
};

/**<
Default constructor
*/
template <class ItemType>
LinkedQueue::LinkedQueue( )
{ 
    apListPtr = NULL;
} // end Default Constructor

/**<
Copy Constructor
*/
template <class ItemType>
LinkedQueue::LinkedQueue( const LinkedQueue<ItemType>& copyQueue )
{
    apListPtr = new LinkedList( *( copyQueue.apListPtr ) );
} // end Copy Constructor

/**<
Deconstructor
*/
template <class ItemType>
LinkedQueue::~LinkedQueue( )
{
    delete apListPtr;
} // end Deconstructor

/**< 
Checks to see if the queue is empty.

@return True if queue is empty. False otherwise.*/
template <class ItemType>
bool LinkedQueue::IsEmpty( ) const
{
    return apListPtr->IsEmpty();
} // end IsEmpty

/**<
Gets the number of entries currently in the queue.

@return The integer number of entries in the queue.
*/
template <class ItemType>
int LinkedQueue::GetSize( ) const
{
    return apListPtr->getLength( );
} // end GetSize


/**<
Enqueue a value to the back of the queue.

@pre None.
@post New entry will be inserted into the queue at the end of the queue.
@param newEntry The new entry to be inserted into the queue.
@return True if entry was successfully added. False otherwise.*/
template <class ItemType>
bool LinkedQueue::Enqueue( const ItemType& newEntry )
{
    return apListPtr->InsertEntry( apListPtr->GetSize( ), newEntry );
} // end Enqueue

/**<
Removes the entry at the given position from the queue.

@pre None.
@post Removes the element from the front of the queue.
@return True if the removal was successful. False otherwise.*/
template <class ItemType>
bool LinkedQueue::Dequeue( )
{
    return apListPtr->RemoveEntry( 0 );
} // end Dequeue

/**<
Gets value at the front of the queue.

@pre Queue is not empty.
@post The entry at the front will be returned.
@return The entry at the given position.*/
template <class ItemType>
ItemType LinkedQueue::PeekFront( ) const
{
    return apListPtr->GetEntry( 0 );
} // end PeekFront

#endif