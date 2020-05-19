#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_

#include "usuario.hpp"
#include "pedido.hpp"

class Usuario_Pedido
{
public:
    typedef std::set<Pedido*> Pedidos;

    void asocia(Usuario* u,Pedido* p);
    void asocia(Pedido* p,Usuario* u);

    const Pedidos& pedidos(const Usuario* u) const;
    const Usuarios& cliente(const Pedido* p) const;
private:
    std::map<Usuario*,Pedidos> Usuario_Pedido;
    std::map<Pedido*,Usuario*> Pedido_Usuario;
};  

#endif