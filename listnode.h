#include <iostream>
#include "Node.h"

using namespace std;

template <class T>
class Node 
{
    private:
        Node(T, Node*);
        
        T data;
        Node *next;

        friend class ListNode<T>;
        friend ostream& operator << (ostream&, const ListNode<T>&);
};

template <class T>
class ListNode 
{
    public:
        ListNode(int=10);
        ListNode(const ListNode&);
        ~ListNode();

        bool insertAfter(int);
        bool insertBefore(int);
        bool get(int&) const;
        bool remove(int&);

        void clear();

        bool goToBeginning();
        bool goToEnd();

        bool goToNext();
        bool goToPrior();

        bool isEmpty() const;
        bool isFull() const;

        ListNode& operator = (const ListNode&);

        friend ostream& operator << (ostream&, const ListNode&);

    private:
        Node<T> *head;
        Node<T> *cursor;
};


