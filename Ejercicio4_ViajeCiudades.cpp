#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef char Provincia[30];

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
				//printf("%s","Pila vacia");
				return(-1);
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
	Provincia origen,destino,ciudad;
	int MAT[8][8];
	int i,j,v;
	int indO=0,indC=0;
	Provincia PR[8];
	int llego=0,enc=0,enc2=0;
	pila Vuelta,Ida;
	
	strcpy(PR[0], "Cordoba");
	strcpy(PR[1], "Villa Maria");
	strcpy(PR[2], "Rosario");
	strcpy(PR[3], "San Luis");
	strcpy(PR[4], "Mendoza");
	strcpy(PR[5], "Bahia Blanca");
	strcpy(PR[6], "Buenos Aires");
	strcpy(PR[7], "San Pedro");
	
	for(i=0;i<8;i++){
		cout<<PR[i]<<"\n";
	}
	

	printf ("Ingrese la ciudad Origen: \n");
	fflush(stdin);
	gets(origen);
	printf ("Ingrese la ciudad Destino: \n");
	fflush(stdin);
	gets(destino);
	printf ("Ingrese la ciudad a visitar: \n");
	fflush(stdin);
	gets(ciudad);
	
	while((indO<8)&&(!enc)){
		if(strcmp(origen,PR[indO])==0){
			enc=1;
		}
		else{
			indO++;
		}
	}
	Vuelta.insertar(indO);
	
	for(i=0;i<8;i++){	
		for(j=0;j<8;j++){
			MAT[i][j]=0;
		}
	}
	MAT[0][1]=MAT[1][0]=MAT[1][2]=MAT[1][3]=MAT[2][1]=MAT[2][7]=MAT[3][1]=MAT[3][4]=MAT[3][5]=MAT[3][6]=MAT[4][3]=MAT[5][3]=MAT[5][6]=MAT[6][5]=MAT[6][7]=MAT[7][2]=MAT[7][6]=1;
	//cout<<"Matriz:\n";
	//for(i=0;i<8;i++){	
	//	for(j=0;j<8;j++){
	//		cout<<MAT[i][j];
	//	}
	//	cout<<"\n";
	//}
	while (!llego){
		while((indC<8)&&(!enc2)){
			//cout<<PR[indC];
			//cout<<ciudad<<"\n";
			if(strcmp(ciudad,PR[indC])==0){
				enc2=1;
			}
			else{
				indC++;
			}
		}
		if (enc2){
			//cout<<"indices "<<indO<<indC<<"\n";
			//cout<<"MATRIZ:"<<MAT[indO][indC]<<"\n";
			if (MAT[indO][indC]==1){
				Vuelta.insertar(indC);
				indO=indC;
				if (strcmp(ciudad,destino)==0){
					llego=1;
				}
			}
			else{
				cout<<"No puede viajar a la ciudad indicada\n";
			}
			if (!llego){
				printf ("Ingrese la siguiente ciudad a visitar: \n");
				fflush(stdin);
				gets(ciudad);
				enc2=0;
				indC=0;
			}
		}
		else{
			cout<<"ERROR DE DESBORDE";
			llego=1;
		}

	}	
	cout<<"\n--------------------------\n";
	cout<<"El Camino de vuelta es:\n";
	v=Vuelta.suprimir();
	while(v!=-1){
		cout<<PR[v]<<" - ";
		Ida.insertar(v);
		v=Vuelta.suprimir();		
	}
	cout<<"\n--------------------------\n";
	cout<<"El Camino de ida fue:\n";
	v=Ida.suprimir();
	while(v!=-1){
		cout<<PR[v]<<" - ";
		v=Ida.suprimir();		
	}
	
};
