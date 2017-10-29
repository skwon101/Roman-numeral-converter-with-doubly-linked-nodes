#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "DoubleLinkNode.h"

class LinkedList
{
    public:
        LinkedList();
        LinkedList(DoubleLinkNode*);
        DoubleLinkNode* getHead();
        DoubleLinkNode* getTail();
        void setHead(DoubleLinkNode*&);
        void setTail();
        void print();
        void operator+=(DoubleLinkNode*&);
        LinkedList& operator--();
        LinkedList& operator--(int);
        void destroy();
        ~LinkedList();

    protected:

    private:
        DoubleLinkNode* head;
        DoubleLinkNode* tail;
};

#endif // LINKEDLIST_H
