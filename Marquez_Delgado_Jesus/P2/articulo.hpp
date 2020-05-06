#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include <ostream>
#include <iomanip>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

class Articulo {
public:
	Articulo(Cadena cod_ref,Cadena titulo, Fecha f_publi, double precio, unsigned stock = 0);
	const Cadena referencia() const;
	const Cadena titulo() const;
	const Fecha f_publi() const;
	const double precio() const;
	const unsigned stock() const;
	double& precio();
	unsigned& stock();
private:
	const Cadena cod_ref_;
	const Cadena titulo_;
	const Fecha f_publi_;
	double precio_;
	unsigned stock_;
};

std::ostream& operator << (std::ostream& os, const Articulo& a);
#endif