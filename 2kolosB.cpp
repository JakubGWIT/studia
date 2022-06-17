#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
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

void add_position(Double_list &l, int &value, int &position)//uzupelnic, git
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



//kolejka

struct ElementKol
{
    int Value;
    ElementKol *Next;
};

struct Queueue
{
    ElementKol *Head;
    ElementKol *Tail;
};

void push(Queueue &q, int value)//git
{
    ElementKol *el=new ElementKol;
    el->Value=value;
    el->Next=nullptr;
    if(q.Tail!=nullptr)
    {
        q.Tail->Next=el;
    }
    else q.Head=el;
    q.Tail=el;
}

void pop(Queueue &q)//git
{
    ElementKol *temp=q.Head;
    q.Head=q.Head->Next;
    delete temp;
    if(q.Head==nullptr)
    {
        q.Tail=nullptr;
    }
}

bool isEmptyQ(Queueue q)//git
{
    if(q.Head==nullptr)
    {
        return 1;
    }
    else return 0;
}

int first(Queueue q)//git
{
    return q.Head->Value;
}

void wyswietl(Queueue q)//nie ma w skrypcie
{
    ElementKol *temp=q.Head;
    while(temp!=nullptr)
    {
        cout<<temp->Value<<"\t";
        temp=temp->Next;
    }
    cout<<endl;
    delete temp;
}

void zad1(Queueue &q, Queueue &q2)
{
    int x, licz=0;
    ifstream plik;
    plik.open("zad1b.txt");
    while(!plik.eof())
    {
        plik>>x;
        if(x>0) push(q,x);
        else push(q2,x);
    }
    ElementKol *z=q.Head;
    ElementKol *z2=q2.Head;
    while(z!=nullptr&&z2!=nullptr)
    {
        if(abs(z->Value)==abs(z2->Value))
        {
            licz++;
        }
        z=z->Next;
        z2=z2->Next;
    }

    cout<<"Kolejki: "<<endl;
    wyswietl(q);
    wyswietl(q2);
    cout<<"Liczba przypadkow: "<<licz<<endl;
}

void zad2(Double_list &l)
{
    int x=rand()%21-10;
    while(x)
    {
        cout<<"Wylosowana liczba:   "<<x<<endl;
        if(x>0) add_tail(l,x);
        else add_head(l,x);
        x=rand()%21-10;
    }
    //cout<<"Zawartosc listy: "<<endl;
    //showToEnd(l);
}
/*
void zad3(Double_list &l)
{
    int n=(l.counter)/2, x;
    cout<<"\nZawartosc listy: "<<endl;
    showToEnd(l);
    cout<<endl;
    Element *pocz=l.head;
    Element *kon=l.tail;
    for(int i=1; i<=n; i++)
    {
        cout<<pocz->number<< " + "<<kon->number<<" = "<<pocz->number+kon->number<<endl;
        if((pocz->number+kon->number)<0)
        {
            x=l.counter;
            delete_position(l,(x+1-i));
            delete_position(l,i);
        }
        pocz=pocz->next;
        kon=kon->prev;
    }
    cout<<"\nZawartosc listy PO: "<<endl;
    showToEnd(l);
}
*/


void zad3(Double_list &l)
{
    int n=(l.counter)/2, x, usunietych=0;
    cout<<"\nZawartosc listy: "<<endl;
    showToEnd(l);
    cout<<endl;
    Element *pocz=l.head;
    Element *kon=l.tail;
    for(int i=1; i<=n; i++)
    {
        Element *pocz2=pocz->next;
        Element *kon2=kon->prev;
        x=l.counter;
        cout<<pocz->number<< " + "<<kon->number<<" = "<<pocz->number+kon->number<<endl;
        if((pocz->number+kon->number)<0)
        {
            delete_position(l,(x-i+1+usunietych));
            delete_position(l,i-usunietych);
            usunietych++;
        }
        pocz=pocz2;
        kon=kon2;
    }
    cout<<"\nZawartosc listy PO: "<<endl;
    showToEnd(l);
}


/*
void zad3(Double_list &l)
{
    showToEnd(l);
    int start=1;
    int end=l.counter;
    Element *x=l.head;
    Element *y=l.tail;
    while(start < end)
    {
        Element *a=x->next;
        Element *b=y->prev;

        cout << x->number << " + " << y->number << " = " << x->number+y->number << endl;
        if(x->number + y->number<0) {
            delete_position(l, end);
            delete_position(l, start);
            end -= 2;
        }else {
            start++;
            end--;
        }
        x = a;
        y = b;
    }
    showToEnd(l);
}
*/

int main()
{
    Double_list l;
    l.head=nullptr;
    l.tail=nullptr;
    l.counter=0;

    Queueue q;
    q.Head=nullptr;
    q.Tail=nullptr;

    Queueue q2;
    q2.Head=nullptr;
    q2.Tail=nullptr;

    srand(time(NULL));
    zad1(q,q2);
    zad2(l);
    zad3(l);
    //cout<<"\nZawartosc listy: "<<endl;
    return 0;
}
