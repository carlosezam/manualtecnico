/**
* Archivo Main
*
* Aqui se encuetran los detalles de implementación y la
* configuración del la interseccion: fases, carriles, etc.
**/

// C STanDar Input Output, contiene la definición de las
// funciones para mostrar y recibir datos por las entradas
// y salidas estandar. Es la versión heredada del lenguage C
// pero con seguridad de tipos.
#include <cstdio> 

// C Time, contiene funciones para realizar tomas de tiempo
// usada para relizar el Benchmark
#include <ctime>

// Vector, incluye la plantilla de clase Vector que permite
// usar vectores.
#include <vector>

// Declara que usará el vector del espacio de nombres estandar
using std::vector;


// Incluye la cabecera de FuzzySemaforo
#include "FuzzySemaforo.hpp"

// Incluye la cabeceta de SensorVehiculos
#include "SensorVehiculos.hpp"

// Incluye las funciones para graficar la interfaz de usuario
#include "semaforoUI.hpp"

/**
* Clase que simula el sensor de vehiculos
*
* Esta clase debe ser implementada adecuadamente para
* proporcionar al sistema el conteo de automoviles de la
* intersección. Sin embargo, para fines de prueba, se ha
* implementado de manera que le solicita al usuario que
* proporcione dichos números a través del teclado.
*/
class MySensor : public SensorVehiculos
{
public:

	/**
	* Constructor que solo toma el numero de camaras
	* i.e. el número de números que debe pedir
	*
	* @param int 	camaras número de camaras a simular
	*/
	MySensor(int camaras) : num_camaras(camaras)
	{
		// Constructor Vacio	
	}

	/**
	* Función que es llamada por el semaforo para conocer la
	* cantidad de autos en las avenidas de la intersección. Es
	* reponsabilidad del usuario final que se implemente
	* correctamente.
	*
	* @return	vector< double >
	*/
	virtual vector<double> read() const
	{
		// Crea el vector en el que se guardarán los números
		vector<double> conteo(num_camaras);

		system("cls");

		// Imprime el prompt para el usuario
		printf("\nIngresa los valores de prueba para las %d camaras, e.g. <2 8 8 10>\n>> ", num_camaras );

		// Semáforos en rojo mientras espera al usuario
		draw_semaforo(4,40, 'r' );
		draw_semaforo(19,80, 'r');
		draw_semaforo(34,40, 'r');
		draw_semaforo(19,1, 'r');
		
		// Itera el vector
		for( double &num : conteo )
		{
			// Pide al usuario los números
			scanf("%lf", &num );
		}
		
		// devuelve al semáforo el vector con los números
		return conteo;
	}

private:
	int num_camaras; //! guarda el número de camaras

};



/**
* Clase que simula el semaforo
*
* Los detalles de implementación de esta clase también dependen del usuario
* final. Al delegar a esta clase los detalles, se permite que el usuario
* implemente el algoritmo en un arduino usando las funciones disponibles como:
* DigitalWrite y AnalogWrite; en una Raspberry mediante los puertos GPIO ó
* en algun PIC.
*
*/
class MySemaforo : public FuzzySemaforo
{
public:

	/**
	* Constructor de la clase
	*
	* Se encarga de incializr la clase base FuzzySemaforo mediante
	* la sintaxis de inicialización de miembros. Los datos requeridos son:
	* la configuración del ciclo, el conteo de los carriles por avenida y,
	* una referencia al sensor de vehiculos.
	*
	* @param vector<vector<int>> ciclo Configuración del ciclo del semáforo
	* @param vector<int>         carriles Número de carriles por avenida 
	* @param SensorVehiculos     &sensor  Referencia al sensor de vehículos
	*/
	MySemaforo(
		vector< vector<int>> ciclo,
		vector<int> carriles,
		SensorVehiculos &sensor
	) : FuzzySemaforo( ciclo, carriles, sensor ), ciclo_semaforo(ciclo)
	{
		// Establece el tamaño de la consolas a
		// 46 filas y 86 columnas
		console_size(46,86);
	}

	// Función encargada de realizar las acciones pertinentes para
	// realizar el cambio de fase, e.g Realizar la secuencia de fases:
	// 1 Amarillo, 2 Todo rojo, 3 Poner en verde los semáforos de la
	// fase indicada, 4 Esperar el tiempo indicado.
	//
	// Los detalles del como se implementa, e.g. mediante sonidos, leds,
	// pantallas, etc... depeden del usuario. Para fines de prueba
	// se ha optado por imprimir el tiempo inferido
	virtual void set_lights( int fase, double tiempo )
	{
		// Imprime la información
		printf("El tiempo inferido para la fase %d es de %02.02f segundos", fase, tiempo);
		vector<int> config_fase = ciclo_semaforo[ fase ];

		// Inicia la fase verde
		draw_semaforo(4,40, (config_fase[0] == VERDE ? 'v' : 'r' ) );
		draw_semaforo(19,80, (config_fase[1] == VERDE ? 'v' : 'r' ));
		draw_semaforo(34,40, (config_fase[2] == VERDE ? 'v' : 'r' ));
		draw_semaforo(19,1, (config_fase[3] == VERDE ? 'v' : 'r' ));

		// Espera el tiempo inferido por el sistema, para fines
		// de prueba, el tiempo es reducido a la mitad
		Sleep(tiempo * 100 );

		// Inicia el parpadeo de la fase amarilla
		for( int i = 0; i < 3; i++ )
		{
			draw_semaforo(4,40, (config_fase[0] == VERDE ? 'a' : 'r' ) );
			draw_semaforo(19,80, (config_fase[1] == VERDE ? 'a' : 'r' ));
			draw_semaforo(34,40, (config_fase[2] == VERDE ? 'a' : 'r' ));
			draw_semaforo(19,1, (config_fase[3] == VERDE ? 'a' : 'r' ));
			Sleep(500);
			draw_semaforo(4,40, (config_fase[0] == VERDE ? 'n' : 'r' ) );
			draw_semaforo(19,80, (config_fase[1] == VERDE ? 'n' : 'r' ));
			draw_semaforo(34,40, (config_fase[2] == VERDE ? 'n' : 'r' ));
			draw_semaforo(19,1, (config_fase[3] == VERDE ? 'n' : 'r' ));
			Sleep(500);
		}

		// Fase todo rojo
		draw_semaforo(4,40, 'r' );
		draw_semaforo(19,80, 'r');
		draw_semaforo(34,40, 'r');
		draw_semaforo(19,1, 'r');
		Sleep(500);
	}

};


/**
* Punto de entrada al programa
*/
int main(int argc, char const *argv[])
{
	// Instancia un sensor que simula 4 camaras
	// 1 para cada avenida
	MySensor mySensor(2);

	// Declara la cantidad de carriles por avenida
	// i.e. av 1 = 3 carriles, av 2 = 2 carriles 
	Carril carriles_avenidas = { 1, 1 };

	// Declara la configuración del ciclo del semáforo
	/*Ciclo ciclo_semaforo = {
		// fase 1: avenida 1 en verde, el resto en rojo
		{ VERDE, ROJO, ROJO, ROJO  },

		// fase 2: avenida 2 en verde, el resto en rojo 
		{  ROJO, VERDE, ROJO, ROJO },

		// fase 3: avenida 3 en verde, el resto en rojo
		{  ROJO, ROJO, VERDE, ROJO },

		// fase 4: avenida 4 en verde, el resto en rojo
		{  ROJO, ROJO, ROJO, VERDE }
	};*/ Ciclo ciclo_semaforo = { {VERDE,ROJO},{ROJO,VERDE} };

	// Inicializa el semaforo con la configuración previamente
	// hecha.
	MySemaforo mySemaforo( ciclo_semaforo, carriles_avenidas, mySensor );

	// Inicia el bucle de cotrol
	mySemaforo.run();

	return 0;
}