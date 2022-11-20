#include <iostream>
#include <memory>
#include <algorithm>

#define ALTA 3
#define MEDIA 2
#define BAIXA 1

class Categoria {
    private:
        std::string _categoria;
        std::string _sub_categoria;
        int _prioridade;

    protected:
        void definirPrioriadeDefault(std::string categoria);

    public:
        Categoria(std::string categoria, std::string sub_categoria, int prioridade);

        //define prioridade default da categoria
        Categoria(std::string categoria, std::string sub_categoria);
        Categoria(std::string categoria);

        std::string getCategoria();
        std::string getSubCategoria();
        int getPrioridade();

        void setCategoria(std::string categoria);
        void setSubCategoria(std::string sub_categoria);
        void setPrioridade(int prioridade);
};