#include "pessoa.h"
#include <iostream>

// Construtor sem parâmetros
Pessoa::Pessoa() {
    nome = "Indefinido";
    cpf = "000.000.000-00";
}

// Construtor com parâmetros
Pessoa::Pessoa(const std::string& nome, const std::string& cpf) {
    this->nome = nome;
    this->cpf = cpf;
}

// Getters
std::string Pessoa::getNome() const {
    return nome;
}

std::string Pessoa::getCpf() const {
    return cpf;
}

// Setters
void Pessoa::setNome(const std::string& nome) {
    this->nome = nome;
}

void Pessoa::setCpf(const std::string& cpf) {
    this->cpf = cpf;
}
