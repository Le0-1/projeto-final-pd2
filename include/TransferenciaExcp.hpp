#ifndef TRANSFERENCIA_EXCP_H
#define TRANSFERENCIA_EXCP_H

#include <iostream>
#include <exception>

namespace trfexcp {
    
    class DataInvalida : public std::exception {
        private:
            std::string _data;

        public:
            DataInvalida(std::string data);

            const char* what() const throw();

            std::string getData();
    };
}

#endif