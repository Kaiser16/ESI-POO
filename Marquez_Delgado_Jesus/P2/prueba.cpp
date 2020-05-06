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
		const Fecha  fHoy;
		const Fecha  fUnaSemana = fHoy + 7;
		const Fecha  fSiguienteAnno(1, 1, fHoy.anno() + 1);
		Articulo articulo1("111", "The Standard Template Library", fHoy, 42.10, 200),articulo2("110", "Fundamentos de C++", fHoy, 35.95, 100);
		Usuario u(sId,sNombre,sApellidos,sDireccion,clave);
		u.compra(articulo1);
   		u.compra(articulo2, 3);
		//Numero n("0123456789abcd");
  		Tarjeta tarjeta(nTarjeta, u, fUnaSemana);
  		Tarjeta tarjeta2(nTarjeta2, u, fUnaSemana);
  		tarjeta.~Tarjeta();
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