//William Kwon
//wsk160030
//DELETE ANY NODE

/*
1. See if the nodes are as they were in ascending order by Arabic numeral after binary search.(! if it is roman search.)
2. Finish the print function and Destructor in LinkedList.cpp 
3. Erase print code at the end before submission.
4. Make BaseNode.cpp abstract.
5. Sort doesn't work after add. O!
Keep in mind of the usage of dynamically allocated pointer!
*/

#include <iostream>
#include "BaseNode.h"
#include "DoubleLinkNode.h"
#include "LinkedList.h"
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

string ConvertToRoman(int);
int ConvertToArabic(string);
void SortRoman(LinkedList&);
void SortArabic(LinkedList&);
bool search(LinkedList&,string);

int main( int argc, char *argv[])
{
	if(argc==1)
		string filename=argv[0];
    LinkedList list;
    const int romeNum=15, arabicNum=4;
    ifstream nameFile;
    nameFile.open(filename, ios::binary);
    char ch;
    int x;
    int position;
    //cout<<"before if ";
    if (nameFile)
    {
        bool firstLine=true;
        while (!nameFile.eof())
        {
            DoubleLinkNode* line=new DoubleLinkNode;
            nameFile.get(ch);
            position=nameFile.tellg();
            position=position-1;
            if(position == -2) break;
            if (ch==' ')
            {
                nameFile.seekg(15, ios::cur);
                bool insert=true;
                int sum=0;
                for (int i=0;i<arabicNum;i++)
                {
                    nameFile.get(ch);
                    x = ch - '0';
                    if (ch==' ') break;
                    else if(x>9||x<0)   //if x is not a number, then ignore the line.
                    {
                        insert=false;
                        break;
                    }
                    sum = sum*10 + x;
                }
                if(sum>4999||sum<1) //if the Arabic numeral is greater than 4999 or less than 1, ignore the line.
                {
                    insert=false;
                }

                if(insert)
                {
                    //cout<<"FF";
                    line->setArabic(sum);
                    line->setRoman(ConvertToRoman(sum)); //insert the data into a node.
                    //cout<<"SSS";
                }
                nameFile.seekg(position, ios::beg);
                nameFile.seekg(22,ios::cur);
            }

            else
            {
                nameFile.seekg(position, ios::beg);
                string rom;
                for (int i=0;i<romeNum;i++)
                {
                    nameFile.get(ch);
                    if (ch==' ') break;
                    rom+=ch;
                }
                //cout<<rom<<endl;
                bool insert=true;
                if(ConvertToArabic(rom)>4999||ConvertToArabic(rom)<1)   //if the converted numeral is greater than 4999 or less than 1, ignore the line.
                {
                    insert=false;
                }
                else
                {
                    for(unsigned int i=0;i<rom.length();i++)
                    {
                        //cout<<rom[i]<<" ";
                        if(rom[i]!='I'&&rom[i]!='V'&&rom[i]!='X'&&rom[i]!='L'&&rom[i]!='C'&&rom[i]!='D'&&rom[i]!='M')   //if there is no roman numeral, ignore the line.
                        {
                            insert=false;
                            break;
                        }
                    }
                }

                if(insert)
                {
                    //cout<<"F";
                    line->setRoman(rom);
                    line->setArabic(ConvertToArabic(rom));   //insert the data into a node.
                    //cout<<"A";
                }
                nameFile.seekg(position, ios::beg);
                nameFile.seekg(22, ios::cur);
            }

            if(firstLine)
            {
                list.setHead(line);
                list.setTail();
                firstLine=false;
                //cout<<"int this if statement"<<endl;
            }
            else
            {
                //cout <<"in the else statement" << endl;
                list+=line;
            }
            //cout<<list.getHead()->getArabic()<<"    "<<list.getHead()->getRoman()<<endl;
            //cout<<list.getTail()->getArabic()<<"    "<<list.getTail()->getRoman()<<endl;
            //cout<<"FF";
        }

    }
    nameFile.close();
    SortArabic(list);

    bool exit=false;
    while(!exit)
    {
        int answer;
        cout<<"1. Search"<<endl;    //show the options.
        cout<<"2. Add"<<endl;
        cout<<"3. Delete first"<<endl;
        cout<<"4. Delete last"<<endl;
        cout<<"5. Delete specific node"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"Choose an option by typing a number. ";
        cin>>answer;

        if(answer==1)
        {
            string input;
            cout<<"Type the value to search. ";
            cin>>input;
            if(search(list,input))    //search.
                cout<<input<<" found."<<endl;
            else
                cout<<input<<" not found."<<endl;
        }
        else if(answer==2)
        {
            DoubleLinkNode* add=new DoubleLinkNode;
            cin>>*add;
            if(add->getArabic()==0&&add->getRoman()=="")
                cout<<"Type something!"<<endl;
            else if(add->getArabic()==0)
                add->setArabic(ConvertToArabic(add->getRoman()));
            else
                add->setRoman(ConvertToRoman(add->getArabic()));
            list+=add;
            //cout<<list.getTail()->getArabic();
            SortArabic(list);
        }
        else if(answer==3)
        {
            --list;
        }
        else if(answer==4)
        {
            list--;
        }
        else if(answer==5)
        {
            string input;
            cout<<"Type the value to delete. ";
            cin>>input;
            if(search(list,input))    //search.
            {
                DoubleLinkNode* ptr=list.getHead();
                if(input[0]<='9'&&input[0]>='0')
                {
                    int tempInput=atoi(input.c_str());
                    while(ptr->getArabic()!=tempInput)
                        ptr=ptr->getNext();
                }
                else
                {
                    while(ptr->getRoman()!=input)
                        ptr=ptr->getNext();
                }

                if(!ptr->getPrev())
                {
                    --list;
                }
                else if(!ptr->getNext())
                {
                    list--;
                }
                else
                {
                    DoubleLinkNode* prePtr=ptr->getPrev();
                    DoubleLinkNode* postPtr=ptr->getNext();
                    prePtr->setNext(postPtr);
                    postPtr->setPrev(prePtr);
                    ptr->setNext(nullptr);
                    ptr->setPrev(nullptr);
                    delete ptr;

                }
            }
            else
                cout<<input<<" not found."<<endl;
        }
        else if(answer==6)
        {
            exit=true;
        }
        else
            cout<<"Invalid number."<<endl;
    }

    ofstream newLine("numbers.txt");
    newLine.close();
    /*DoubleLinkNode* out=list.getTail();
    while(out)
    {
        cout<<out->getArabic()<<"   "<<out->getRoman()<<endl;
        out=out->getPrev();
    }*/

    //nameFile2.close();
    list.print();
    list.~LinkedList();
}


string ConvertToRoman(int i)
{
    string str;
    int thousands=i/1000;
    int hundreds=i%1000/100;
    int tens=i%1000%100/10;
    int ones=i%1000%100%10;
    if (thousands>0&&thousands<=4)
        for (int i=0;i<thousands;i++)
        {
            str+="M";
        }
    if (hundreds>0&&hundreds<4)
        for (int i=0;i<hundreds;i++)
        {
            str+="C";
        }
    else if (hundreds==4)
    {
        str+="CD";
    }
    else if (hundreds==5)
    {
        str+="D";
    }
    else if (hundreds>5&&hundreds<9)
    {
        str+="D";
        for (int i=0;i<hundreds-5;i++)
        {
            str+="C";
        }
    }
    else if(hundreds==9)
    {
        str+="CM";
    }
    if (tens>0&&tens<4)
    {
        for(int i=0;i<tens;i++)
        {
            str+="X";
        }
    }
    else if (tens==4)
    {
        str+="XL";
    }
    else if (tens==5)
    {
        str+="L";
    }
    else if (tens>5&&tens<9)
    {
        str+="L";
        for (int i=0;i<tens-5;i++)
        {
            str+="X";
        }
    }
    else if(tens==9)
    {
        str+="XC";
    }
    if (ones>0&&ones<4)
    {
        for(int i=0;i<ones;i++)
        {
            str+="I";
        }
    }
    else if (ones==4)
    {
        str+="IV";
    }
    else if (ones==5)
    {
        str+="V";
    }
    else if (ones>5&&ones<9)
    {
        str+="V";
        for(int i=0;i<ones-5;i++)
        {
            str+="I";
        }
    }
    else if (ones==9)
    {
        str+="IX";
    }
    return str;
}

int ConvertToArabic(string s)
{
    int sum=0;
    for(unsigned int i=0;i<s.length();i++)
    {
        char p=s[i-1];
        char c=s[i];
        char c2=s[i+1];
        if (c=='M')
        {
            if(p=='C');
            else
                sum+=1000;
        }
        else if (c=='D')
        {
            if(p=='C');
            else
                sum+=500;
        }
        else if (c=='C'&&c2=='M')
        {
            sum+=900;
        }
        else if (c=='C'&&c2=='D')
        {
            sum+=400;
        }
        else if (c=='C')
        {
            if(p=='X');
            else
                sum+=100;
        }
        else if (c=='L')
        {
            if(p=='X');
            else
                sum+=50;
        }
        else if (c=='X'&&c2=='C')
        {
            sum+=90;
        }
        else if (c=='X'&&c2=='L')
        {
            sum+=40;
        }
        else if (c=='X')
        {
            if(p=='I');
            else
                sum+=10;
        }
        else if (c=='V')
        {
            if(p=='I');
            else
                sum+=5;
        }
        else if (c=='I'&&c2=='X')
        {
            sum+=9;
        }
        else if (c=='I'&&c2=='V')
        {
            sum+=4;
        }
        else if (c=='I')
        {
            sum+=1;
        }

    }
    return sum;
}

void SortRoman(LinkedList &list)//selection sort
{
    int count=0;
    DoubleLinkNode* num=list.getHead();
    while(num)
    {
        num=num->getNext();
        count++;
    }

    DoubleLinkNode* ptr;
    DoubleLinkNode* temp;
    DoubleLinkNode* prePtr;
    DoubleLinkNode* postPtr;
    bool swap;
    do
    {
        ptr=list.getHead();
        swap=false;
        for(int i=1;i<count;i++)
        {
            //cout<<ptr->arabic<<" "<<ptr->next->arabic<<endl;
            if(ptr->getRoman()>ptr->getNext()->getRoman())
            {
                if(i==1)    //arrange the nodes.
                {
                    temp=ptr->getNext();
                    postPtr=temp->getNext();
                    ptr->setNext(postPtr);
                    ptr->setPrev(temp);
                    temp->setNext(ptr);
                    temp->setPrev(nullptr);
                    postPtr->setPrev(ptr);
                    list.setHead(temp);
                    ptr=list.getHead();
                }

                else if(i==(count-1))
                {
                    temp=ptr->getNext();
                    prePtr=ptr->getPrev();
                    ptr->setNext(nullptr);
                    ptr->setPrev(temp);
                    temp->setPrev(prePtr);
                    temp->setNext(ptr);
                    prePtr->setNext(temp);
                }

                else
                {
                    temp=ptr->getNext();
                    prePtr=ptr->getPrev();
                    postPtr=temp->getNext();
                    ptr->setNext(postPtr);
                    ptr->setPrev(temp);
                    temp->setNext(ptr);
                    temp->setPrev(prePtr);
                    prePtr->setNext(temp);  //link the previous node with arranged nodes.
                    postPtr->setPrev(ptr);
                    ptr=temp;
                }
                swap=true;
                //cout<<ptr->arabic<<" "<<ptr->next->arabic<<" "<<ptr->next->next->arabic<<endl;
            }
            ptr=ptr->getNext();
        }
    }while(swap);
//    list.setTail();
    //print(head);
}

void SortArabic(LinkedList &list)//selection sort
{
    int count=0;
    DoubleLinkNode* num=list.getHead();
    while(num)
    {
        num=num->getNext();
        count++;
    }
    //cout<<count;
    DoubleLinkNode* ptr;
    DoubleLinkNode* temp;
    DoubleLinkNode* prePtr;
    DoubleLinkNode* postPtr;
    bool swap;
    do
    {
        ptr=list.getHead();
        //cout<<ptr->getArabic()<<" "<<ptr->getNext()->getArabic()<<endl;
        swap=false;
        for(int i=1;i<count;i++)
        {
            if(ptr->getArabic()>ptr->getNext()->getArabic())
            {
                //cout<<ptr->getArabic()<<"   ";
                if(i==1)    //arrange the nodes.
                {
                    temp=ptr->getNext();
                    postPtr=temp->getNext();
                    ptr->setNext(postPtr);
                    ptr->setPrev(temp);
                    temp->setNext(ptr);
                    temp->setPrev(nullptr);
                    postPtr->setPrev(ptr);
                    list.setHead(temp);
                    ptr=list.getHead();
                }

                else if(i==(count-1))
                {
                    temp=ptr->getNext();
                    prePtr=ptr->getPrev();
                    ptr->setNext(nullptr);
                    ptr->setPrev(temp);
                    temp->setPrev(prePtr);
                    temp->setNext(ptr);
                    prePtr->setNext(temp);
                }

                else
                {
                    temp=ptr->getNext();
                    prePtr=ptr->getPrev();
                    postPtr=temp->getNext();
                    ptr->setNext(postPtr);
                    ptr->setPrev(temp);
                    temp->setNext(ptr);
                    temp->setPrev(prePtr);
                    prePtr->setNext(temp);  //link the previous node with arranged nodes.
                    postPtr->setPrev(ptr);
                    ptr=temp;
                }
                swap=true;
                //cout<<ptr->arabic<<" "<<ptr->next->arabic<<" "<<ptr->next->next->arabic<<endl;
            }
            ptr=ptr->getNext();
            //cout<<"SSSS";
        }
    }while(swap);
    list.setTail();
    //print(head);
}

bool search(LinkedList &list, string s)
{
    int count=0;
    DoubleLinkNode* num=list.getHead();
    while(num)
    {
        num=num->getNext();
        count++;
    }

    int left=1, right=count, middle;
    bool found=false;

    if(s[0]<='9'&&s[0]>='0')
    {
        int sum=0;
        int x;
        for(unsigned int i=0;i<s.length();i++)   //change the string s to int.
        {
            x=s[i]-'0';
            sum=sum*10+x;
        }

        while(!found&&left<=right)  //do the binary search.
        {
            DoubleLinkNode* ptr=list.getHead();
            //print(head);
            middle=(left+right)/2;
            for(int i=0;i<middle-1;i++) //get to the middle node.
            {
                ptr=ptr->getNext();
            }
            if(ptr->getArabic()==sum)    //if found, swap 'found' true.
                found=true;
            else if(ptr->getArabic()>sum)
            {
                right=middle-1;
            }
            else
                left=middle+1;
        }

        if(found)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    else
    {
        SortRoman(list);    //sort the list.
        while(!found&&left<=right)
        {
            DoubleLinkNode* ptr=list.getHead();
            //print(head);
            middle=(left+right)/2;
            for(int i=0;i<middle-1;i++) //move to the middle node.
            {
                ptr=ptr->getNext();
            }
            if(ptr->getRoman()==s)   //if found, swap 'found' true.
                found=true;
            else if(ptr->getRoman()>s)
            {
                right=middle-1;
            }
            else
                left=middle+1;
        }
        SortArabic(list);
        //print(head);
        if(found)
        {
            return true;
        }
        else
        {
            return false;
        }
        //print(head);
    }
}
