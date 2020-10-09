#include <iostream>
using namespace std;

class Pila{
	private:
		int* items;
		int tope;
		int cant;
	
	public:
		Pila(int xcant=0){
			cant = xcant;
			tope = -1;
			items= new int[cant];
		}
		int vacia(){
			return (tope == -1);
		}
		int insertar (int x){
			if(tope < cant-1){
				items[++tope]=x;
				return(x);
			}
			else{
				cout << "Pila llena" << endl;
				return (0);
			}		
		}
		int suprimir(){
			int x;
			if (vacia()){
				cout << "Pila vacia" << endl;
				return(0);
			}
			else{
				x=items[tope--];
				return(x);
			}
		}
		void mostrar(){
			int i;
			if(!vacia()){
				for(i=tope;i>=0;i--){
					cout<<items[i]<<endl;
				}
			}
		}
};

int main(){
	Pila P;
	P = Pila(5);
	cout << "Pila: " << P.vacia() << endl;
	P.insertar(1);
	P.insertar(2);
	cout << "------1" << endl;
	P.mostrar();
	cout << "------2" << endl;
	P.insertar(3);
	P.insertar(4);
	P.insertar(5);
	cout << "------3" << endl;
	P.insertar(6);
	cout << "------4" << endl;
	P.mostrar();
	P.suprimir();
	cout << "------" << endl;
	P.mostrar();
}
