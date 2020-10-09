#include <iostream>
#include <stdlib.h>
#include <time.h>
#define T_SIMULACION 10 
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
};

int llegadaCliente(float xFrecuencia){
	int rta;
	rta= rand()%101;
	cout << rta << endl;
	return (rta <= ((1/xFrecuencia)*100));
}

int main(){
	int Reloj, Tiempo_atencion, Cajero, Tiempo_Maximo, Tiempo_Espera_Cliente;
	float Frecuencia_llegada;
	Cola clientes;
	clientes = Cola();
	Reloj = 0;
	Cajero = 0;
	Tiempo_Maximo = 0;
	srand(time(NULL));
	cout << "Ingrese el tiempo de atencion del cajero: ";
	cin >> Tiempo_atencion;
	cout << "Ingrese la frecuencia de llegada de los clientes: ";
	cin >> Frecuencia_llegada;
	while (Reloj < T_SIMULACION){
		if (llegadaCliente(Frecuencia_llegada)){
			clientes.insertar(Reloj);
		}
		if (Cajero == 0){
			if (!clientes.vacia()){
				Tiempo_Espera_Cliente = Reloj - clientes.suprimir();
				cout << "-----Tiempo espera cliente: " << Tiempo_Espera_Cliente << "-------- Reloj: " << Reloj << endl;
				if (Tiempo_Espera_Cliente > Tiempo_Maximo){
					Tiempo_Maximo = Tiempo_Espera_Cliente;
				}
				Cajero = Tiempo_atencion;
			}
		}
		Reloj++; //Pasa 1 minuto
		if (Cajero > 0){
			Cajero--;
		}
	}
	cout << "El tiempo maximo de espera de un cliente en la simulacion es : " << Tiempo_Maximo << endl;
}




