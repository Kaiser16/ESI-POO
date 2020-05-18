#include "tarjeta.hpp"

#include <iostream>

std::set<Numero> Tarjeta::tarjetas_{};

bool EsBlanco(char c)
{
	return isspace(c);
}

bool EsDigito(char c)
{
	return isalpha(c);
}

Numero::Numero(Cadena numero) : numero_(numero)
{
	auto aux = std::remove_if(numero_.begin(),numero_.end(),EsBlanco);
	if(aux != numero_.end())
	{
		int j = 0;
		for(auto i = numero_.begin(); i!=aux;++i)
			j++;
		numero_ = numero_.substr(0,j);
	}

	aux = std::find_if(numero_.begin(),numero_.end(),EsDigito);
	if(aux != numero_.end())
		throw Incorrecto(DIGITOS);

	if(numero_.length() < 13 || numero_.length() > 19)
		throw Incorrecto(LONGITUD);
	else if(!luhn(numero_))
	{
		throw Incorrecto(NO_VALIDO);
	}
};

Numero::operator const char*() const
{
	return numero_.c_str();
}

bool operator <(const Numero& a,const Numero& b)
{
	if(strcmp(a,b) < 0)
		return true;
	else
		return false;
}

Numero::Incorrecto::Incorrecto(Razon r):r_(r){}

const Numero::Razon Numero::Incorrecto::razon() const
{
	return r_;
}

Tarjeta::Tarjeta(Numero numero,Usuario& titular,Fecha caducidad)
: numero_(numero),titular_(&titular),caducidad_(caducidad),activa_(true)
{	
	if(Fecha() > caducidad_)
		throw Tarjeta::Caducada(caducidad_);
	titular.es_titular_de(*this);
	if(!(tarjetas_.insert(numero).second))
		throw Tarjeta::Num_duplicado(numero_);
}

const Numero Tarjeta::numero() const
{
	return numero_;
}

const Usuario* Tarjeta::titular() const
{
	return titular_;
}

const Fecha Tarjeta::caducidad() const
{
	return caducidad_;
}

const bool Tarjeta::activa() const
{
	return activa_;
}

const Tarjeta::Tipo Tarjeta::tipo() const
{
	if(numero_[0] == '3')
	{
		if(numero_[1] == '4' || numero_[1] == '7')
			return AmericanExpress;
		else
			return JCB;
	}
	else if(numero_[0] == '4')
		return VISA;
	else if(numero_[0] == '5')
		return Mastercard;
	else if(numero_[0] == '6')
		return Maestro;
	else
		return Otro;
}

bool Tarjeta::activa(bool activa)
{
	activa_ = activa;
	return activa_;
}

void Tarjeta::anular_titular()
{
	titular_ = nullptr;
	activa_ = false;
}

bool operator <(const Tarjeta& a,const Tarjeta& b)
{
	return (a.numero() < b.numero());
}

Cadena tocapitalletter(Cadena a)
{
	for(int i = 0; i < a.length(); i++)
		a[i] = char(toupper(a[i]));
	return a;
}

std::ostream& operator << (std::ostream& os, const Tarjeta& t)
{
	Tarjeta::Tipo tipo = t.tipo();
	os<<"\n";

	if(tipo == Tarjeta::AmericanExpress)
		os<<"AmericanExpress";
	else if(tipo == Tarjeta::JCB)
		os<<"JCB";
	else if(tipo == Tarjeta::VISA)
		os<<"VISA";
	else if(tipo == Tarjeta::Mastercard)
		os<<"Mastercard";
	else if(tipo == Tarjeta::Maestro)
		os<<"Maestro";
	else
		os<<"Otros";

	Cadena nombre = tocapitalletter(t.titular()->nombre());
	Cadena apellidos = tocapitalletter(t.titular()->apellidos());
	os<<"\n";
	os<<t.numero()<<"\n";
	os<<nombre<<" "<<apellidos<<"\n";
	os<<"Caduca: ";
	if(t.caducidad().mes() < 10)
		os <<'0'<<t.caducidad().mes();
	else
		os <<t.caducidad().mes();
	os <<"/"<<(t.caducidad().anno()%100)<<"\n";
	return os;
}

Tarjeta::Caducada::Caducada(Fecha caducada):caducada_(caducada){};

const Fecha Tarjeta::Caducada::cuando() const
{
	return caducada_;
}

Tarjeta::Num_duplicado::Num_duplicado(Numero numero):numero_(numero){};

const Numero Tarjeta::Num_duplicado::que() const
{
	return numero_;
}

Tarjeta::~Tarjeta()
{
	if(titular_ != nullptr)
		const_cast<Usuario*>(titular_)->no_es_titular_de(*this);
	tarjetas_.erase(numero_);
}