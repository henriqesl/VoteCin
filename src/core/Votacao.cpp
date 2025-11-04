#include "core/Votacao.h"
#include "core/Urna.h" 
#include "models/Votante.h"
#include "models/Opcao.h"
#include <iostream>

Votacao::Votacao(const std::string& titulo, const std::string& data) 
    : titulo(titulo), data(data), status("NAO_INICIADA") {}

Votacao::~Votacao() = default;

void Votacao::adicionarOpcao(Opcao* o) {
    opcoes.push_back(o);
}

void Votacao::adicionarVotante(Votante* v) {
    votantes[v->getId()] = v; 
}

void Votacao::limparOpcoes() {
    opcoes.clear();
    urna.reset(nullptr); 
}

bool Votacao::iniciarVotacao() {
    if (status == "NAO_INICIADA") {
        if (opcoes.empty()) {
            std::cout << "[ERRO] Nao e possivel iniciar uma votacao sem opcoes. Adicione opcoes no menu Admin.\n";
            return false;
        }
        urna = std::make_unique<Urna>(opcoes); 
        status = "ATIVA";
        std::cout << "Votacao '" << titulo << "' (Data: " << data << ") INICIADA. Urna pronta." << std::endl;
        return true; // Sucesso
    }
    std::cout << "[AVISO] A votacao ja foi iniciada (ou encerrada).\n";
    return false; 
}

void Votacao::encerrarVotacao() {
    if (status == "ATIVA") {
        status = "ENCERRADA";
        std::cout << "Votacao '" << titulo << "' ENCERRADA." << std::endl;
    }
}

bool Votacao::votar(Votante& votante, int idOpcao) {
    if (status != "ATIVA" || !urna) {
        std::cerr << "ERRO: Votacao nao esta ATIVA ou Urna nao iniciada." << std::endl;
        return false;
    }
    
    return urna->votar(votante, idOpcao);
}

const std::vector<Opcao*>& Votacao::getOpcoes() const {
    return this->opcoes;
}

// --- Getters ---
Votante* Votacao::getVotante(const std::string& id) const {
    auto it = votantes.find(id);
    if (it != votantes.end()) {
        return it->second;
    }
    return nullptr;
}

const std::map<std::string, Votante*>& Votacao::getVotantes() const {
    return votantes;
}

std::string Votacao::getStatus() const {
    return status;
}

std::string Votacao::getTitulo() const {
    return titulo;
}

// --- Setters ---
// Implementação da nova função
void Votacao::setTitulo(const std::string& novoTitulo) {
    this->titulo = novoTitulo;
}