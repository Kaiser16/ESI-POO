#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include <set>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"

bool luhn(const Cadena& numero);

class Usuario;

class Numero {
public:
	enum Razon{LONGITUD,DIGITOS,NO_VALIDO};
	class Incorrecto
	{
	public:
		Incorrecto(Razon r);
		const Razon razon() const;
	private:
		Razon r_;
	};
	Numero(Cadena numero);
	operator const char*() const;

private:
	Cadena numero_;
};

bool operator <(const Numero& a,const Numero& b);

class Tarjeta {
public:
	enum Tipo{Otro,VISA,Mastercard,Maestro,JCB,AmericanExpress};
	Tarjeta(Numero numero, Usuario& titular,Fecha caducidad);
	class Caducada
	{
	public:
		Caducada(Fecha caducada);
		const Fecha cuando() const;
	private:
		Fecha caducada_;
	};

	class Num_duplicado
	{
	public:
		Num_duplicado(Numero numero);
		const Numero que() const;
	private:
		Numero numero_;
	};

	class Desactivada{};

	const Numero numero() const;
	const Usuario* titular() const;
	const Fecha caducidad() const;
	const bool activa() const;
	const Tipo tipo() const;

	Tarjeta(const Tarjeta& u) = delete;
	Tarjeta& operator=(const Tarjeta& u) = delete;

	bool activa(bool activa = true);
	void anular_titular();

	~Tarjeta();
private:
	const Numero numero_;
	const Usuario* titular_;
	const Fecha caducidad_;
	bool activa_;
	static std::set<Numero> tarjetas_;
};

bool operator <(const Tarjeta& a,const Tarjeta& b);

std::ostream& operator << (std::ostream& os, const Tarjeta& t);

inline const Numero Tarjeta::numero() const
{
	return numero_;
}

inline const Usuario* Tarjeta::titular() const
{
	return titular_;
}

inline const Fecha Tarjeta::caducidad() const
{
	return caducidad_;
}

inline const bool Tarjeta::activa() const
{
	return activa_;
}

#endif