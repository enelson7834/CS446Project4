#include "listnode.h"

Node::Node( int value, Node* nxt )
{
    this->data = value;
    this->next = nxt;
}

ListNode::ListNode( int a )
{
    this->head = this->cursor = NULL;
}

ListNode::ListNode( const ListNode& copy )
{
	if( copy.isEmpty( ) )
	{
		this->cursor = this->head = NULL;
	}
	else
	{
		Node* tempCopy = copy.head;
		Node* tempThis = new Node( tempCopy->data, NULL );
		this->head = tempThis;

		if( copy.cursor == tempCopy )
		{
			this->cursor = tempThis;
		}

		Node* temp = tempThis;

		tempCopy = tempCopy->next;
		tempThis = tempThis->next;


		while( tempCopy != NULL )
		{
			tempThis = new Node( tempCopy->data, NULL );
			temp->next = tempThis;

			temp = temp->next;

			if( copy.cursor == tempCopy )
			{
				this->cursor = tempThis;
			}

			tempCopy = tempCopy->next;
			tempThis = tempThis->next;
		}
	}
}

ListNode::~ListNode( )
{
	this->clear( );
}

bool ListNode::insertAfter( int a )
{
	Node* temp = new Node( a, NULL );

	if( this->isEmpty( ) )
	{
		this->head = this->cursor = temp;

		temp = NULL;
		return true;
	}
	else
	{
		temp->next = this->cursor->next;

		this->cursor->next = temp;
		this->cursor = temp;

		temp = NULL;
		return true;
	}
}

bool ListNode::insertBefore( int a )
{
	if( this->isEmpty( ) )
	{
		this->head = new Node( a, NULL );
		this->cursor = this->head;
		return true;
	}
	else
	{
		Node* temp = new Node( this->cursor->data, this->cursor->next );

		this->cursor->next = temp;

		this->cursor->data = a;
		if( this->head == temp )
		{
			this->head = this->cursor;
		}

		temp = NULL;
		return true;
	}

}

bool ListNode::get( int& a ) const
{
	if( this->isEmpty( ) )
	{
		return false;
	}
	else
	{
		a = this->cursor->data;
		return true;
	}
}

bool ListNode::remove( int& a )
{
	if( this->isEmpty( ) )
	{
		return false;
	}
	else
	{
		a = this->cursor->data;

		Node* temp1 = this->cursor->next;
		Node* temp2 = this->cursor;

		if( this->cursor == this->head )
		{
			this->head = temp1;
		}
		else
		{
			this->goToPrior( );
			this->cursor->next = temp1;
		}

		if( temp1 == NULL )
		{
			this->cursor = this->head;
		}
		else
		{
			this->cursor = this->cursor->next;
		}

		delete temp2;
		temp2 = temp1 = NULL;

		return true;
	}
}

void ListNode::clear( )
{
	if( this->isEmpty( ) )
	{
		return;
	}

	Node* temp1 = this->head;
	Node* temp2 = this->head->next;

	while( temp2 != NULL )
	{
		delete temp1;
		temp1 = temp2;

		temp2 = temp2->next;
	}
	delete temp1;

	this->head = this->cursor = temp1 = temp2 = NULL;
}

bool ListNode::goToBeginning( )
{
	if( this->isEmpty( ) )
	{
		return false;
	}
	else
	{
		this->cursor = this->head;
	}
}

bool ListNode::goToEnd( )
{
	if( this->isEmpty( ) )
	{
		return false;
	}
	else
	{
		while( this->cursor->next != NULL )
			this->cursor = this->cursor->next;
		return true;
	}
}

bool ListNode::goToNext( )
{
	if( this->isEmpty( ) )
	{
		return false;
	}
	else if( this->cursor->next == NULL )
	{
		return false;
	}
	else
	{
		this->cursor = this->cursor->next;
		return true;
	}
}

bool ListNode::goToPrior( )
{
	if( this->isEmpty( ) )
	{
		return false;
	}
	else if( this->cursor == this->head )
	{
		return false;
	}
	else
	{
		Node* temp = this->head;
		while( temp->next != this->cursor )
			temp = temp->next;

		this->cursor = temp;

		return true;
	}
}

bool ListNode::isEmpty( ) const
{
	if( this->head == NULL && this->cursor == NULL )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ListNode::isFull( ) const
{
	return false;
}

ListNode& ListNode::operator = ( const ListNode& copy )
{
	if( this == &copy )
	{
		return *this;
	}

	this->clear( );

	if( copy.isEmpty( ) )
	{
		this->cursor = this->head = NULL;
	}
	else
	{
		Node* tempCopy = copy.head;
		Node* tempThis = new Node( tempCopy->data, NULL );
		this->head = tempThis;

		if( copy.cursor == tempCopy )
		{
			this->cursor = tempThis;
		}

		Node* temp = tempThis;

		tempCopy = tempCopy->next;
		tempThis = tempThis->next;


		while( tempCopy != NULL )
		{
			tempThis = new Node( tempCopy->data, NULL );
			temp->next = tempThis;

			temp = temp->next;

			if( copy.cursor == tempCopy )
			{
				this->cursor = tempThis;
			}

			tempCopy = tempCopy->next;
			tempThis = tempThis->next;
		}
	}

	return *this;
}
 
ostream& operator << ( ostream& out, const ListNode& source )
{
	if( source.isEmpty( ) )
	{
		return out;
	}
	else
	{
		Node* temp = source.head;
		while( temp != NULL )
		{
			out << temp->data;
			out << " ";
			temp = temp->next;
		}

		return out;
	}
}

