//Proyecto 1
//El juego de la vida
//Antonio Maldonado Pinzón
//Estructura de datos 2019

#include<iostream>
#include<cstring>
#include<ncurses.h>
#include<cstdlib>
#include<fstream>
#include<curses.h>
#include<unistd.h>
#include<time.h>
#include<stdio.h>
#include"libs/Node.h"
#include"libs/List.h"

const int ESCAPE=27;
#define TICKRATE 100
using namespace std;

// patrones iniciales 
void patron1(int*,int,int,int);
void patron2(int*,int,int,int);
void patron3(int*,int,int,int);

// funcion
void CicloVida(int *T0,int *T1,int sizeX,int sizeY){
  memset( T1, 0, sizeof(int)*sizeX*sizeY );  // limpia arreglo para t+1
  	for(int r = 1;r < sizeY-1;r++)
    	for(int c = 1;c < sizeX-1;c++){
       	// obtiene celda y cuenta vecinos vivos
       	int live = T0[r*sizeX+c];
       	int suma = 0;                                       // cuenta vecinos vivos
        	for(int rr = r-1;rr <= r+1;rr++)
          	for(int cc = c-1;cc <= c+1;cc++)
             	suma += T0[rr*sizeX+cc];
        		 	int s = suma - live;                             // elimina celda bajo analisis
        
//        Reglas de la Vida:
//  1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
//  2. Any live cell with two or three live neighbours lives on to the next generation.
//  3. Any live cell with more than three live neighbours dies, as if by overcrowding.
//  4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction. 
        
        // verifica reglas, actualiza estado de celdas vivas para t+1
        if((live &&(s == 2 || s == 3)) || (!live && s == 3))
          	T1[r*sizeX+c] = 1;
		}
}

// *************************************************************
//    Funcion principal
// *************************************************************
int main(int argc, char*argv[]){
  // declara variables modifiva

	int  maxX, maxY; 
	initscr();				
	keypad(stdscr,TRUE); //Declaramos que vamos a usar teclas
	nodelay(stdscr,TRUE);
	if(has_colors()){		//Declaramos los diferentes colores a utilizar
		start_color();
		init_pair(1,COLOR_MAGENTA,COLOR_BLACK);
      init_pair(2,COLOR_WHITE,COLOR_BLACK);
      init_pair(3,COLOR_CYAN,COLOR_BLACK);
      init_pair(4,COLOR_BLUE,COLOR_BLACK);
      init_pair(5,COLOR_YELLOW,COLOR_BLACK);
      init_pair(6,COLOR_RED,COLOR_BLACK);
      init_pair(7,COLOR_GREEN,COLOR_BLACK);
	}
	//definimos las dimensiones de la ventana
	maxX=250,maxY=100;
	//Definimos el numero de iteraciones
	int iteraciones=250;

 	int *active = new int[maxX*maxY]; 
  	int *inactive = new int[maxX*maxY];
	int x,y;	//Variables para saber en que coordenadas esta una celula en una iteracion
	int ch;	//Variable para saber que tecla se presiono
	int top;	//Variable para saber la poblacion
	int col=0; //Variable para cambiar de color
	//Pantalla de inicio
  	while((ch=getch())==ERR){
		mvprintw(0,0,"EL JUEGO DE LA VIDA");
		mvprintw(1,0,"Utilice la flecha de arriba para moverse a la siguiente iteracion");
		mvprintw(2,0,"Utilice la flecha de abajo para moverse a la iteracion anterior");
		mvprintw(3,0,"Para salir del juego presione ESCAPE");
		mvprintw(4,0,"Se recomienda utilizar pantalla completa para apreciar mejor el juego");	
		mvprintw(5,0,"Realizado por: Antonio Maldonado Pinzon");
		mvprintw(6,0,"Presione cualquier tecla para iniciar el juego");	
	}
		
	//Patron inicial
	patron1(active,maxX,25,15);
	TIPO data;		//Declaro el tipo dato del nodo
	//Creo el nodo inicial
	Node *Inicio=CrearNode();//Creamos el primer nodo
   Node *ptr=Inicio;
	
	for(int t=0; t<iteraciones;t++){
      //ejecuta transicion
      CicloVida(active, inactive, maxX, maxY );
      
      //actualiza arreglo activo
      int* temp = inactive;
      inactive = active;
      active = temp;
      
      //despliega resultados
      for(int r=0;r<maxY;r++)
        for(int c=0;c<maxX;c++)
          if(active[r*maxX+c]){
     		    push(&data.x,c); push(&data.y,r);  
			}
		//Se le asigna un color a TIPO		
		data.color=col%8;
		col++;
		if(t==0)
			memcpy(&(Inicio->data), &data, sizeof(TIPO));
		else if (!insertNodoLista(ptr,data))
      	ptr=ptr->next;    //apunta al ultimo nodo
		else  
 			exit(EXIT_FAILURE);//termina con error
		clear(&data.x);
		clear(&data.y);	
  } 
	
	ptr=Inicio;
	int iter=1;
	while(ptr!=NULL&&(ch = getch())!=ESCAPE){
		erase();
		//pobacion;
		top=ptr->data.x.top;
		//despliega informacion para el usuario
 		mvprintw(0,0,"Poblacion = %d  Iteracion = %d  ESCAPE para salir",top+1,iter);
		//imprime la iteracion actual
		while(!pop(&ptr->data.x,&x)&&!pop(&ptr->data.y,&y))
 			mvprintw(y,x,"o");
	
		ptr->data.x.top=top;
		ptr->data.y.top=top;
		delay_output(0);

		//verifica la tecla presionada para avanzar o retroceder
   	switch(ch){
      	case KEY_UP:
         	if(ptr->next!=NULL){
           		ptr = ptr->next;
               iter++;                    
				}
  				attrset(COLOR_PAIR(ptr->data.color));
            break;
         case KEY_DOWN:
         	if(ptr->prev!=NULL){
            	ptr = ptr->prev;
               iter--;          
            }
   			attrset(COLOR_PAIR(ptr->data.color));
				break;
         default:
            break;
      }
	}
	//elimina nodos  
   cout<<endl<<"ciclo de eliminacion..."<<endl;
   ptr = Inicio;
   while(ptr->next!=NULL){
       TIPO d;
       if(eliminaNodoLista(ptr,&d))
         exit(EXIT_FAILURE);
   }
   endwin();
   //libera memoria
	cout<<"Elimina Node";
	EliminaNode(Inicio);       
	return EXIT_SUCCESS;
   //libera memoria
   delete [] active;
   delete [] inactive;
}

// *************************************************************
//    Funcion patrones iniciales de celulas
// *************************************************************
void patron1(int *array, int size, int c, int r){
  array[r*size+c] = array[r*size+(c+1)] = 
  array[(r+1)*size+(c-1)] = array[(r+1)*size+c] = 
  array[(r+2)*size+c] = 1;
}

void patron2(int *array, int size, int c, int r){
  array[r*size+c] = array[r*size+(c+4)] = array[r*size+(c+5)] = array[r*size+(c+6)] =
  array[(r+1)*size+c] = array[(r+1)*size+(c+1)] = array[(r+1)*size+(c+2)] = array[(r+1)*size+(c+5)] = 
  array[(r+2)*size+(c+1)] = 1;
}

void patron3(int *array, int size, int c, int r){
  array[(r+4)*size+c] = array[(r+5)*size+c] = 
  array[(r+4)*size+(c+1)] = array[(r+5)*size+(c+1)] = 
  array[(r+4)*size+(c+10)] = array[(r+5)*size+(c+10)] = array[(r+6)*size+(c+10)] =
  array[(r+3)*size+(c+11)] = array[(r+7)*size+(c+11)] =
  array[(r+2)*size+(c+12)] = array[(r+8)*size+(c+12)] =
  array[(r+2)*size+(c+13)] = array[(r+8)*size+(c+13)] =
  array[(r+5)*size+(c+14)] = 
  array[(r+3)*size+(c+15)] = array[(r+7)*size+(c+15)] =
  array[(r+4)*size+(c+16)] = array[(r+5)*size+(c+16)] = array[(r+6)*size+(c+16)] =
  array[(r+5)*size+(c+17)] = 
  array[(r+2)*size+(c+20)] = array[(r+3)*size+(c+20)] = array[(r+4)*size+(c+20)] =
  array[(r+2)*size+(c+21)] = array[(r+3)*size+(c+21)] = array[(r+4)*size+(c+21)] =
  array[(r+1)*size+(c+22)] = array[(r+5)*size+(c+22)] =
  array[r*size+(c+24)] = array[(r+1)*size+(c+24)] = array[(r+5)*size+(c+24)] = array[(r+6)*size+(c+24)] =
  array[(r+2)*size+(c+34)] = array[(r+3)*size+(c+34)] = 
  array[(r+2)*size+(c+35)] = array[(r+3)*size+(c+35)] =  1;
}
