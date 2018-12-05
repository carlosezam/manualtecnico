/**
* @file		MembershipFunction.hpp
* @author	Carlos Ezam
* @date		28/06/2018
* @version 	0.1
*
* @brief Funciones de membresía
*
* @section Descripción
*
* Este archivo define la clase abstracta MembershipFunction, toda 
* clase que represente una función de membresía debe exteder de 
* esta clase para poder ser usada con el resto de clases de este
* proyecto.
*
* Este archivo además, contiene las definciones de las clases que repre-
* sentan funciones de mebresía tipicas.
*
* Solo se implementan las funciones necesarias para este proyecto.
*/

#ifndef MEMBERSHIP_FUNCTION
#define MEMBERSHIP_FUNCTION
#include "FuzzyValue.hpp"
#include <cmath>

/**
* Clase MembershipFunction
*
* Define una única función. Tal función es bastante especial puesto que
* sobrecarga el operador () como una función virtual pura. Toda clase
* que represente una función de membresía definida por el usuario, debe
* extender de esta clase y debe implementar dicho operador.
*/
class MembershipFunction
{
public:

	/**
	* Función virtual pura operator()
	*
	* Sobrecarga del operador (), que debe ser sobreescrito por las clases derivadas
	*
	* @param	double 		x 	valor a fuzificar
	* @return	FuzzyValue 		clase que representa un valor difuso
	*/
	virtual FuzzyValue	operator()	(double x) const = 0;
};



/**
* Interfaz de la clase TriangularMF
*
* Representa una función de membresía triangular
*/
class TriangularMF : public MembershipFunction
{
public:

	// Constructor de TriangularMF
	TriangularMF( double, double, double);

	// Calcula el grado de membresía de un valor dado
	virtual FuzzyValue operator()(double ) const;
	
private:
	double a; //! vertice A de la función triangular
	double b; //! vertice B de la función triangular
	double c; //! vertice C de la función triangular
};



/**
* Interfaz de la clase SigmoidalMF
*
* Representa una función de membresía Sigmoidal
*/
class SigmoidalMF : public MembershipFunction
{
public:
	
	// Constructor de SigmoidalMF
	SigmoidalMF( double, double);

	// Calcula el grado de mebresía de un valor dado
	virtual FuzzyValue operator()(double) const;

private:
	double a;	//! valor de la pendiente de la función
	double x0;	//! punto de cruce
};



/**
* Interfaz de la clase GaussianaMF
*
* Representa una función de membresía Gaussiana
*/
class GaussianaMF : public MembershipFunction
{
public:

	// Constructor de SigmoidalMF
	GaussianaMF( double, double);

	// Calcula el grado de mebresía de un valor dado
	virtual FuzzyValue operator()(double x) const;
	
private:
	double a;	//! pendiente de la función
	double x0;	//! punto de cruce
};
#endif