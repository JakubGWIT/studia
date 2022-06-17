#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
using namespace std;

struct Element
{
    int number;
    Element *next;
    Element *prev;
};

struct Double_list
{
    Element *head;
    Element *tail;
    int counter;
};

void add_tail(Double_list &l, int value)//git
{
    Element *el = new Element;
    el->number=value;
    el->next=nullptr;
    el->prev=nullptr;
    if(l.tail!=nullptr)
    {
        l.tail->next=el;
        el->prev=l.tail;
    }
    else
    {
        l.head=el;
    }
    l.counter++;
    l.tail=el;
}

void add_head(Double_list &l, int value)//sprawdzic!!!
{
    Element *el=new Element;
    el->number=value;
    el->next=nullptr;
    el->prev=nullptr;
    if(l.head!=nullptr)
    {
        l.head->prev=el;
        el->next=l.head;
    }
    else
    {
        l.tail=el;
    }
    l.counter++;
    l.head=el;
}

void add_position(Double_list &l, int &value, int position)//uzupelnic, git
{
    if(position==1) add_head(l,value);
    else
    {
        if(position==l.counter+1) add_tail(l,value);
        else
        {
            if (position<1||position>l.counter) cout<<"Nieprawidlowa pozycja"<<endl;
            else
            {
                Element *temp=l.head;
                int i=1;
                while(i<position-1)
                {
                    temp=temp->next;
                    i++;
                }
                Element *el=new Element;
                el->number=value;
                el->prev=temp;
                el->next=temp->next;
                temp->next->prev=el;
                temp->next=el;
                l.counter++;
            }
        }
    }
}

void delete_tail(Double_list &l)//git, dodac counter
{
    Element *temp=l.tail;
    if(l.counter==1)
    {
        l.tail=nullptr;
        l.head=nullptr;
    }
    else
    {
        l.tail=l.tail->prev;
        l.tail->next=nullptr;
    }
    l.counter--;
    delete temp;
}

void delete_head(Double_list &l)//git, dodac counter
{
    Element *temp=l.head;
    if(l.counter==1)
    {
        l.tail=nullptr;
        l.head=nullptr;
    }
    else
    {
        l.head=l.head->next;
        l.head->prev=nullptr;
    }
    l.counter--;
    delete temp;
}

void delete_position(Double_list &l, int position)//dodac if'y i counter
{
    if(position==1) delete_head(l);
    else
    {
        if(position==l.counter) delete_tail(l);
        else
        {
            if (position<1||position>l.counter) cout<<"Nieprawidlowa pozycja"<<endl;
            else
            {
                Element *temp=l.head;
                int i=1;
                while(i<position-1)
                {
                    temp=temp->next;
                    i++;
                }
                Element *temp_us=temp->next;
                temp->next=temp_us->next;
                temp->next->prev=temp;
                l.counter--;
                delete temp_us;
            }
        }
    }
}

void showToEnd(Double_list l)//sam pisalem
{
    //cout<<"Lista: "<<endl;
    int i=1;
    Element *temp=l.head;
    while(i<=l.counter)
    {
        cout<<"\t"<<temp->number;
        temp=temp->next;
        i++;
    }
    cout<<endl;
}

void showToBeg(Double_list l)//sam pisalem
{
    //cout<<"Lista: "<<endl;
    int i=l.counter;
    Element *temp=l.tail;
    while(i>0)
    {
        cout<<"\t"<<temp->number;
        temp=temp->prev;
        i--;
    }
    cout<<endl;
}

bool isEmpty(Double_list l)//sam pisalem
{
    if(l.head==nullptr) return true;
    else return false;
}

double suma(Double_list l)
{
    int x=0,i=1;
    Element *temp=l.head;
    while(i<=l.counter)
    {
        x+=temp->number;
        temp=temp->next;
        i++;
    }
    return x;
}

void zad1(Double_list l)
{
    ifstream plik;
    int x;
    plik.open("zad1a.txt");
    while(!plik.eof())
    {
        plik>>x;
        if(x%2==0) add_head(l,x);
        else add_tail(l,x);
    }
    showToEnd(l);
}

void zad2(Double_list &l)
{
    ifstream plik;
    int x, usunietych=0;
    plik.open("zad2a.txt");
    while(!plik.eof())
    {
        plik>>x;
        add_tail(l,x);
    }
    cout<<"Przed: "<<endl;
    showToEnd(l);
    Element *pocz=l.head;

    for(int k=1; k<=l.counter; k++)
    {
        int licz=0;
        Element *pocz2=pocz->next;
        for(int i=2; i<=sqrt(pocz->number)+1; i++)
        {
            if(((pocz->number)%i)==0)
            {
                licz++;
            }
        }
        if(licz==0)
        {
            delete_position(l,k-usunietych);
            usunietych++;
        }
        pocz=pocz2;
    }
    cout<<"Wynik zad2: "<<endl;
    showToEnd(l);
}

void zad3(Double_list &l)
{
    int  n=l.counter/2, x;
    Element *pocz=l.head;
    for(int i=1; i<=n; i++)
    {
        Element *pocz2=pocz->next->next;
        x=pocz->number*pocz->next->number;
        add_position(l,x,3*(i-1)+2);
        pocz=pocz2;
    }
    cout<<"Wyniki zad3: "<<endl;
    showToEnd(l);
}

int main()
{
    Double_list l;
    l.head=nullptr;
    l.tail=nullptr;
    l.counter=0;

    Double_list l2;
    l2.head=nullptr;
    l2.tail=nullptr;
    l2.counter=0;

    zad1(l);
    zad2(l);
    zad3(l);
    return 0;
}

