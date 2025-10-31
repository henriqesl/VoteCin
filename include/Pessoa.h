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
    virtual ~Pessoa() = default; // Destrutor virtual

    // GETTERS
    std::string getNome() const;
    std::string getCpf() const;

    // SETTERS
    void setNome(const std::string& nome);
    void setCpf(const std::string& cpf);

    virtual void imprimirDetalhes() const = 0;
};

#endif 
