//*********************************************************

//#ifndef _STACK_HPP
//#define _STACK_HPP     // include just once

// define  ADT
typedef int TIPOS; 

struct Stack
{
  int top;
  TIPOS items[250];
  Stack()  {  top = -1;  }
};

// define funciones del ADT
bool empty(Stack*);            // true si esta vacÃ­o
bool push(Stack*,TIPOS);    // true si hay problemas 
bool pop(Stack*,TIPOS*);    // true si hay problemas 
void clear(Stack*);
//#endif




