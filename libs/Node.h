//******************************************************************************
/*
  Node.h
  Encabezados del Node

  \author Ricardo Legarda Sáenz.
  \date 2015-09-06 22:25:34 
*/
//******************************************************************************


#ifndef _NODE_HPP
#define _NODE_HPP     // include just once


// incluye los encabezados de la funciones a utilizar
#include <cstdlib>    // NULL
#include "stack.h"
using namespace std;
// definicion de estructuras de datos
typedef struct{
Stack x;
Stack y;
int color;

} TIPO;


// define estructura de nodos y funciones de creacion/eliminacion
struct Node 
{
  TIPO data;
  Node *next;
  Node *prev;
  Node ()  { prev=NULL;next=NULL;    } 
};
Node* CrearNode(void);
void EliminaNode(Node*);


#endif




