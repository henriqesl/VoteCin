#include "models/Participante.h"
#include <iostream>

// Construtor padrão
Participante::Participante() {
    nome = "Indefinido";
    id = "0000";
}

// Construtor principal
Participante::Participante(const std::string& nome, const std::string& id) {
    this->nome = nome;
    this->id = id;
}

// --- Getters ---
std::string Participante::getNome() const {
    return nome;
}

std::string Participante::getId() const {
    return id;
}

// --- Setters ---
void Participante::setNome(const std::string& nome) {
    this->nome = nome;
}

void Participante::setId(const std::string& id) {
    this->id = id;
}
