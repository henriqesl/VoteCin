#include "models/Opcao.h"
#include <iostream>

// Construtor: Inicializa os membros privados
Opcao::Opcao(int id, const std::string& nome, const std::string& descricao)
    : idNumerico(id),
      nome(nome),
      descricao(descricao),
      totalVotos(0) {           // Sempre começa com 0 votos
}

// Modifica um membro privado
void Opcao::adicionarVoto() {
    this->totalVotos++;
}

// --- Getters ---
int Opcao::getIdNumerico() const {
    return idNumerico;
}

std::string Opcao::getNome() const {
    return nome;
}

std::string Opcao::getDescricao() const {
    return descricao;
}

int Opcao::getTotalVotos() const {
    return totalVotos;
}

// Função de impressão (usada pelo Admin)
void Opcao::imprimirDetalhes() const {
    std::cout << "--- DADOS DA OPCAO ---" << std::endl;
    std::cout << "Numero: " << this->idNumerico << std::endl;
    std::cout << "Nome: " << this->nome << std::endl;
    std::cout << "Descricao: " << this->descricao << std::endl;
    std::cout << "Votos Atuais: " << this->totalVotos << std::endl;
}