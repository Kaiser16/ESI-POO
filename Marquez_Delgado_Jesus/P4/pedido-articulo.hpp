#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include<iostream>
#include<map>
#include "pedido.hpp"
#include "articulo.hpp"


class LineaPedido
{
public:
    explicit LineaPedido(double precioVenta,unsigned cantidadVendida = 1);
    LineaPedido operator =(double precioVenta) = delete;
    const double precio_venta() const;
    const unsigned int cantidad() const;
private:
    double precioVenta_;
    unsigned int cantidadVendida_;
};

class Articulo;
class Pedido;

struct OrdenaPedidos
{
    bool operator()(const Pedido* p1,const Pedido* p2) const;
};

struct OrdenaArticulos
{
    bool operator()(const Articulo* a1,const Articulo* a2) const
    {
        return a1->referencia() < a2->referencia();
    }
};

class Pedido_Articulo
{
public:
    typedef std::map<Articulo*, LineaPedido,OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    
    void pedir(Pedido& ped,Articulo& art,double precio,unsigned cantidad = 1);
    void pedir(Articulo& art,Pedido& ped,double precio,unsigned cantidad = 1);

    const ItemsPedido& detalle(Pedido& p) const;
    Pedidos ventas(Articulo& a) const;

    std::ostream& mostrarDetallePedidos(std::ostream& os);

    std::ostream& mostrarVentasArticulos(std::ostream& os);

private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> pedArt;
    std::map<Articulo*, Pedidos, OrdenaArticulos> artPed;
};

std::ostream& operator <<(std::ostream& os,const LineaPedido& lp);

std::ostream& operator <<(std::ostream& os,const Pedido_Articulo::ItemsPedido& artsPed);

std::ostream& operator <<(std::ostream& os,const Pedido_Articulo::Pedidos& pedidos);

#endif