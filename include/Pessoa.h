#ifndef PESSOA_H
#define PESSOA_H

#include <string>

class Pessoa {
private:
    std::string nome;
    std::string cpf;

public:
    Pessoa();
    Pessoa(const std::string& nome, const std::string& cpf);  // Construtor com parâmetros

    // (get/set)
    std::string getNome() const;
    std::string getCpf() const;
    void setNome(const std::string& nome);
    void setCpf(const std::string& cpf);
};

#endif 
