#include "Eleicao.h"
#include <iostream>

Eleicao::Eleicao(const std::string& data) 
    : data(data) {}

void Eleicao::adicionarCandidato(Candidato* c) {
    candidatos.push_back(c);
}

void Eleicao::adicionarEleitor(Eleitor* e) {
    // Chave é o título do eleitor
    eleitores[e->getTituloEleitor()] = e; 
}

void Eleicao::iniciarEleicao() {
    if (status == "NAO_INICIADA") {
        // Cria a Urna passando a lista de candidatos
        urna = std::make_unique<Urna>(candidatos); 
        status = "ATIVA";
        std::cout << "Eleicao em " << data << " INICIADA. Urna pronta." << std::endl;
    }
}

void Eleicao::encerrarEleicao() {
    if (status == "ATIVA") {
        status = "ENCERRADA";
        std::cout << "Eleicao em " << data << " ENCERRADA." << std::endl;
    }
}

bool Eleicao::votar(const std::string& tituloEleitor, int numeroCandidato) {
    if (status != "ATIVA" || !urna) {
        std::cerr << "ERRO: Eleicao nao esta ATIVA ou Urna nao iniciada." << std::endl;
        return false;
    }
    
    // Busca o eleitor
    Eleitor* eleitor = getEleitor(tituloEleitor);
    if (!eleitor) {
        std::cerr << "ERRO: Eleitor com titulo " << tituloEleitor << " nao cadastrado." << std::endl;
        return false;
    }

    // Delega a responsabilidade de votação para a Urna
    return urna->votar(*eleitor, numeroCandidato);
}

// GETTERS

// Busca um eleitor específico
Eleitor* Eleicao::getEleitor(const std::string& titulo) const {
    auto it = eleitores.find(titulo);
    if (it != eleitores.end()) {
        return it->second;
    }
    return nullptr;
}

// Retorna o mapa completo de eleitores para o relatório
const std::map<std::string, Eleitor*>& Eleicao::getEleitores() const {
    return eleitores;
}