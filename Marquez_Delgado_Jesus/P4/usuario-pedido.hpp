#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_

#include <map>
#include <set>

class Pedido;
class Usuario;

class Usuario_Pedido
{
public:
    typedef std::set<Pedido*> Pedidos;
    typedef std::map<Usuario*,Pedidos> usuarioPedidos;
    typedef std::map<Pedido*,Usuario*> pedidoUsuario;

    void asocia(Usuario& u,Pedido& p)
    {
        usuPed_[&u].insert(&p);
        pedUsu_[&p] = &u;
    };
    void asocia(Pedido& p,Usuario& u){asocia(u,p);};

    const Pedidos& pedidos(Usuario& u) const
    {
        return usuPed_.find(&u)->second;
    };
    Usuario* cliente(Pedido& p) const
    {
        return pedUsu_.find(&p)->second;
    };
private:
    usuarioPedidos usuPed_;
    pedidoUsuario pedUsu_;
};  

#endif