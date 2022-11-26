#ifndef ABA_CONTA_H
#define ABA_CONTA_H

#include "Aba.hpp"
#include "Carteira.hpp"
// #include "ContaBancaria.hpp"

#include <vector>

class AbaConta : public Aba {
  private:
    std::vector<Carteira *> _contas;

    std::vector<Carteira *> &get_contas();
    void imprimirInfo() override;

  public:
    AbaConta(WINDOW *janela);
};

#endif