/**
* @file		FuzzySemaforo.hpp
* @author	Carlos Ezam
* @date		28/06/2018
* @version 	0.1
*
* @brief FuzzySemaforo
*
* @section Descripción
*
* La clase FuzzySemaforo se encarga de integrar la inferencia
* difusa con el algoritmo de sincronización de semáforos. En otras
* palabras, se encarga de conectar todas las piezas: Sensor,
* Semaforo y Sistema de inferencia. Además delega los detalles de
* implementación final mediante la función set_lights().
*/

#ifndef FUZZY_SEMAFORO
#define FUZZY_SEMAFORO

#include <ctime>
#include "SensorVehiculos.hpp"

// Defie la constante simbólica VERDE como 1
#define VERDE 1

// Defie la constante simbólica ROJO como 0
#define ROJO 0

// Define el alias Ciclo como un vector de vectores de tipo int
using Ciclo = vector< vector <int> >;

// Define el alias Carril como un vector de tipo int
using Carril = vector <int>;

/*
* Clase FuzzySemaforo
*
* Implementa el algoritmo de sincronización de semaforos dejando
* los detalles de implementacion del sensor y de los semáforos al
* usuario final
*/
class FuzzySemaforo{
public:

	// Constructor principal
	FuzzySemaforo( Ciclo _ciclo, Carril _carriles, SensorVehiculos &_sensor );

	// Función virtual que a la que se le delega el cambio de fase
	virtual void set_lights(int, double) = 0;

	// Echa a andar el bucle permanente que controlará los semáforos.
	void run();
	
private:
	
	/**
	* Calcula el tiempo en verde.
	*
	* Esta función es una parte funamental de todo el sistema, es aqui
	* donde se encuentra el Sistema de Inferencia Difusa.
	*/
	double get_time( int, int );

	// Calcula la media ponderada de los autos por carril
	double get_media( int, int);

	// Número de fases del ciclo
	int num_fases;

	// Número de carriles de la interseccón
	int num_carriles;

	// Número de avenidas de la interseción
	int num_avenidas;
	
	// Fase actual
	int fase;

	// Tiempo asignado a la fase actual
	double tiempo;

	// Media ponderada Vehiculos
	double vehiculos;

	// Media ponderada Congestión
	double congestion;
	
	// Referencia al sensor de vehiculos
	SensorVehiculos &sensor;

	// Fases del ciclo
	vector< vector<int>> ciclo;

	// Carriles por avenida de la intersección
	vector<int> carriles;

	// Autos por avenida de la intersección
	vector<double> autos;

	// Pesos de ponderación por avenida
	vector<double> pesos;
};

#endif