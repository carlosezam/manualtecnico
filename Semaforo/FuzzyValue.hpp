/**
* @file		FuzzyValue.hpp
* @author	Carlos Ezam
* @date		28/06/2018
* @version 	0.1
*
* @brief Valor Difuso
*
* @section Descripción
*
* Este archivo define la clase FuzzyValue. Las funciones de membresía
* devuelven el valor de fusificación como un objeto de esta clase,
* permitiendo asi usar los operadores de unión, intersección y
* complemento sobre los resultados.
*/

#ifndef FUZZY_VALUE
#define FUZZY_VALUE

/**
* Clase FuzzyValue
*
* Es una envoltura para un valor de membresía de tipo double. De esta
* manera se define las operadores que se pueden utilizar sobre los
* objetos de esta clase.
*/
class FuzzyValue
{
	
public: 

	// Constructor por defecto.
	FuzzyValue( const double = 0 );
	
	// Operador de conversión double
	operator double() const;

	// Sobrecarga el operador AND 
	FuzzyValue operator&( const FuzzyValue &rvalue ) const;

	// Sobrecarga el operador OR
	FuzzyValue operator|( const FuzzyValue &rvalue ) const;

	// Sobrecarga el operador Complemento
	FuzzyValue operator~() const;

private:
	double x; //! valor de membresía
};


#endif