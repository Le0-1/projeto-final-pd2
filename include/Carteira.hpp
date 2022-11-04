#ifndef CARTEIRA
#define CARTEIRA

#include <string>
#include <map>
#include <utility>

#include "Transacao.hpp"

class Carteira {
    private:
        std::string _nome;
        double _saldo_inicial, _saldo_atual;
        std::map<int, Transacao> transacoes;

    public:
        Carteira(double saldo_inicial, std::string nome,  double saldo_atual);

        Carteira(std::string Nome);

        std::map<int, Transacao> UltimasTransacoes(unsigned quantidade);

        void AdicionarTransacao(Transacao t);

        void RemoverTransacao(Transacao t);

        std::string GetNome();

        double GetSaldoInicial();
        
        double GetSaldoAtual();
};

#endif // !CARTEIRA
