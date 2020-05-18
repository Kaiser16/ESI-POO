#include "pedido.hpp"

Pedido::Pedido(Usuario_Pedido& usuPed,Pedido_Articulo& pedArt,Usuario& usuario,
Tarjeta& tarjeta,Fecha& fecha): tarjeta_(&tarjeta), fecha_(fecha)
{
    
}

const unsigned Pedido::numero() const
{
    return numero_;
}

const Tarjeta* Pedido::tarjeta() const
{
    return tarjeta_;
}

const Fecha Pedido::fecha() const
{
    return fecha_;
}

const double Pedido::total() const
{
    return total_;
}

const unsigned Pedido::n_total_pedidos() const
{
    return n_total_pedidos_;
}