#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

void print(vector<struct lispVar>* a);

struct lispVar
{
    string value;
    vector<lispVar>* next;
} lispVar;

void printList(vector<struct lispVar>* a)
{
    cout << "( ";
    print(a);
    cout << " )" << endl;
}

void print(vector<struct lispVar>* a)
{
    for(auto it = a->begin(); it != a->end(); it++)
    {
        if((*it).next)
        {
            cout << "( " << (*it).value << " ";
            print((*it).next);
            cout << ") ";
        }
        else cout << (*it).value << " ";
    }
}

int main()
{
    cout << "Hello1" << endl;

    vector<struct lispVar>* a = new vector<struct lispVar>();

    struct lispVar a1;
    a1.value = "a1";
    a1.next = NULL;
    a->push_back(a1);

    cout << "Hello2" << endl;

    struct lispVar a2;
    a2.value = "a2";
    a2.next = NULL;
    a->push_back(a2);

    vector<struct lispVar>* b = new vector<struct lispVar>();
    struct lispVar a11;
    a11.value = "a11";
    a11.next = NULL;
    b->push_back(a11);

    cout << "Hello" << endl;
    a->at(0).next = b;

    if(a->at(0).next) cout << "Multidimensional Vector:" << a->at(0).next->at(0).value << endl;
    printList(a);
    
}