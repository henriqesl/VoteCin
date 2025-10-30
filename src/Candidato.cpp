#include "Candidato.h"

// Implementação do Construtor
Candidato::Candidato(const std::string& nome, const std::string& cpf,
                     int numero, const std::string& partido)
    : Pessoa(nome, cpf), // Chama o construtor da classe base Pessoa
      numeroCandidato(numero),
      partido(partido),
      totalVotos(0) { // Todo candidato começa com 0 voto
}

// Implementação dos métodos
void Candidato::adicionarVoto() {
    this->totalVotos++;
}

// Implementação dos Getters
int Candidato::getNumeroCandidato() const {
    return numeroCandidato;
}

std::string Candidato::getPartido() const {
    return partido;
}

int Candidato::getTotalVotos() const {
    return totalVotos;
}