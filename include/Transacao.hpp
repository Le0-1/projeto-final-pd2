#ifndef TRANSACAO_H
#define TRANSACAO_H

#include <string>

class Transacao {
    private:
        static int _contador;
        int _id;
        double _valor;
        std::string _descricao, _data, _categoria;

    public:
        Transacao(double valor, std::string descricao, std::string data, 
                std::string categoria);

        double getValor();
        
        std::string getDescricao();

        std::string getData();

        std::string getCategoria();

        int getID();
};

#endif // !TRANSACAO
