#ifndef CANDIDATO_H
#define CANDIDATO_H

#include "pessoa.h" // Inclui a classe base

// Representa um candidato, herdando de Pessoa
// Armazena dados de candidatura (número, partido)
// contabiliza o total de votos recebidos

class Candidato : public Pessoa { // Herança pública
private:
    int numeroCandidato;
    std::string partido;
    int totalVotos;

public:
    // Construtor
    Candidato(const std::string& nome, const std::string& cpf,
              int numero, const std::string& partido);

    // Incrementa o contador de votos do candidato

    void adicionarVoto();

    // GETTERS
    int getNumeroCandidato() const;
    std::string getPartido() const;
    int getTotalVotos() const;
};

#endif