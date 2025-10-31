#ifndef ELEITOR_H
#define ELEITOR_H

#include "Pessoa.h" // Classe base
#include <iostream>

// Representa um eleitor, herdando de Pessoa
// Armazena dados de votação (título, seção, zona) + controla o estado da votação

class Eleitor : public Pessoa { // Herança pública
private:
    std::string tituloEleitor;
    int secao;
    int zona;
    bool jaVotou;

public:
    // Construtor
    Eleitor(const std::string& nome, const std::string& cpf,
            const std::string& titulo, int secao, int zona);
    
    // Verifica se o eleitor está apto a votar
    // true se ainda não votou, false caso contrário

    bool podeVotar() const;

    // Registra que o eleitor votou, alterando o valor de 'jaVotou'

    void registrarVoto();

    // GETTERS
    std::string getTituloEleitor() const;
    int getSecao() const;
    int getZona() const;
    bool getJaVotou() const;

    virtual void imprimirDetalhes() const override;

};

#endif