#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"

int main()
{
	/*Fecha a("12/01/1999");
	std::cin>>a;
	std::cout<<a<<std::endl;*/
	Cadena c("hola");
	c+="adios";
	std::cout<<c<<std::endl;
}
//ls -1 Marquez_Delgado_Jesus/P1/{{cadena,fecha}.[ch]pp,Makefile} | tar -cvzf Marquez_Delgado_Jesus.tar.gz -T -