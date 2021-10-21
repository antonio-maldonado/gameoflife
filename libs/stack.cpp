//******************************************************************************
/**
  Stack.cpp
  Funciones del Stack

  \author Ricardo Legarda SÃ¡enz.
  \date 2015-09-06 22:25:58  
*/
//******************************************************************************

// directivas del preprocesador
#include <iostream>
#include <cstring>
#include "stack.h"
using namespace std;

// *************************************************************
//  Definicion de funciones del Stack
// *************************************************************
// define funcion
bool empty( Stack *S )
{    return (S->top == -1);    }

// define funcion
bool pop( Stack *S, TIPOS *valor )
{
  if ( empty(S) == true )
    return true;
  *(valor) = S->items[(S->top)--];
  return false;
}

// define funcion
bool push( Stack *S, TIPOS valor )
{
  if ( S->top == 249 )
    return true;
  S->items[++(S->top)] = valor;
  return false;
}
void clear(Stack *S){
S->top=-1;
}
