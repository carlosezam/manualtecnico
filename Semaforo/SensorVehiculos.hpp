/**
* @file		SensorVehiculos.hpp
* @author	Carlos Ezam
* @date		28/06/2018
* @version 	0.1
*
* @brief Sensor Vehiculos
*
* @section Descripción
*
* Este archivo define la clase SensorVehiculos, el propósito de
* esta clase es definir la función virtual pura read(). La clase
* FuzzySemaforo recibe una referencia de este tipo para obtener los
* cantidad de carros de las avenidas. El usuario final debe
* implementar dicha función.
*/

#ifndef SENSOR_VEHICULOS
#define SENSOR_VEHICULOS

/**
* Clase SensorVehiculos
*
* Esta clase define el metodo read usado por la clase FuzzySemaforo
* para obtener el número de carros en la intersección 
*/
class SensorVehiculos
{
public:

	// funcion virtual pura que debe implementar el usuario
	virtual vector<double> read() const = 0;
};

#endif