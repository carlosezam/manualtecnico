#include "MembershipFunction.hpp"

#include <cstdio>
#include <vector>
using namespace std;

/**
* Constructor de TriangularMF
*
* Crea una funcion triangular a partir de sus tres vertices: A, B y C.
*
* @param double	_a 	vertice A
* @param double _b 	vertice B
* @param double _c 	vertice C
*/
TriangularMF::TriangularMF(double _a, double _b, double _c ) : a(_a), b(_b), c(_c)
{
	//Constructor vacio
}


/**
* Sobrecarga del operador ()
*
* Calcula el valor de membresia en base a la funcion definida
* por los vertices A, B y C.
*
* @param	double	x 	valor discreto a fuzificar.
* @return	FuzzyValue 	valor de membresia u(x).
*/
FuzzyValue TriangularMF::operator()(double x) const
{
	double u;
	if 		( x <= a)			u = 0;
	else if ( x > a && x < b )	u = (x - a) / (b - a);
	else if ( x == b )			u = 1;
	else if ( x > b && x < c )	u = (c - x) / (c - b);
	else 						u = 0;
	return u;
}

/**
* Constructor de SigmoidalMF
*
* Crea una función Sigmoidal a partir de su pendiente y punto de cruce
*
* @param double	a 	determina la pendiente de la curva
* @param double x0 	determina el punto de cruce
*/
SigmoidalMF::SigmoidalMF(double _a, double _x0) : a(_a), x0(_x0)
{
	//Constructor vacio
}

/**
* Sobrecarga del operador ()
*
* Calcula el valor de membresia en base a la funcion definida
* por la pendienete y punto de cruce
*
* @param	double	x 	valor discreto a fuzificar.
* @return	FuzzyValue 	valor de membresia u(x).
*/
FuzzyValue SigmoidalMF::operator()(double x) const
{
	double u;
	u = 1 / ( 1 + exp( (-1 * a )*(x-x0) ));
	return u;
}

/**
* Constructor de GaussianaMF
*
* Crea una función Gaussiana a partir de su pendiente y punto de cruce
*
* @param double	a 	determina la pendiente de la curva
* @param double x0 	determina el punto de cruce
*/
GaussianaMF::GaussianaMF(double _a, double _x0) : a(_a), x0(_x0)
{
	//Constructor vacio
}

/**
* Sobrecarga del operador ()
*
* Calcula el valor de membresia en base a la funcion definida
* por la pendienete y punto de cruce
*
* @param	double	x 	valor discreto a fuzificar.
* @return	FuzzyValue 	valor de membresia u(x).
*/
FuzzyValue GaussianaMF::operator()(double x) const
{
	double u;
	u = exp( -0.5 * pow( ((x-x0)/a) ,2));
	return u;
}