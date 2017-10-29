#include "BaseNode.h"
#include <iomanip>
#include <string>

BaseNode::BaseNode()
{
    roman="";
    arabic=0;//ctor
}

BaseNode::BaseNode(string r,int a)
{
    roman=r;
    arabic=a;
}

BaseNode::BaseNode(const BaseNode& obj)
{
    roman=obj.roman;
    arabic=obj.arabic;
}

string BaseNode::getRoman()
{
    return roman;
}

int BaseNode::getArabic()
{
    return arabic;
}

ostream& operator<<(ostream &strm,const BaseNode &obj)
{
    strm<<left<<setw(15)<<obj.roman<<" "<<setw(4)<<obj.arabic<<endl;
    return strm;
}

istream& operator>>(istream &strm,BaseNode &obj)
{
    cout<<"Type in Arabic or Roman numeral.";
    string s;
    strm>>s;
    if(s[0]<='9'&&s[0]>='0')
    {
        int sum=0;
        int x;
        for(int i=0;i<s.length();i++)   //change the string s to int.
        {
            x=s[i]-'0';
            sum=sum*10+x;
        }
        obj.arabic=sum;
    }
    else
        obj.roman=s;
    return strm;
}

BaseNode::~BaseNode()
{
    //dtor
}
