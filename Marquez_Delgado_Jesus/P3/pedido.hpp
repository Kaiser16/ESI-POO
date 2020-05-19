#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include <ostream>
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

class Pedido
{
public:
    Pedido(Usuario_Pedido& usuPed,Pedido_Articulo& pedArt,Usuario& usuario,Tarjeta& tarjeta,Fecha& fecha);

    class Vacio
    {
    public:
        Vacio(Usuario& u): u_(&u){};
        inline const Usuario* usuario() const {return u_;};
    private:
        Usuario* u_;
    };

    class Impostor
    {
    public:
        Impostor(Usuario& u): u_(&u){};
        inline const Usuario* usuario() const {return u_;};
    private:
        Usuario* u_;
    };

    class SinStock
    {
    public:
        SinStock(Articulo& a): a_(&a){};
        inline const Articulo* articulo() const {return a_;};
    private:
        Articulo* a_;
    };

    const unsigned numero() const;
    const Tarjeta* tarjeta() const;
    const Fecha fecha() const;
    const double total() const;
    const unsigned n_total_pedidos() const;
private:
    unsigned numero_;
    Tarjeta* tarjeta_;
    Fecha fecha_;
    double total_;
    static unsigned n_total_pedidos_;
};

std::ostream& operator << (std::ostream& os, const Pedido& p);

#endif