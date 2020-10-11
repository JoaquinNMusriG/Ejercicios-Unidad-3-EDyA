#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

class celda
{
	int item;
	celda *sig;
	
	public:
		int obteneritem(void)
		{
			return(item);
		}
		
		void cargaritem(int xitem)
		{
			item=xitem;
		}
		
		void cargarsig(celda* xtope)
		{
			sig=xtope;
		}
		
		celda* obtenersig(void)
		{
			return(sig);
		}
};

class pila
{
	int cant;
	celda *tope;
	
	public:
		pila(celda* xtope=NULL,int xcant=0) //constructor
		{
			//tope(xtope),cant(xcant);
			tope=xtope;
			cant=xcant;			
		}
		
		int vacia(void)
		{
			return (cant==0);
		}
		
		int insertar(int x)
		{
			celda *ps1= new celda;
			//ps1=new(celda);
			ps1->cargaritem(x);
			ps1->cargarsig(tope);
			tope=ps1;
			cant++;
			return(ps1->obteneritem());
		}
		
		int suprimir(void)
		{
			celda *aux;
			int x;
			if (vacia())
			{
				printf("%s","Pila vacia");
				return(0);
			}
			else
			{
				aux=tope;
				x=tope->obteneritem();
				tope=tope->obtenersig();
				cant--;
				free(aux);
				return(x);
			}
		}
		
		void mostrar(void)
		{
			celda *aux = tope;
			while(aux!=NULL)
			{
				cout<< aux->obteneritem() << " ";
				aux=aux->obtenersig();
			}
		}
};

//ALGORITMO PRINCIPAL
main ()
{
	pila pi;
	int dec,i=0;
	printf ("Ingrese el numero entero en formato decimal\n");
	fflush(stdin);
	scanf("%d", &dec);
	while(pow(2,i+1)<=dec)
	{
		i++;
	}
	while(i>=0)
	{
		if (dec%2 == 1)
		{
			pi.insertar(1);
			dec=dec/2;
			i--;
		}
		else
		{
			pi.insertar(0);
			dec=dec/2;
			i--;
		}
	}
	printf("La representacion binaria es: ");
	pi.mostrar();		
};
