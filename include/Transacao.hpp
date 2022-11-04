#ifndef TRANSACAO
#define TRANSACAO

#include <string>

class Transacao {
    private:
        static int contador;
        int _id;
        double _valor;
        std::string _descricao, _data, _categoria;

    public:
        Transacao(double valor, std::string descricao, std::string data, std::string categoria);

        double GetValor();
        
        std::string GetDescricao();

        std::string GetData();

        std::string GetCategoria();

        int GetID();
};

#endif // !TRANSACAO
