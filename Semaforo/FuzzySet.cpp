#include "FuzzySet.hpp"
#include <cstdlib>
#include <cstdio>

/*
* Sobrecarga del operador de iserción de flujo
*
* El operador es sobrecargado como un operador de implicación modus ponens, g.e.
* A $\rightarrow$ B   puede ser modelado como  A >> B
* devuelve un conjunto conclusión
*
* @param	FuzzyValue&	value 	antecedente
* @param 	FuzzySet&	set 	consecuente
* @return	FuzzySet
*/
FuzzySet operator>>(const FuzzyValue& value, FuzzySet& set )
{
	// Itera sobre todo el dominio del conjunto
	for( size_t i = 0; i < set.set_u.size(); i++ )
	{
		// Corta el conjunto a la altura del valor de membresía del antecedente
		set.set_u[ i ] = (set.set_u[ i ] < value) ? set.set_u[ i ] : static_cast<double>(value);
	}

	// devuelve el conjunto ya cortado
	return set;
}

/**
* Sobrecarga el operador AND
*
* Devuelve un conjunto resulato de la unión de los dos conjuntos 
* que le son proporcionados
*
* @param	FuzzySet&	setl operando izquierdo
* @param	FuzzySet&	setr operando derecho
* @return	FuzzySet
*/
FuzzySet operator&(const FuzzySet& setl, const FuzzySet& setr )
{
	// Crea una copia de uno de los conjuntos
	FuzzySet setc( setl );

	// Itera ambos conjuntos (operando izq. y der.)
	for (int i = 0; i < setl.set_u.size(); ++i)
	{
		// Realiza la unión conservando el mayor de los valores de
		// membresía para cada valor del universo de discurso (operador max)
		setc.set_u[ i ] = (setl.set_u[i] > setr.set_u[i]) ? setl.set_u[i] : setr.set_u[i];
	}

	// Devuelve el conjunto resultado
	return setc;
}

/**
* Defusifica mediante el método de centroide
*
* Aplica el metodo de centroide sobre los valores de conjunto
* y devuelve el el valor certero.
*
* @return	double
*/
double FuzzySet::get_centroid() const
{
	double ux_x = 0;
	double ux = 0;
	// Rezaliza la sumatoria
	for( size_t i = 0; i < set_u.size(); ++i )
	{
		// u(x) * x
		ux_x += set_x[ i ] * set_u[ i ];
		// u(x)
		ux += set_u[ i ];
	}

	return ux_x / ux;
}

/**
* Constructor
*
* Crea un conjunto difuso discreto con membresía 0 donde el universo de
* discuro se encuentra en el rango [begin, end] con step como intervalo
* e.g. FuzzySet(2,2,10) -> {0/2, 0/4, 0/6, 0/8, 0/10} 
*
* @param	double	begin 	primer elemento (inclusive)
* @param	double	step	intervalo o salto
* @param	double	end		último elemento
*/
FuzzySet::FuzzySet( double begin, double step, double end )
{
	// Calcula el total de elementos que tendrá el cojunto
	double elements = (end - begin) / step +1;

	// inicializa la imagen del conjunto
	set_u = vector<double>(elements);

	// inicializa el dominio del conjunto
	set_x = vector<double>(elements);
	
	for( size_t i = 0; i < elements; ++i )
	{
		// asigna los valores del dominio
		set_x[ i ] = begin + ( i * step );
		// asigna 0 como valor de membresía 
		set_u[ i ] = 0; 
	}

}

/**
* Constructor
*
* Crea un conjunto difuso discreto, resultado de aplicar la funcion
* de membresía mf a los elementos del conjunto fset.
*
* @param	FuzzySet&			begin 	conjunto de entrada
* @param	MembershipFunction&	step	función de membresía
*/
FuzzySet::FuzzySet( FuzzySet &fset, MembershipFunction &mf )
{
	// inicializa el dominio y la imagen del conjunto
	// con el tamaño exacto del conjunto entrada
	set_u = vector<double>( fset.set_u.size() );
	set_x = vector<double>( fset.set_x.size() );

	for (int i = 0; i < set_x.size(); ++i)
	{
		// copia el dominio
		set_x[ i ] = fset.set_x[ i ];

		// aplica la función de membresía a la imagen
		set_u[ i ] = mf( set_x[ i ] );
	}
}

/**
* Imprime el conjunto
*
* Imprime el conjunto difuso usando la notación propia de los
* conjuntos difusos discretos: x / u(x)
*
* @param	bool	cero 	indica si deben imprimir los valores u(x)=0
*/
void FuzzySet::print( bool cero )
{
	printf("( ");
	
	// Si no está vacio
	if( set_x.size() > 0 )
	{
		// imprime si el primer elemento es diferente de cero
		if( set_u[ 0 ] != 0 || cero )
			printf( "%.2f/%.2f", set_x[ 0 ], set_u[ 0 ] );
		
		// recoore el resto de elementos
		for( size_t item = 1; item < set_x.size(); ++item )
		{
			// imprime si u(x) es diferen de cero
			if( set_u[ item ] != 0 || cero )
				printf( ", %.2f/%.2f", set_x[ item ], set_u[ item ] );
		}
	}

	printf(" )");
}
