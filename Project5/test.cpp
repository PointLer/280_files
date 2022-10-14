#include <iostream>
#include "Dlist.h"
#include "DlistImpl.h"
using namespace std;

int main(){
    Dlist<int> trial;
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int *c = &a[0];
    trial.insertFront(c);
    trial.insertFront(c+1);
    trial.insertFront(c+2);
    trial.insertBack(c+7);
    trial.insertBack(c+8);
    trial.insertBack(c+9);
    trial.print();
}