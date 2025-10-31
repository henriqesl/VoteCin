#ifndef CANDIDATO_H
#define CANDIDATO_H

#include "Pessoa.h" // Classe base

// Representa um candidato, herdando de Pessoa
// Armazena dados de candidatura (número, partido) + contagem de votos

class Candidato : public Pessoa{ // Herança pública
private:
    int numeroCandidato;
    std::string partido;
    int totalVotos;

public:
    // Construtor
    Candidato(const std::string& nome, const std::string& cpf, int numero, const std::string& partido);

    // Contador de votos do candidato
    void adicionarVoto();

    // GETTERS
    int getNumeroCandidato() const;
    std::string getPartido() const;
    int getTotalVotos() const;

    virtual void imprimirDetalhes() const override;

};

#endif