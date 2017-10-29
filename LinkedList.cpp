#include "LinkedList.h"
#include <fstream>
#include <iomanip>
#include <iostream>

LinkedList::LinkedList()
{
    head=nullptr;
    tail=nullptr;//ctor
}

LinkedList::LinkedList(DoubleLinkNode* h)
{
    head=h;
    setTail();
}

DoubleLinkNode* LinkedList::getHead()
{
    return head;
}

DoubleLinkNode* LinkedList::getTail()
{
    return tail;
}

void LinkedList::setHead(DoubleLinkNode* &h)
{
    head=h;
}

void LinkedList::setTail()
{
    tail=head;
    while(tail->getNext())
        tail=tail->getNext();
}

void LinkedList::print()
{
    const int romeNum=15;
    const int arabicNum=4;
    ofstream file("numbers.txt",ios::app);
    if(head)
    {
//        cout<<left<<setw(romeNum)<<head->getRoman()<<" ";
//        cout<<left<<setw(arabicNum)<<head->getArabic()<<"\n";
        file<<left<<setw(romeNum)<<head->getRoman()<<" ";
        file<<left<<setw(arabicNum)<<head->getArabic()<<"\n";
        head->setPrev(nullptr);
        head=head->getNext();
        file.close();
        print();
    }
}


void LinkedList::operator+=(DoubleLinkNode* &d)
{
    tail->setNext(d);
    d->setPrev(tail);
    tail=d;
}

LinkedList& LinkedList::operator--()
{
    head=head->getNext();
    head->setPrev(nullptr);
    return *this;
}

LinkedList& LinkedList::operator--(int)
{
    DoubleLinkNode* ptr=tail->getPrev();
    ptr->setNext(nullptr);
    tail=ptr;
    return *this;
}

void LinkedList::destroy()
{
    if(head)
    {
        head->setPrev(nullptr);
        head=head->getNext();
        destroy();
    }
}

LinkedList::~LinkedList()
{
    destroy();
//dtor
}
