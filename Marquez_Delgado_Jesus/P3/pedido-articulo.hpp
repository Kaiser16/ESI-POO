#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include <map>
#include <utility>
#include <ostream>
#include "pedido.hpp"

class LineaPedido
{
public:
    LineaPedido(double precioVenta,unsigned cantidadVendida_ = 1);
    LineaPedido operator =(double precioVenta) = delete;
    const double precio_venta() const;
    const double cantidad() const;
private:
    double precioVenta_;
    unsigned catidadVendida_;
};

std::ostream& operator<<(std::ostream& os,LineaPedido linPed)
{
    os<<linPed.precio_venta()<<"\t"<<linPed.cantidad();
    return os;
}

class Pedido_Articulo
{
public:
    struct OrdenaArticulos
    {
        bool operator()(const Articulo* a,const Articulo* b)
        {return a->referencia() < b->referencia();}
    };
    
    struct OrdenaPedidos
    {
        bool operator()(const Pedido* a,const Pedido* b)
        {return a->numero() < b->numero();}
    };
    typedef std::map<Articulo*, LineaPedido,OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    
    void pedir(Pedido* ped,Articulo* art,double precio,unsigned cantidad = 1);
    void pedir(Articulo* art,Pedido* ped,double precio,unsigned cantidad = 1);

    const ItemsPedido& detalle(Pedido& p) const;
    const Pedidos& ventas(Articulo& a) const;

    void mostrarDetallePedidos(std::ostream& os);

    void mostrarVentasArticulos(std::ostream& os);

private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> pedArts;
    std::map<Articulo*, Pedidos, OrdenaArticulos> artPeds;
};

std::ostream& operator <<(std::ostream& os,Pedido_Articulo::ItemsPedido artsPed);

std::ostream& operator <<(std::ostream& os,Pedido_Articulo::Pedidos pedidos);

#endif