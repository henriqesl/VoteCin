#ifndef ELEITOR_H
#define ELEITOR_H

#include "Pessoa.h" // Inclui a classe base

// Representa um eleitor, herdando de Pessoa
// Armazena dados de votação (título, seção, zona)
// Controla o estado de votação (se já votou ou não)

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

    // Registra que o eleitor votou
    // Altera o status 'jaVotou' para true

    void registrarVoto();

    // GETTERS
    std::string getTituloEleitor() const;
    int getSecao() const;
    int getZona() const;
    bool getJaVotou() const;
};

#endif