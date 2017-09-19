/** Node ADT header file.
@file Node.hh
@author Eugene Nelson
@date 9/17/17
@version 1.0 (Eugene Nelson 9/17/17)

Header file for the Node ADT. Details the memebers and attributes of the Node ADT and their paramaters/functions.*/

#ifndef node_h
#define node_h

template <class ItemType>
class Node
{
	public:
		/** Constructors and deconstructors.*/
		Node(const ItemType& anItem)		
		{ aItem = anItem; apNext = NULL; }
		
		Node(const ItemType& anItem, Node* nextNodePointer) 
		{ aItem = anItem; apNext = nextNodePointer; }
		
		~Node()									
		{  }

		/** Sets the item of the Node.
		@pre None.
		@post The item of the Node will be set to the specified value.
		@param anItem The item that will be set in the Node.*/
		void SetEntry(const ItemType& anItem)			
		{ aItem = anItem; }

		/** Sets the next pointer of the Node.
		@pre None.
		@post The pointer to the next node is set to the specified value.
		@param nextNodePtr The pointer to the next node that will be used.*/
		void SetNext(Node<ItemType>* nextNodePtr) 	
		{ apNext = nextNodePtr; }

		/** Returns the item in the Node.
		@pre None.
		@post Item in Node will be returned.
		@return The item in the Node.*/
		ItemType GetEntry()			
		{ return aItem; }

		/** Returns the pointer to the next Node.
		@pre None.
		@post The pointer to the next Node is returned.
		@return The pointer to the next Node.*/
		Node<ItemType>* GetNext()	
		{ return apNext; }

	private:
		ItemType			aItem;
		Node<ItemType>*		apNext;

};

#endif