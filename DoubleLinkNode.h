#ifndef DOUBLELINKNODE_H
#define DOUBLELINKNODE_H
#include "BaseNode.h"


class DoubleLinkNode : public BaseNode
{
    public:
        DoubleLinkNode();
        DoubleLinkNode(DoubleLinkNode* n,DoubleLinkNode* p,string r,int a):BaseNode(r,a)
        {
            next=n;
            prev=p;
        }

        DoubleLinkNode(const DoubleLinkNode& obj):BaseNode(obj)
        {
            next=obj.next;
            prev=obj.prev;
        }

        DoubleLinkNode* getNext();
        DoubleLinkNode* getPrev();
        virtual void setArabic(int);
        virtual void setRoman(string);
        void setNext(DoubleLinkNode*);
        void setPrev(DoubleLinkNode*);
        virtual ~DoubleLinkNode();

    protected:

    private:
        DoubleLinkNode* next;
        DoubleLinkNode* prev;
};

#endif // DOUBLELINKNODE_H
