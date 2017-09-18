/** LinkedList ADT header file.
@file LinkedList.hh
@author Eugene Nelson
@date 9/17/17
@version 1.0 (Eugene Nelson 9/17/17)

Header file for the LinkedList ADT. Describes the memeber functions of the
LinkedList ADT and their paramaters/functions.*/

#ifndef linked_list_h
#define linked_list_h

#include "Node.hh"

template <class ItemType>
class LinkedList
{
    public:
      	/** Default constructor, copy constructor, and deconstructor.*/
       	LinkedList();
       	LinkedList(const LinkedList<ItemType>& copyList);
       	~LinkedList();

        bool IsEmpty() const;
        int GetLenth() const;

        bool InsertEntry(int newPosition, const ItemType& newEntry);
        bool RemoveEntry(int position);
        void Clear();
        ItemType GetEntry(int position);
        bool SetEntry(int position, const ItemType& newEntry);

	private:
	    Node<ItemType>* 	apHead;
	    int 				aItemCount;
};
/**<
Default Constructor
*/
template <class ItemType>
LinkedList<ItemType>::LinkedList()
{
	apHead = NULL;
	aItemCount = 0;
} // end Default Constructor

/**<
Copy Constructor
*/
template <class ItemType>
LinkedList<ItemType>::LinkedList( const LinkedList<ItemType>& copyList )
{
    if( copyList.IsEmpty( ) )
    {
        this->apHead = NULL;
        this->aItemCount = 0;
    }
    else
    {
        for( int position = 0; position < copyList->aItemCount; 
                                                        ++position )
        {
            this->InsertEntry( position, copyList->
                                                GetItem( position ) );
        }
    }
} // end Copy Constructor

/**<
Deconstructor
*/
template <class ItemType>
LinkedList<ItemType>::~LinkedList(  )     
{ 
    this->Clear(  ); 
} // end Deconstructor

/**<
Checks to see if the list is empty.

@return True if list is empty. False otherwise.
*/		
template <class ItemType>
LinkedList<ItemType>::IsEmpty()
{
	if( aItemCount <= 0 )
	{
		return true;
	} 

	return false;
} // end IsEmpty

/**<
Gets the number of entries currently in the list.

@return The integer number of entries in the list.
*/
template <class ItemType>
LinkedList<ItemType>::GetLenth()
{
	return aItemCount;
} // end GetLength

/**<
Insert entry into list at the a given position.

@pre None.
@post New entry will be inserted into the list at the given position, moving
the current entry at that position and all following entries forward in the
list.
@param newPosition The position where the new entry will be inserted.
@param newEntry The new entry to be inserted into the list.
@return True if entry was successfully added. False otherwise.
@note Position starts at 0 and goes to ItemCount -1.
*/
template <class ItemType>
bool LinkedList<ItemType>::InsertEntry( int newPosition, 
                                        const ItemType& newEntry )
{
    if( newPosition > aItemCount || newPosition < 0 ) 
    {
        return false;
    }

    if( this->IsEmpty(  ) )
    {
        apHead = new Node<ItemType>( newEntry, NULL );
    }
    else if( newPosition == 0 )
    {
        Node<ItemType>* temp = new Node<ItemType>( newEntry, apHead );
        apHead = temp;
        temp = NULL;
    }
    else
    {
        Node<ItemType>* cursor = apHead;
        for( int i = 0; i < newPosition - 1; ++i )
        {
            cursor = cursor->GetNext(  );
        }
        
        Node<ItemType>* temp = new Node<ItemType>( newEntry, 
                                                        cursor->GetNext( ) );
        cursor->SetNext( temp );

        temp = NULL;
        cursor = NULL;
    }

    ++aItemCount;
    return true;
} // end InsertEntry

/**<
Removes the entry at the given position from the list.

@pre None.
@post Removes node at given position and relinks the list. If the entry to be
removed was the first entry, then the head pointer is adjusted.
@param position The position in the list where the removal will occur.
@return True if the removal was successful. False otherwise.
*/
template <class ItemType>
bool LinkedList<ItemType>::RemoveEntry( int position )
{
    if( this->IsEmpty(  ) ) 
    {
        return false;
    }
    if( position >= aItemCount || position < 0 )
    {
        return false;
    }

    Node<ItemType>* cursor = apHead;
    if( position == 0 )
    {
        apHead = apHead->GetNext(  );
    } 
    else
    {
        for( int i = 0; i < position - 1; ++i )
        {
            cursor = cursor->GetNext(  );
        }

        Node<ItemType>* temp = cursor;
        cursor = cursor->GetNext( );

        temp->SetNext( cursor->GetNext( ) );
        temp = NULL;
    }

    delete cursor;
    cursor = NULL;
    --aItemCount;
    return true;
} // end RemoveEntry

/**<
Removes all of the entries in the list.

@post The list will be emptied and private values are adjusted as necessary.
*/
template <class ItemType>
void LinkedList<ItemType>::Clear(  )
{
    while( !this->IsEmpty(  ) )
    {
        this->RemoveEntry( 0 );
    }
} // end Clear

/**<
Gets value of entry at a given position in the list.

@pre 0 < position <= getLength()
@post The entry at postition will be returned.
@param position The position of the entry to be returned.
@return The entry at the given position.
*/
template <class ItemType>
ItemType LinkedList<ItemType>::GetEntry( int position )
{
    if( this->IsEmpty(  ) ) return ItemType(  );
    if( position >= aItemCount || position < 0 ) return ItemType(  );
    
    Node<ItemType>* cursor = apHead;
    for( int i = 0; i < position; ++i )
    {
        cursor = cursor->GetNext(  );
    }

    return cursor->GetItem( );
}

/**<
Replaces an entry at given position.

@pre 0 < position <= getLength():
@post The entry at the given position will be replaced.
@param position The position of the element to be replaced.
@param newEntry The replacement entry.
@return True if the entry has been replaced. False otherwise.
*/
template <class ItemType>
bool LinkedList<ItemType>::SetEntry( int position, const ItemType& newEntry )
{
    if( this->IsEmpty(  ) ) return false;
    if( position >= aItemCount || position < 0 ) return false;
    
    Node<ItemType>* cursor = apHead;
    for( int i = 0; i < position; ++i )
    {
        cursor = cursor->GetNext(  );
    }

    cursor->SetItem( newEntry );

    return true;
}

#endif
