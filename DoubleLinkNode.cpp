#include "DoubleLinkNode.h"

DoubleLinkNode::DoubleLinkNode()
{
    next=nullptr;
    prev=nullptr;//ctor
}

DoubleLinkNode* DoubleLinkNode::getNext()
{
    return next;
}

DoubleLinkNode* DoubleLinkNode::getPrev()
{
    return prev;
}

void DoubleLinkNode::setRoman(string r)
{
    roman=r;
}

void DoubleLinkNode::setArabic(int a)
{
    arabic=a;
}

void DoubleLinkNode::setNext(DoubleLinkNode* n)
{
    next=n;
}

void DoubleLinkNode::setPrev(DoubleLinkNode* p)
{
    prev=p;
}

DoubleLinkNode::~DoubleLinkNode()
{
    //dtor
}
