#include "models/Votante.h"
#include <iostream>

// Construtor: Chama o construtor da classe base (Participante)
Votante::Votante(const std::string& nome, const std::string& id)
    : Participante(nome, id), // Passa os dados para a classe Participante
      jaVotou(false) { // Todo votante começa como "não votou"
}

// Verifica o estado 
bool Votante::podeVotar() const {
    return !jaVotou; // Retorna true se jaVotou for false
}

// Modifica o estado (Encapsulamento)
void Votante::registrarVoto() {
    this->jaVotou = true;
}

// --- Getter ---
bool Votante::getJaVotou() const {
    return jaVotou;
}

// Implementação do método virtual (Polimorfismo)
void Votante::imprimirDetalhes() const {
    std::cout << "--- DADOS DO VOTANTE ---" << std::endl;
    std::cout << "Nome: " << getNome() << std::endl; // Método da classe base
    std::cout << "ID: " << getId() << std::endl;     // Método da classe base
    std::cout << "Status: " << (jaVotou ? "Ja votou" : "Apto a votar") << std::endl;
}