#ifndef GERENCIA_ABA_H
#define GERENCIA_ABA_H

#include "Aba.hpp"
#include "AbaConta.hpp"

#include <vector>

class GerenciaAba {
private:
    std::vector<Aba *> _abas;

public:
    GerenciaAba();
    ~GerenciaAba();
};

#endif