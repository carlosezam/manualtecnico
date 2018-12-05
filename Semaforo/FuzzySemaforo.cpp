#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

#include "FuzzySemaforo.hpp"
#include "FuzzySet.hpp"
#include "FuzzyValue.hpp"
#include "MembershipFunction.hpp"

/**
* Constructor de la clase
*
* Para crear un objeto de la clase es necesario proporcionar la 
* confiuración de las fases del ciclo, la cantidad de carriles por avenida
* y una referencia al sensor de vehiculos.
*
* @param	vector< vector< int > >		_ciclo		matriz de enteros donde 
* 1 es verde y 0 es rojo, además, cada fila es una fase y cada columna un
* semáforo. e.g. una intersección de dos avenidas y dos fases:
* ciclo = {
*	{ VERDE, ROJO }, // fase 1, verde en la avenida 1, rojo en la 2
*	{ ROJO, VERDE }	// fase 2, verde en la avenida 2, rojo en la 1
* }
*
* @param	vector< int >				_carriles	vector con el número de
* carriles por avenida. e.g. carriles = { 2, 3 }
*
* @param	SensorVehiculos&			_sensor		referencia al sensor
*/
FuzzySemaforo::FuzzySemaforo
(
	vector< vector< int > > _ciclo,
	vector< int >			_carriles,
	SensorVehiculos&		_sensor
)
: ciclo(_ciclo), carriles(_carriles), sensor(_sensor)
{
	// Inicializa el numero de avenidas de la interseciión
	num_avenidas 	= carriles.size();

	// Inicializa el numero de fases del semaforo
	num_fases 		= ciclo.size();

	// Iniciliza la suma de carriles en 0
	num_carriles 	= 0;

	// Establece la fase inicial del semaforo
	fase			= 0;

	// Crea el vector de pesos para ponderar más adelante
	// la cantidad de carros por avenida
	pesos = vector<double>( num_avenidas );

	// Calcula el total de carriles de la intersección
	for( int n : carriles )
	{
		num_carriles += n;
	}

	// Calcula el valor de ponderación para cada avenida como un cociente
	// de el número de carriles por avenida sobre el total de carriles de
	// la intersección 
	for( int n = 0; n <  carriles.size(); ++n)
	{
		pesos[ n ] = (static_cast<double>(carriles[n]) / (num_carriles));
	}

}

/**
* Inicia el bucle permanente
*
* Mantiene un buccle perpetuo donde se encunetra el algoritmo de
* sincronización de semáforos
*/
void FuzzySemaforo::run()
{
	/**
		// Variables usadas para medir el tiempo de ejecución
		// Descomentar en caso de requerirse.
	
	double    time = 0;
	unsigned long  tick = 0;
	unsigned long tock = 0; */
	
	// Buccle permanente
	while( true ) {

		// obtiene la catidad de autos en cada avenida
		autos = sensor.read();

		/**
			// toma de tiempo inicial
			// Descomentar en caso de requerirse.

  		tick = clock(); */

		// calcula la media ponderada de los vehiculos en las avenidas que pasaran a verde
		vehiculos 	= get_media( fase, 1 );

		// calcula la media ponderada de la congestion, esto es la cantidad de autos en las avenidas que quedaran en rojo
		congestion 	= get_media( fase, 0 );
		
		// Infiere el tiempo en verde a asignar mediante Logiga Difusa
		tiempo = get_time( vehiculos, congestion );

		/**
			// toma de tiempo inicial
			// Descomentar en caso de requerirse.

  		tock = clock(); */

		// Estable el cambio de fase
		set_lights( fase, tiempo );

		// Siguiente fase
		fase = (fase + 1) % num_fases;

		/* 
		   // Calculo e impresión del tiempo de ejecución.
		   // Descomentar en caso de requerirse.

  		time = ((double)(tock-tick)/CLOCKS_PER_SEC);
  		printf("tiempo de ejecución: %f\n", tock-tick);*/
	}
}

/**
* Calcula la suma ponderada de los vehiculos en las avenidas
*
* Mediante la fase actual (fase) y el paso: verde o rojo, determina
* la media de ponderada de vehiculos o congestión, respectivamente.
*
* @param	int		fase 	la fase del ciclo a evaluar
* @param	int 	estado	ROJO o VERDE
* @return	double
*/
double FuzzySemaforo::get_media( int fase, int estado )
{
	// inicialización de variables
	double x = 0;	//! autos por carril
	double xy = 0;	//! sumatoria de de x ponderada
	double y = 0;	//! sumatoria de los pesos

	// Itera todas las avenidas
	for( int n = 0; n < num_avenidas; ++n )
	{
		// Si estado es igual a 1 (verde) analiza solo las avenidas que
		// tendrán fase verde en la fase actual. Si es 0 (rojo) analiza
		// las que tendrán fase roja en la fase actual.
		if( ciclo[ fase ][ n ] == estado )
		{	
			// Calcula autos por carril
			x = autos[n] / carriles[n];

			// Suma X ponderada por el peso
			xy += x * pesos[n] ;
			
			// Suma los pesos
			y += pesos[n];
		}
	}

	// retorna la suma ponderada
	return xy / y;
}

/**
* Usa lógica difusa para inferir la duración de la fase
*
* Calcula el tiempo de duración de la fase mediate un Sistema
* de Ieferencia Difusa. Esta es la parte central del proyecto.
*
* @param	int 	v 	suma ponderada de los vehiculos en las
* intersecciones a los que se les cederá el paso
*
* @param	int 	c 	suma ponderada de los vehiculos en las
* intersecciones que se mantendrán en espera.
* 
* @return double
*/
double FuzzySemaforo::get_time( int v, int c )
{	
	// Declara el universo de discuro como un conjunto
	FuzzySet universo_discurso(0,0.1,80);



	// Declara los terminos linguisticos de la variable
	// de entrada Vehiculos
	SigmoidalMF vehiculos_bajo( -0.8, 4 );
	GaussianaMF vehiculos_medio( 1.6, 7 );
	SigmoidalMF vehiculos_alto( 0.8, 10 );

	// Declara los terminos linguisticos de la variable
	// de entrada Congestión
	SigmoidalMF congestion_bajo( -0.8, 5);
	SigmoidalMF congestion_alto( 0.8, 5);
	
	// Declara los terminos linguisticos de la variable
	// de salida Tiempo
	TriangularMF tiempo_minimo(  0, 0, 25);
	TriangularMF tiempo_bajo( 0, 25, 40);
	TriangularMF tiempo_medio( 20, 40, 60);
	TriangularMF tiempo_alto( 40, 60, 80);
	TriangularMF tiempo_extra( 60, 80, 100);


	
	// Declara los conjutos consecuentes de las reglas
	// difusas
	FuzzySet salida_vminimo( universo_discurso, tiempo_minimo );
	FuzzySet salida_vbajo( universo_discurso, tiempo_bajo );
	FuzzySet salida_vmedio( universo_discurso, tiempo_medio );
	FuzzySet salida_valto( universo_discurso, tiempo_alto );
	FuzzySet salida_vextra( universo_discurso, tiempo_extra );
	


	// Declara el conjunto conclusión como la union del las
	// imlicaciones siguientes:
	FuzzySet conclusion = 

	// si Vehiculos es Bajo -> Tiempo es Minimo
	(vehiculos_bajo(v)  >> salida_vminimo) &

	// si Vehiculos es Medio y Congestión es Bajo -> Tiempo es Medio
	((vehiculos_medio(v)	&	congestion_bajo(c)) >> salida_vmedio) &

	// si Vehiculos es Medio y Congestión es Alto -> Tiempo es Bajo
	((vehiculos_medio(v)	&	congestion_alto(c)) >> salida_vbajo ) &

	// si Vehiculos es Alto y Congestión es Bajo -> Tiempo es Extra
	((vehiculos_alto(v)		&	congestion_bajo(c)) >> salida_vextra ) &

	// si Vehiculos es Alto y Congestión es Alto -> Tiempo es Alto
	((vehiculos_alto(v)		&	congestion_alto(c)) >> salida_valto );



	// Obtiene el valor de salida mediante el metodo de centroide
	double out = conclusion.get_centroid();


	return out;
}