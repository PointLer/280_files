#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "Dlist.h"
#include "Instr.h"

using namespace std;
const int MEM_ARRAY = 16;

void ADD_fun(Dlist<int>& oper);
//REQUIREs: Dlist must contain at least 2 numbers.
//EFFECTs:  Popping up two elements from the stack and pushing their sum into the stack.

void NOR_fun(Dlist<int>& oper);
//REQUIREs: Dlist must contain at least 2 numbers.
//EFFECTs:  Popping up two elements from the stack and pushing their NOR result into the stack.

void IFZ_fun(int n, Dlist<Instr>& ins, Dlist<int>& oper);
//REQUIREs: Dlist<Instr> must contain at least n instructions.
//EFFECTs:  Pop up the first element in the stack. If zero, we pop up 
//          the following n instructions in the queue. Continue executing the next instruction otherwise.

void LOAD_fun(Dlist<int>& oper, int mem[]);
//REQUIREs: Dlist must contain at least 1 numbers.
//EFFECTs:  Pop up one element from the stack, find the value stored at this address and push it into the stack.

void STORE_fun(Dlist<int>& oper, int mem[]);
//REQUIREs: Dlist must contain at least 2 numbers.
//EFFECTs:  Popping up two elements from the stack. The first element is the address and the second is the value.

void POP_fun(Dlist<int>& oper);
//EFFECTs:  Pop up an element from the stack.

void PUSHI_fun(Dlist<int>& oper, int n);
//EFFECTs:  Push a constant n into the stack.

int main(int argc, char *argv[])
{
    //initialization:
    int operands, instructions;
    cin >> operands >> instructions;
    Dlist<int> oper_stack;
    Dlist<Instr> ins_queue;
    int mem_array[MEM_ARRAY];

    //operands:
    for(int i = 0; i < operands; i++){
        int *temp = new int;
        cin >> *temp;
        oper_stack.insertBack(temp);
    }

    //instructions:
    for(int j = 0; j < instructions; j++){
        Instr *temp = new Instr;
        cin >> *temp;
        ins_queue.insertBack(temp);
    }

    //memory array:
    for(int k = 0; k < MEM_ARRAY; k++){
        cin >> mem_array[k];
    }

    //implementation of the stack machine:
    for(int l = 0; l < instructions; l++){
        Instr *victim = ins_queue.removeFront();
        cout << *victim << endl;
        int cur_ins = (int)victim->name;
        switch(cur_ins){
        case 0://ADD
            ADD_fun(oper_stack);
            break;
        case 1://NOR
            NOR_fun(oper_stack);
            break;
        case 2://IFZ
            IFZ_fun(victim->parameter, ins_queue, oper_stack);
            l += victim->parameter;
            break;
        case 3://HALT
            break;
        case 4://LOAD
            LOAD_fun(oper_stack,mem_array);
            break;
        case 5://STORE
            STORE_fun(oper_stack,mem_array);
            break;
        case 6://POP
            POP_fun(oper_stack);
            break;
        case 7://PUSHI
            PUSHI_fun(oper_stack, victim->parameter);
            break;
        default://NOOP
            break;
        }
        delete victim;

        //print the results:
        cout << oper_stack << endl;
        cout << ins_queue << endl;
        for(int m = 0; m < MEM_ARRAY; m++){
            cout << mem_array[m] <<" ";
        }
        cout << endl;

        //break if the instruction is HALT:
        if(cur_ins == 3)
            break;
    }
    return 0;
}

void ADD_fun(Dlist<int>& oper){
    int *victim1 = oper.removeBack();
    int *victim2 = oper.removeBack();
    int *sum = new int(*victim1 + *victim2);
    oper.insertBack(sum);
    delete victim1;
    delete victim2;
}

void NOR_fun(Dlist<int>& oper){
    int *victim1 = oper.removeBack();
    int *victim2 = oper.removeBack();
    int *nor = new int(~(*victim1 | *victim2));
    oper.insertBack(nor);
    delete victim1;
    delete victim2;
}

void IFZ_fun(int n, Dlist<Instr>& ins, Dlist<int>& oper){
    int *victim = oper.removeBack();
    if(*victim == 0){
        for(int i = 0; i < n; i++){
            Instr *temp = ins.removeFront();
            delete temp;
        }
    }
    delete victim;
}

void LOAD_fun(Dlist<int>& oper, int mem[]){
    int *victim = oper.removeBack();
    int *new_load = new int(mem[*victim]);
    oper.insertBack(new_load);
    delete victim;
}

void STORE_fun(Dlist<int>& oper, int mem[]){
    int *victim1 = oper.removeBack();
    int *victim2 = oper.removeBack();
    mem[*victim1] = *victim2;
    delete victim1;
    delete victim2;
}

void POP_fun(Dlist<int>& oper){
    int *victim = oper.removeBack();
    delete victim;
}

void PUSHI_fun(Dlist<int>& oper, int n){
    int *new_num = new int(n);
    oper.insertBack(new_num);
}