#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"

int main()
{
	Fecha a;
	bool correcta = false;
	while(!correcta)
	{
		Fecha b;
		try
		{
			std::cin.clear();
			//std::cin.ignore();
			std::cin>>b;
			correcta = true;
		}		
		catch(Fecha::Invalida& e)
		{
			std::cout<<e.por_que()<<std::endl;
		}
	}
	std::cout<<a<<std::endl;
}