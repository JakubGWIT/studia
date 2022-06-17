#include <iostream>
#include <fstream>

using namespace std;

struct element{
    int number;
    element * next;
};

struct struktura {
    int counter;
    element * head;
    element * tail;
};

bool czyPierwsza ( int a ){
    if ( a < 2 ){
        return false;
    }
    for ( int i = 2; i*i<=a; i++ ){
        if ( a%i == 0 ){
            return false;
        }
    }
    return true;
}

void wczytajZadanie1 ( struktura &l );
void wczytajZadanie2 ( struktura &l );
void show ( struktura l );
void addTail ( struktura &l, int value );
void addHead ( struktura &l, int value );
void addPosition ( struktura &l, int value, int position );
void usunPierwsze ( struktura &l );
void deleteTail ( struktura &l );
void deleteHead ( struktura &l );
void deletePosition ( struktura &l, int position );
void dodajIloczyn ( struktura &l );
void wyczyscStrukture ( struktura &l );


int main(){
    struktura l1;
    wyczyscStrukture(l1);
    cout << "zadanie 1.\n";
    wczytajZadanie1(l1);
    show(l1);
    wyczyscStrukture(l1);
    struktura l2;
    wyczyscStrukture(l2);
    cout << "\nzadanie 2.\n";
    wczytajZadanie2(l2);
    usunPierwsze(l2);
    show(l2);
    cout << "\nzadanie 3.\n";
    dodajIloczyn(l2);
    show(l2);
    wyczyscStrukture(l2);

    return EXIT_SUCCESS;
}


void addTail ( struktura &l, int value ){
    element * el = new element;
    el->number = value;
    el->next = nullptr;
    if ( l.tail != nullptr ){
        l.tail->next = el;
    } else {
        l.head = el;
    }
    l.tail = el;
    l.counter++;
}

void addHead ( struktura &l, int value ){
    element * el = new element;
    el->number = value;
    el->next = l.head;
    l.head = el;
    if ( l.tail == nullptr ){
        l.tail = el;
    }
    l.counter++;
}

void addPosition ( struktura &l, int value, int position ){
     if ( position <= l.counter && position > 1 ){
        element * el = new element;
        el -> number = value;
        element * temp = l.head;
        int i = 1;
        while ( i < position - 1 ){
            temp = temp -> next;
            i++;
        }
        el -> next = temp -> next;
        temp -> next = el;
        l.counter ++;
    } else if ( position == 1){
        addHead(l,value);
    } else if (  position == l.counter+1 ){
        addTail(l,value);
    } else cout << "error" << endl;
}

void wczytajZadanie1 ( struktura &l ){
    ifstream file;
    file.open("zad1a.txt");
    int data;
    while ( !file.eof() ){
        file>>data;
        if ( data % 2 == 0 ){
            addHead(l,data);
        } else {
            addTail(l,data);
        }
    }
    file.close();
}

void wczytajZadanie2 ( struktura &l ){
    ifstream file;
    file.open("zad2a.txt");
    int data;
    while ( !file.eof() ){
        file>>data;
        addTail(l,data);
    }
    file.close();
}

void show ( struktura l ){
    element * temp = l.head;
    int i = 1;
    while ( i <= l.counter ){
        cout << temp->number << " ";
        temp = temp->next;
        i++;
    }
    delete temp;
    cout << endl;
}

void deleteTail ( struktura &l ){
    if ( l.counter != 0 ){
        element * temp = l.tail;
        if ( l.counter == 1 ){
            l.tail=nullptr;
            l.head=nullptr;
        } else {
            element * bef_temp = l.head;
            int i = 1;
            while ( i < l.counter-1 ){
                bef_temp=bef_temp->next;
                i++;
            }
            l.tail=bef_temp;
            l.tail->next=nullptr;
        }
        delete temp;
        l.counter--;
    } else {
        cout << "pusto!" << endl;
    }
}

void deleteHead ( struktura &l ){
    if ( l.counter != 0 ){
        element * temp = l.head;
        l.head=l.head->next;
        if ( l.counter == 1 ){
            l.tail=nullptr;
        }
        delete temp;
        l.counter--;
    } else {
        cout << "pusto!" << endl;
    }

}

void deletePosition ( struktura &l, int position ){
    if ( l.counter != 0 ){
        if ( position == 1 ){
            deleteHead(l);
        } else if ( position == l.counter ){
            deleteTail(l);
        } else {
            element * prev = l.head;
            int i = 1;
            while ( i < position-1 ){
                prev = prev->next;
                i++;
            }
            element * temp = prev->next;
            prev->next = temp->next;
            delete temp;
            l.counter--;
        }
    } else {
        cout << "pusto!" << endl;
    }
}

void usunPierwsze ( struktura &l ){
    element * temp = l.head;
    int i = 1;
    while ( i <= l.counter ){
        if ( czyPierwsza(temp->number) ){
            temp = temp->next;
            deletePosition(l,i);
            continue;
        }
        temp = temp->next;
        i++;
    }
}

void dodajIloczyn ( struktura &l ){
    element * temp = l.head;
    element * temp2 = l.head->next;
    int i = 1;
    while ( i < l.counter ){
        int a = temp->number*temp2->number;
        for ( int j = 0; j < 2; j++ ){
            temp=temp->next;
            temp2=temp2->next;
        }
        addPosition(l,a,i+1);
        i+=3;
    }
    delete temp, temp2;
}

void wyczyscStrukture ( struktura &l ){
    l.counter=0;
    l.head=nullptr;
    l.tail=nullptr;
}
