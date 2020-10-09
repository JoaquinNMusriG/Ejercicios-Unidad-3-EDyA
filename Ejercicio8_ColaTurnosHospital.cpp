#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#define T_SIMULACION  240 
using namespace std;

class Nodo{
	private:
		int item; //Valor del reloj para pacientes
		int espec; //Valor de la especialidad del paciente que pidio el turno; para colas de espera de medicos no es nada
		Nodo* sig;
		
	public:  
            
        int GetItem(){
        	return item;
		}        

        void SetItem(int xitem, int xespe){
        	item = xitem;
        	espec = xespe;
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
		
		int insertar(int x, int xespe){
			Nodo* nuevo;
			nuevo = new (Nodo);
			nuevo->SetItem(x, xespe);
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
		
		void recorrer (){  //ELIMINAR DSP
			Nodo* aux;
			aux = pr;
			while (aux != NULL){
				cout << aux->GetItem() << endl;
				aux = aux->GetSig();
			}
		}
};

int llegadaCliente(float xFrecuencia){
	int rta;
	rta= rand()%101;  //in + rand()%(fin+1-in) rta aleatoreas
	return (rta <= ((1/xFrecuencia)*100));
}

int main(){ //Suponer simulacion de 7 a 11 am y que hay 1 medico por especialidad
	int Reloj, Mesa_Entrada, cant_turnos[4], medico[4], Sin_Turno, especialidad, i;
	int Tiempo_Espera_Turno;                             //variables cola de turnos
	float Tiempo_Acumulado_Turno, Cant_Pac_Atendidos_Mesa;
	int Tiempo_Espera_Atendido;                         //variables cola de atendidos
	float Tiempo_Acumulado_Atendido[4], Cant_Pac_Atendidos_Medico[4];
	int band_turno_dado, band_termino_hora;
	float Frecuencia_paciente;
	string nomb, dni;
	Cola cola_Turnos, cola_atendidos[4];
	cola_Turnos = Cola();
	for (i = 0;i<4;i++){
		cola_atendidos[i] = Cola();
		cant_turnos[i] = 0; //cerear contidad de turnos por especialidad 
		medico[i] = 0;       //tiempo de atencion 20 min; arreglo de contadores para calcular tiempo mientras son atendidos los pacientes por los medicos
		Tiempo_Acumulado_Atendido[i] = 0;  //para calcular promedio de cola atendidos
		Cant_Pac_Atendidos_Medico[i] = 0;
	}
	Reloj = 0;
	Mesa_Entrada = 0; //tiempo de atencion 2 min; contador para calcular tiempo de atencion al paciente en mesa de entrada
	Sin_Turno = 0;    //contador de los que no consiguen turno
	Tiempo_Acumulado_Turno = 0;   //para calcular promedio de cola turno
	Cant_Pac_Atendidos_Mesa = 0;
	band_turno_dado = 0;
	band_termino_hora = 0;
	Frecuencia_paciente = 1;
	srand(time(NULL));
	while (Reloj < T_SIMULACION){
		
		if (Reloj < 60){   //Solo se reciben turnos la primera hora 
			if (llegadaCliente(Frecuencia_paciente)){ //frecuencia de clientes que llega al hospital es 1 por min
				/*
				cout << "Ingrese la especialidad en la que quiere ser atendido(1:Ginecologia, 2:Clinica medica, 3:Oftalmologia, 4:Pediatria): ";
				cin >> especialidad;
				*/
				especialidad = 1 + rand()%(4+1-1); //especialidades aleatoreas
				if (cant_turnos[especialidad-1] < 10){ //solo hay 10 turnos por especialidad
					band_turno_dado = 1;
					cant_turnos[especialidad-1]++;
					cola_Turnos.insertar(Reloj, especialidad-1);
					/*
					cout << "Ingrese el nombre del paciente: ";   //Datos que no utilizo pero aumenta la realidad del problema
					cin >> nomb;
					cout << "Ingrese el dni del paciente: ";
					cin >> dni;
					//Indicar consultorio en el que sera atendido*/
				}
				else{
					Sin_Turno++; //Cantidad de pacientes que no pudieron reservar turno
				}
			}
			if (Mesa_Entrada == 0){
				if (!cola_Turnos.vacia()){
					Tiempo_Espera_Turno = Reloj - cola_Turnos.suprimir(); //tiempo esperado por el primer paciente en la cola de espera
					Tiempo_Acumulado_Turno = Tiempo_Acumulado_Turno + Tiempo_Espera_Turno; //total de tiempo esperado por los pacientes para pedir turno
					Cant_Pac_Atendidos_Mesa++;   //total de pacientes que pasaron a reservar su turno
					Mesa_Entrada = 2; //atendiendo paciente
				}
			}
		}
		else{
			band_termino_hora = 1;
			band_turno_dado = 0;
		}
		
		if(band_turno_dado){     //Pacientes atendidos en la primera HORA
			cola_atendidos[especialidad-1].insertar(Reloj, 0); //ingresa pacientes a la cola para ser atendidos por el medico de su especialidad
			if (medico[especialidad-1] == 0){
				if(!cola_atendidos[especialidad-1].vacia()){
					Tiempo_Espera_Atendido = Reloj - cola_atendidos[especialidad-1].suprimir();
					Tiempo_Acumulado_Atendido[especialidad-1] = Tiempo_Acumulado_Atendido[especialidad-1] + Tiempo_Espera_Atendido;
					Cant_Pac_Atendidos_Medico[especialidad-1]++;
					medico[especialidad-1] = 20; //atendiendo paciente
				}
			}
		}
		
		if (band_termino_hora){  //Pacientes atendidos las restantes 3 horas
			for (i=0;i<4;i++){
				if (medico[i] == 0){
					if (!cola_atendidos[i].vacia()){
						Tiempo_Espera_Atendido = Reloj - cola_atendidos[i].suprimir();
						//cout << "------Tiempo espera del turno actual: " << Tiempo_Espera_Atendido << endl; tiempos de espera
						Tiempo_Acumulado_Atendido[i] = Tiempo_Acumulado_Atendido[i] + Tiempo_Espera_Atendido;
						Cant_Pac_Atendidos_Medico[i]++;
						medico[i] = 20; //atendiendo paciente
					}
				}
			}	
		}
		
		Reloj++; //Pasa 1 minuto
		if (Mesa_Entrada > 0){
			Mesa_Entrada--;
		}
		for(i=0;i<4;i++){
			if(medico[i] > 0){
				medico[i]--;
			}
		}
	}
	cout << "El tiempo promedio de cola de espera para turnos es de : " << Tiempo_Acumulado_Turno/Cant_Pac_Atendidos_Mesa << " minutos" << endl;
	cout << "1:Ginecologia, 2:Clinica medica, 3:Oftalmologia, 4:Pediatria" << endl;
	for (i=0;i<4;i++){
		if (Cant_Pac_Atendidos_Medico[i] != 0){
			cout << "El tiempo promedio de cola de espera para la especialidad " << i+1 <<" es de : " << Tiempo_Acumulado_Atendido[i]/Cant_Pac_Atendidos_Medico[i] << " minutos" << endl;
		}
		else{
			cout << "El tiempo promedio de cola de espera para la especialidad " << i+1 <<" es de : " << 0 << " minutos" << endl;
		}
	}
	cout << "La cantidad de pacientes que no obtuvieron turno son: " << Sin_Turno << endl;
}
