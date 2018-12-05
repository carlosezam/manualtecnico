/**
* @file		FuzzySet.hpp
* @author	Carlos Ezam
* @date		28/06/2018
* @version 	0.1
*
* @brief Conjunto difuso
*
* @section Descripción
*
* Este archivo define la calse FuzzySet que representa un conjunto difuso.
* Los conjuntos difusos son una parte central en el proceso de
* inferencia. Esta clase define las operaciones elementales sobre 
* cojuntos difusos como: implicación, defusificación y conjunción.
* 
*/


#ifndef FUZZY_SET
#define FUZZY_SET

#include <vector>
using std::vector;

#include "MembershipFunction.hpp"
#include "FuzzyValue.hpp"

/**
* Clase FuzzySet
*
* Modela un conjunto difuso discreto para relizar los procesos de
* inferencia.
*/
class FuzzySet
{
	// Sobrecarga el operador de inserción de flujo para realizar
	// la implicación
	friend FuzzySet operator>>(const FuzzyValue& value, FuzzySet& set );

	// Sobrecarga el operador AND para realizar la unión de conjuntos
	friend FuzzySet operator&(const FuzzySet&, const FuzzySet& );

public:

	// Constructor principal, crea un conjunto con un dominio definido
	// por un rango y con imagen 0
	FuzzySet( double, double, double );

	// Constructor que crea un conjunto difuso a partir de una función
	// de membresía y otro conjunto.
	FuzzySet( FuzzySet &, MembershipFunction & );

	// Imprime el conjunto difuso en pantalla
	void print( bool cero = false );

	// Defusifica mediante el metodo de centroide
	double get_centroid() const;

private:
	vector<double> set_u; //! imagen del conjunto
	vector<double> set_x; //! dominio del conjunto
};

#endif
