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

class Cola{
	private:
		Nodo* pr;
		Nodo* ul;
	public:
		Cola(){
			pr = NULL;
			ul = NULL;
		}	
		
		int vacia(){
			return ((ul == NULL)&&(pr == NULL));
		}
		
		int insertar(int x){
			Nodo* nuevo;
			nuevo = new (Nodo);
			nuevo->SetItem(x);
			nuevo->SetSig(NULL);
			if (ul == NULL){
				pr = nuevo;
			}
			else{
				ul->SetSig(nuevo);
			}
			ul = nuevo;
			return (ul->GetItem());
		}
		
		int suprimir(){
			Nodo* aux;
			int x;
			if(vacia()){
				cout << "Cola vacia" << endl;
				return 0;
			}
			else{
				aux = pr;
				x = pr->GetItem();
				pr = pr->GetSig();
				if (pr == NULL){
					ul = NULL;
				}
				free(aux);
				return (x);
			}
		}
		
		void recorrer (){
			Nodo* aux;
			aux = pr;
			while (aux != NULL){
				cout << aux->GetItem() << endl;
				aux = aux->GetSig();
			}
		}
};

int main(){
	Cola C;
	C = Cola();
	cout << C.vacia() << endl;
	C.insertar(1);
	C.insertar(2);
	cout << "----------------" << endl;
	C.recorrer();
	cout << "----------------" << endl;
	C.insertar(3);
	C.insertar(4);
	C.insertar(5);
	C.insertar(6);
	cout << "----------------" << endl;
	C.recorrer();
	cout << "----------------" << endl;
	C.suprimir();
	cout << "----------------" << endl;
	C.recorrer();
	cout << "----------------" << endl;
	cout << C.vacia() << endl;
}
