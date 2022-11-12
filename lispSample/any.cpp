#include <iostream>
#include <string>
#include <list>
#include <iterator>

using namespace std;

struct lispVar
{
    string value;
    lispVar* next;
} lispVar;

int main()
{
    list<struct lispVar> stringlist;

   struct lispVar lv_v2;
   lv_v2.value = "world";
   lv_v2.next = NULL;

    struct lispVar lv;
    lv.value = "hello";
    lv.next = &lv_v2;
    stringlist.push_back(lv);
    for(auto it = stringlist.begin(); it != stringlist.end(); it++)
    {
        cout << "Hello: " << it->value << endl;
        if(it->next) cout << "Hello: " << it->next->value << endl;
    }
}