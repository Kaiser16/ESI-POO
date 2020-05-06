#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"

int main()
{
	Cadena a(5,'a');
	Cadena b(6,'a');
	if((a==b) == true)
		std::cout<<a<<std::endl;
	else
		std::cout<<b<<std::endl;
}
