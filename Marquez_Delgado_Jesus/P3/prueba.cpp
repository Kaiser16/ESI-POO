#include <iostream>
#include <ostream>
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

typedef std::unordered_map<Articulo*,unsigned int> Articulos;

int main()
{
	try
	{	
		const Cadena referencia("1234XYZ");
		const Cadena titulo("Prueba");
		const Fecha  fecha(10, 10, 2000);
		const Cadena sId("pperez");
		const Cadena sNombre("Perico");
		const Cadena sApellidos("Perez Palotes");
		const Cadena sDireccion("13 Rue del Percebe");
		const Clave  clave("pedrofueacomprarpan");
		const Numero nTarjeta("4164 2959 2196 7832");
		const Numero nTarjeta2("3138799837441258");
		const Numero nTarjeta3("5544313153232185");
		Usuario u(sId,sNombre,sApellidos,sDireccion,clave);
		//Numero n("0123456789abcd");
   		mostrar_carro(std::cout, u);

	}catch( Numero::Incorrecto error)
	{
		std::cout<<error.razon()<<std::endl;
	}
	catch( Usuario::Id_duplicado error)
	{
		std::cout<<error.idd()<<std::endl;	
	}
	catch( Tarjeta::Caducada error)
	{
		std::cout<<error.cuando()<<std::endl;
	}
	catch(Clave::Incorrecta error)
	{
		std::cout<<error.razon()<<std::endl;
	}
	catch(Tarjeta::Num_duplicado error)
	{
		std::cout<<error.que()<<std::endl;
	}
}