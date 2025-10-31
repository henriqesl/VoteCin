#include "Eleitor.h"
#include <iostream>

// Construtor
Eleitor::Eleitor(const std::string& nome, const std::string& cpf,
                 const std::string& titulo, int secao, int zona)
    : Pessoa(nome, cpf),
      tituloEleitor(titulo),
      secao(secao),
      zona(zona),
      jaVotou(false) { // Todo eleitor começa como "não votou"
}

// Implementação dos métodos
bool Eleitor::podeVotar() const {
    // Retorna true se jaVotou for false
    return !jaVotou;
}

void Eleitor::registrarVoto() {
    this->jaVotou = true;
}

// Getters
std::string Eleitor::getTituloEleitor() const {
    return tituloEleitor;
}

int Eleitor::getSecao() const {
    return secao;
}

int Eleitor::getZona() const {
    return zona;
}

bool Eleitor::getJaVotou() const {
    return jaVotou;
}

void Eleitor::imprimirDetalhes() const {
    std::cout << "--- DADOS DO ELEITOR ---" << std::endl;
    std::cout << "Nome: " << getNome() << std::endl;
    std::cout << "CPF: " << getCpf() << std::endl;
    std::cout << "Titulo: " << this->tituloEleitor << std::endl;
}
