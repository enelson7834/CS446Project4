/**
@file Node.hh
@author Eugene Nelson
@breif The header/implamentation for the templated Node class
@version    1.0 Eugene Nelon
            Originally developed ( 10 - 15 - 16 ) 
*/
/////////////////////////////////////////////////////////////////////////////
// Precompiler Directives 
/////////////////////////////////////////////////////////////////////////////
#ifndef node_hh
#define node_hh

/////////////////////////////////////////////////////////////////////////////
// Class Definition 
/////////////////////////////////////////////////////////////////////////////
template <class ItemType>
class Node
{    
    public:
        Node( const ItemType& SourceData, Node* NextNode );
        ~Node();

        ItemType* getData();
        Node<ItemType>* getNext();
        void setData( const ItemType& SourceData );
        void setNext( Node<ItemType>* NextNode );
        
    private:
        ItemType Data;
        Node* Next;
}; //end Node

/**<
Default paramaterized constructor for Node class
****************************************************************************/
template <class ItemType>
Node<ItemType>::Node( const ItemType& SourceData, Node* NextNode )
{
    Data = SourceData;
    Next = NextNode;
} // end constructor

/**<
Deconstructor for Node class
****************************************************************************/
template <class ItemType>
Node<ItemType>::~Node()
{   
    ;
} // end deconstructor

/**<
Gets the data stored in the node
@return Returns a pointer to the data stored in Node
****************************************************************************/
template <class ItemType>
ItemType* Node<ItemType>::getData()
{
    return &Data;
} // end getData

/**<
Gets the value of the next pointer in Node
@return Pointer to next Node
****************************************************************************/
template <class ItemType>
Node<ItemType>* Node<ItemType>::getNext()
{
    return Next;
} // end getNext

/**<
Sets the data for the Node object
@return void
@param SourceData The data that will be used to set the data stored in Node
****************************************************************************/
template <class ItemType>
void Node<ItemType>::setData( const ItemType& SourceData )
{
    Data = SourceData;    
} // end SetData

/**<
Sets the next Node
@return void
@param NextNode The node that will be set as the next Node
****************************************************************************/
template <class ItemType>
void Node<ItemType>::setNext( Node<ItemType>* NextNode )
{
    Next = NextNode;
} // end setNext
        
#endif
