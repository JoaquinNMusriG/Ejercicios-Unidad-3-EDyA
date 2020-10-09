#include <iostream>
#include <math.h>
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
		int mostrar_top(){
			return items[tope];
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

int main() {
//aqui declaramos las variables y pilas a utilizar
	int pilaDestino, pilaOrigen;
	Pila torre[3]; //declaramos las 3 torres 
	int Cant_mov, Cant_discos, Band, i, Disco;
	cout << "Ingrese la cantidad de discos con los que va a jugar: ";
	cin >> Cant_discos;
	for  (i=0;i<3;i++){
		torre[i] = Pila(Cant_discos);
	}
	for (i=0;i<Cant_discos;i++){
		torre[0].insertar(Cant_discos - i);
	}
	for  (i=0;i<3;i++){                  //estado inicial
		cout << "Torre: " << i+1 << endl;
		torre[i].mostrar();
		cout << "-------" << endl;
	}
	Cant_mov = 0;
	Band = 1;
	while( Band ) {
		cout << "Mover desde la pila (1 a 3): ";
		cin >> pilaOrigen;
		cout << "Hacia la pila (1 a 3): ";
		cin >> pilaDestino;
		pilaOrigen -= 1;
		pilaDestino -=1;
/* restricciones cuando se hagan los movimientos */
		if((pilaOrigen < 0 || pilaOrigen > 2 ) || (pilaDestino < 0 || pilaDestino > 2) || pilaOrigen == pilaDestino || torre[pilaOrigen].vacia()){
			cout << "Movimiento invalido. "; 
		}
		else{
			if (torre[pilaDestino].vacia() || (torre[pilaDestino].mostrar_top() > torre[pilaOrigen].mostrar_top())) {
				Disco = torre[pilaOrigen].suprimir();
				torre[pilaDestino].insertar(Disco);
				cout << "Movimiento correcto. " << endl;
			} 
			else{
				cout << "Movimiento incorrecto. " << endl;
			}
		}
	
		Cant_mov++; //contador de movimientos
		cout << "Los movimientos que vas realizando son: " << Cant_mov << endl;
		
		for  (i=0;i<3;i++){                  //estado actual
			cout << "Torre: " << i+1 << endl;
			torre[i].mostrar();
			cout << "-------" << endl;	
		}
		
		if (torre[0].vacia() && torre[1].vacia()){
			Band = 0;
		}
	}
	cout << "El numero de movimientos que realizo es de: " << Cant_mov << endl;
	cout << "El numero minimo de jugadas para este juego es de: " << pow(2,Cant_discos)-1 << endl;
}
