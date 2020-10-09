#include <iostream>
using namespace std;

class Cola{
	private:
		int *items;
		int max;
		int pr;
		int ul;
		int cant;
		
	public:
		Cola (int xmax=0){
			max = xmax;
			pr = 0;
			ul = 0;
			cant = 0;
			items = new int[max];
		}
		
		int vacia(){
			return (cant==0);
		}	
		
		int insertar(int x){
			if (cant < max){
				items[ul] = x;
				ul = (ul + 1)%max;
				cant++;
				return (x);
			}
			else{
				return (0);
			}
		}
		
		int suprimir (){
			int x;
			if(vacia()){
				cout << "Pila vacia" << endl;
				return 0;
			}
			else{
				x = items[pr];
				pr = (pr + 1)%max;
				cant--;
				return(x); 
			}
		}
		
		void recorrer(){
			int i, j;
			if(!vacia()){
				for (i = pr, j = 0;j < cant; i = (i+1)%max, j++){
					cout << items[i] << endl;
				}
			}
		}
};

int main(){
	Cola C;
	C= Cola(5);
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
}
