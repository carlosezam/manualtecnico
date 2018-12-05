#include "FuzzyValue.hpp"

/**
* Constructor por defecto
*
* Crea un objeto FuzzyValue a partir de un valor de tipo fundamental
*
* @param	double	_x
*/
FuzzyValue::FuzzyValue( const double _x ) : x(_x)
{
	// Constructor vacio
}

/**
* Operador de conversioón double
*
* Permite utilizar el operador de conversión de tipo, ya sea de 
* manera explícita o implícita.
*
* @return double valor de mebresía
*/
FuzzyValue::operator double() const
{
	// para convertirlo a double basta con devolver el valor de mebresía
	return x;
}

/**
* Sobrecarga el operador AND
*
* Permite utilizar el operador & (AND) y devuelve el resulatdo de
* efectuar el operador min sobre los operandos
*
* @param	FuzzyValue rvalue operando derecho
* @return	FuzzyValue 
*/
FuzzyValue FuzzyValue::operator&( const FuzzyValue &rvalue ) const
{
	// Compara los valores de mebresía actual y el del operador 
	// derecho y devuelve el más pequeño.
	return (x < rvalue.x) ? x : rvalue.x;
}

/**
* Sobrecarga el operador OR
*
* Permite utilizar el operador | (OR) y devuelve el resulatdo de
* efectuar el operador max sobre los operandos
*
* @param	FuzzyValue rvalue operando derecho
* @return	FuzzyValue 
*/
FuzzyValue FuzzyValue::operator|( const FuzzyValue &rvalue ) const
{
	// Compara los valores de mebresía actual y el del operador 
	// derecho y devuelve el más grande.
	return (x > rvalue.x) ? x : rvalue.x;
}

/**
* Sobrecarga el operador ~
*
* Permite utilizar el operador ~ (Complemento) y devuelve el
* resulatdo de efectuar el complemento a 1
*
* @return	FuzzyValue 
*/
FuzzyValue FuzzyValue::operator~() const
{
	// Devuelve el complemento a uno del valor de mebresía
	return 1 - x;
}