#include <iostream>
using namespace std;

class Pila{
	private:
		int* items;
		int tope1, tope2;
		int cant;
	
	public:
		Pila(int xcant=0){
			cant = xcant;
			tope1 = -1;
			tope2 = xcant;
			items= new int[cant];
		}
		int vacia(){
			return (tope1 == -1) && (tope2 == cant);
		}
		int insertar (int x, int xtope){
			if (xtope == 1){
				if(tope1 < tope2-1){
					items[++tope1]=x;
					return(x);
				}
				else{
					cout << "Pila llena" << endl;
					return (0);
				}
			}
			else{
				if(tope2 > tope1+1){
					items[--tope2]=x;
					return(x);
				}
				else{
					cout << "Pila llena" << endl;
					return (0);
				}
			}		
		}
		int suprimir(int xtope){
			int x;
			if (vacia()){
				cout << "Pila vacia" << endl;
				return(0);
			}
			else{
				if (xtope == 1){
					x=items[tope1--];
					return(x);
				}
				else{
					x = items[tope2++];
					return x;
				}
			}
		}
		void mostrar(){
			int i;
			if(!vacia()){
				for(i=tope1;i>=0;i--){
					cout<<items[i]<<endl;
				}
				cout << "------_----------------" << endl;
				for(i=tope2;i<cant;i++){
					cout<<items[i]<<endl;
				}
				cout << "------_----------------" << endl;
			}
		}
};

int main(){
	Pila P;
	P = Pila(5);
	cout << "Pila: " << P.vacia() << endl;
	P.insertar(1,1);
	P.insertar(1,2);
	cout << "------1" << endl;
	P.mostrar();
	cout << "------2" << endl;
	P.insertar(2,1);
	P.insertar(3,1);
	P.insertar(4,1);
	cout << "------3" << endl;
	P.insertar(6,1);
	cout << "------4" << endl;
	P.insertar(2,2);
	cout << "------5" << endl;
	P.mostrar();
	P.suprimir(1);
	cout << "------6" << endl;
	P.mostrar();
	P.insertar(2,2);
	cout << "------7" << endl;
	P.mostrar();
}
