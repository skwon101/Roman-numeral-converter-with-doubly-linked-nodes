#ifndef BASENODE_H
#define BASENODE_H
#include <string>
#include <iostream>

using namespace std;
class BaseNode;

ostream &operator << (ostream &,const BaseNode &);
istream &operator >> (istream &,BaseNode &);

class BaseNode
{
    public:
        BaseNode();
        BaseNode(string,int);
        BaseNode(const BaseNode&);  //have to use translator funtions in project3 when needed.
        string getRoman();
        int getArabic();
        virtual void setRoman(string)=0;
        virtual void setArabic(int)=0;
        friend ostream &operator << (ostream &,const BaseNode &);
        friend istream &operator >> (istream &,BaseNode &);
        //overloaded << and >> like cout, cin.
        virtual ~BaseNode();

    protected:
        string roman;
        int arabic;
    private:
};

#endif // BASENODE_H
