#ifndef USUARIO_HPP_
#define USUARIO_HPP_

//#include <crypt.h>
#include <unistd.h>
#include <map>             
#include <unordered_map>   
#include <unordered_set> 
#include <random>
#include <iostream>   
#include <iomanip>
#include <iterator>    
#include "../P1/cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

class Tarjeta;
class Numero;

class Clave{
public:
	enum Razon {CORTA,ERROR_CRYPT};
	Clave(const char* clave);
	class Incorrecta{
	public:
		Incorrecta(Razon r);
		const Razon razon() const;
	private:
		Razon r_;
	};
	const Cadena clave() const;
	bool verifica(const Cadena& clave) const;
private:
	Cadena clave_;
};

class Usuario{
public:
	
	typedef std::map<Numero, Tarjeta*> Tarjetas;
	typedef std::unordered_map<Articulo*,unsigned int> Articulos;
	
	Usuario(Cadena identificador, Cadena nombre, Cadena apellidos, Cadena direccion,Clave clave);

	class Id_duplicado
	{
	public:
		Id_duplicado(Cadena id);
		const Cadena idd() const;
	private:
		Cadena id_;
	};

	inline const Cadena id() const { return identificador_; };
	inline const Cadena nombre() const { return nombre_; };
	inline const Cadena apellidos() const { return apellidos_; };
	const Cadena direccion() const;
	const Tarjetas& tarjetas() const;
	const Articulos& compra() const;

	friend std::ostream& operator << (std::ostream& os, const Usuario& u);

	Usuario(const Usuario& u) = delete;
	Usuario& operator=(const Usuario& u) = delete;
	
	void es_titular_de(Tarjeta& tarjeta);
	void no_es_titular_de(Tarjeta& tarjeta);
	
	void compra(Articulo& articulo);
	void compra(Articulo& articulo, unsigned cantidad);

	unsigned n_articulos() const;
	
	~Usuario();
private:
	const Cadena identificador_;
	const Cadena nombre_;
	const Cadena apellidos_;
	const Cadena direccion_;
	Clave clave_;
	Tarjetas tarjetas_;
	Articulos articulos_;
	static std::unordered_set<Cadena> usuarios_;
};

std::ostream& mostrar_carro (std::ostream& os, const Usuario& u);

#endif