#include <iostream>
#include <stdlib.h>
using namespace std;

class Nodo{
	private:
		int item;
		Nodo* sig;
		
	public:  
            
        int GetItem(){
        	return item;
		}        

        void SetItem(int xitem){
        	item = xitem;
		}           

        Nodo* GetSig (){
        	return sig;
		}

        void SetSig(Nodo* xsig){
            sig = xsig;
        }     	
};

class Pila{
	private:
		Nodo* tope;
	
	public:
		Pila(Nodo* xtope=NULL){
			tope = xtope;
		}	
		int vacia(){
			return (tope == NULL);
		}	
			
		int insertar (int xnuevo){
			Nodo* nuevo;
			nuevo = new (Nodo);
			nuevo->SetItem(xnuevo);
			nuevo->SetSig(tope);
			tope = nuevo;
			return nuevo->GetItem();
		}
		int suprimir (){
			Nodo* aux;
			int x;
			if(vacia()){
				cout << "Pila vacia" << endl;
				return 0;
			}
			else{
				aux = tope;
				x = tope->GetItem();
				tope = tope->GetSig();
				free(aux);
				return(x);
			}
		}	
		void mostrar (){
			Nodo* aux;
			aux = tope; 
			if(!vacia()){
				while (aux != NULL){
					cout << aux->GetItem() << endl;
					aux = aux->GetSig();
				}
			}
		}
};

int main(){
	Pila P;
	P = Pila(NULL);
	cout << "Pila vacia: " << P.vacia() << endl;
	P.insertar(1);
	cout << "------" << endl;
	P.mostrar(); 
	P.insertar(2);
	P.insertar(3);
	P.insertar(4);
	P.insertar(5);
	P.insertar(6);
	cout << "------" << endl;
	P.mostrar();
	cout << "------" << endl;
	P.suprimir();
	P.mostrar();
}
