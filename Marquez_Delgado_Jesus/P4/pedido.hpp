#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include "tarjeta.hpp"
#include "usuario.hpp"
#include "articulo.hpp"
#include "../P1/fecha.hpp"

class Pedido_Articulo;
class Tarjeta;
class Usuario_Pedido;

class Pedido
{
public:
    Pedido(Usuario_Pedido& usuPed,Pedido_Articulo& pedArt,Usuario& usuario,const Tarjeta& tarjeta,const Fecha& fecha = Fecha());

    class Vacio
    {
    public:
        Vacio(Usuario* u): u_(u){};
        inline const Usuario& usuario() const {return *u_;};
    private:
        Usuario* u_;
    };

    class Impostor
    {
    public:
        Impostor(Usuario* u): u_(u){};
        inline const Usuario& usuario() const {return *u_;};
    private:
        Usuario* u_;
    };

    class SinStock
    {
    public:
        SinStock(Articulo* a): a_(a){};
        inline const Articulo& articulo() const {return *a_;};
    private:
        Articulo* a_;
    };

    const unsigned numero() const;
    const Tarjeta* tarjeta() const;
    const Fecha fecha() const;
    const double total() const;
    static unsigned n_total_pedidos()
    {
        return Npedidos_;
    };
    
private:
    int num_;
    const Tarjeta* tarjeta_;
    Fecha fecha_;
    double total_;
    static unsigned Npedidos_;
};

std::ostream& operator << (std::ostream& os, const Pedido& p);

#endif