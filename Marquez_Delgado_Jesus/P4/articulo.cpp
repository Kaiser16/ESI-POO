#include "articulo.hpp"

Articulo::Articulo(Cadena cod_ref,Cadena titulo, Fecha f_publi, double precio, unsigned stock)
: cod_ref_(cod_ref),titulo_(titulo),f_publi_(f_publi),precio_(precio),stock_(stock){}

const Cadena Articulo::referencia() const{
	return cod_ref_;
}

const Cadena Articulo::titulo() const{
	return titulo_;
}

const Fecha Articulo::f_publi() const{
	return f_publi_;
}

const double Articulo::precio() const{
	return precio_;
}

const unsigned Articulo::stock() const{
	return stock_;
}

double& Articulo::precio(){
	return precio_;
}

unsigned& Articulo::stock(){
	return stock_;
}

std::ostream& operator << (std::ostream& os, const Articulo& a)
{
	os << "[" << a.referencia() << "]"<<" \""<<a.titulo()<<"\", ";
	os <<a.f_publi().anno()<<". "<< std::setprecision(2) << std::fixed <<a.precio()<<" €"<<std::endl;
	return os;
}