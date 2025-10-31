#include "Candidato.h"
#include <iostream>

// Construtor
Candidato::Candidato(const std::string& nome, const std::string& cpf,
                     int numero, const std::string& partido)
    : Pessoa(nome, cpf), // Chama o construtor da classe base Pessoa
      numeroCandidato(numero),
      partido(partido),
      totalVotos(0) { // Todo candidato começa com 0 voto
}

// Métodos
void Candidato::adicionarVoto() {
    this->totalVotos++;
}

// Getters
int Candidato::getNumeroCandidato() const {
    return numeroCandidato;
}

std::string Candidato::getPartido() const {
    return partido;
}

int Candidato::getTotalVotos() const {
    return totalVotos;
}

void Candidato::imprimirDetalhes() const {
    std::cout << "--- DADOS DO CANDIDATO ---" << std::endl;
    std::cout << "Nome: " << getNome() << std::endl;
    std::cout << "CPF: " << getCpf() << std::endl;
    std::cout << "Numero: " << this->numeroCandidato << std::endl;
    std::cout << "Partido: " << this->partido << std::endl;
}