#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include <ostream>
#include <iomanip>
#include <set>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

class Autor{
public:
	Autor(Cadena nombre,Cadena apellidos,Cadena direccion);
	const Cadena nombre() const noexcept;
	const Cadena apellidos() const noexcept;
	const Cadena direccion() const noexcept;
private:
	Cadena nombre_,apellidos_,direccion_;
};

inline const Cadena Autor::nombre() const noexcept{
	return nombre_;
}

inline const Cadena Autor::apellidos() const noexcept{
	return apellidos_;
}
	
inline const Cadena Autor::direccion() const noexcept{
	return direccion_;
}

class Articulo {
public:
	class Autores_vacios {};
	typedef std::set<Autor*> Autores;
	Articulo(Autores& autores,Cadena cod_ref,Cadena titulo, Fecha f_publi, double precio);
	const Cadena referencia() const;
	const Cadena titulo() const;
	const Fecha f_publi() const;
	const double precio() const;
	const Autores& autores() const;

	virtual const void impresion_especifica(std::ostream& os) const = 0;

	double& precio();

	virtual ~Articulo() {};
private:
	Autores autores_;
	const Cadena cod_ref_;
	const Cadena titulo_;
	const Fecha f_publi_;
	double precio_;
};

inline const Articulo::Autores& Articulo::autores() const{
	return autores_;
}

class ArticuloAlmacenable : public Articulo{
public:
	ArticuloAlmacenable(Autores autores,Cadena cod_ref,Cadena titulo, Fecha f_publi, double precio,unsigned stock = 0);

	const unsigned stock() const;
	unsigned& stock();

	virtual ~ArticuloAlmacenable() {};
protected:
	unsigned stock_;
};

inline const unsigned ArticuloAlmacenable::stock() const{
	return stock_;
}

inline unsigned& ArticuloAlmacenable::stock(){
	return stock_;
}

class Libro : public ArticuloAlmacenable{
public:
	Libro(Autores autores,Cadena cod_ref,Cadena titulo, Fecha f_publi, double precio,unsigned n_pag,unsigned stock = 0);

	const void impresion_especifica(std::ostream& os) const;

	const unsigned n_pag() const;
private:
	const unsigned n_pag_;
};

inline const unsigned Libro::n_pag() const{
	return n_pag_;
}

class Cederron : public ArticuloAlmacenable{
public:
	Cederron(Autores autores,Cadena cod_ref,Cadena titulo, Fecha f_publi, double precio,unsigned tam,unsigned stock = 0);

	const void impresion_especifica(std::ostream& os) const;

	const unsigned tam() const;
private:
	const unsigned tam_;
};

inline const unsigned Cederron::tam() const{
	return tam_;
}

class LibroDigital : public Articulo{
public:
	LibroDigital(Autores autores,Cadena cod_ref,Cadena titulo, Fecha f_publi, double precio,Fecha f_expir);

	const void impresion_especifica(std::ostream& os) const;

	const Fecha f_expir() const;
private:
	Fecha f_expir_;
};

inline const Fecha LibroDigital::f_expir() const{
	return f_expir_;
}

std::ostream& operator << (std::ostream& os, const Articulo& a);
#endif