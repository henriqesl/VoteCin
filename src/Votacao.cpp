#include "Votacao.h"
#include "Urna.h" 
#include "Votante.h"
#include "Opcao.h"
#include <iostream>

// Inicializa o título, data e status
Votacao::Votacao(const std::string& titulo, const std::string& data) 
    : titulo(titulo), data(data), status("NAO_INICIADA") {}

// Adiciona um ponteiro de Opcao
void Votacao::adicionarOpcao(Opcao* o) {
    opcoes.push_back(o);
}

// Adiciona um ponteiro de Votante 
void Votacao::adicionarVotante(Votante* v) {
    // Usa o ID como chave do mapa
    votantes[v->getId()] = v; 
}

// Limpa a lista de ponteiros
void Votacao::limparOpcoes() {
    opcoes.clear();
    // A Urna (se existir) fica inválida, precisa ser recriada
    urna.reset(nullptr); 
}

// Muda o status e CRIA a Urna
void Votacao::iniciarVotacao() {
    // Só pode iniciar se não estiver iniciada
    if (status == "NAO_INICIADA") {
        // Não pode iniciar sem opções
        if (opcoes.empty()) {
            std::cout << "[ERRO] Nao e possivel iniciar uma votacao sem opcoes. Adicione opcoes no menu Admin.\n";
            return;
        }
        // Cria a Urna, passando as opções válidas
        urna = std::make_unique<Urna>(opcoes); 
        status = "ATIVA";
        std::cout << "Votacao '" << titulo << "' (Data: " << data << ") INICIADA. Urna pronta." << std::endl;
    }
}

// Muda o status
void Votacao::encerrarVotacao() {
    if (status == "ATIVA") {
        status = "ENCERRADA";
        std::cout << "Votacao '" << titulo << "' ENCERRADA." << std::endl;
    }
}

// Delega a lógica do voto para a Urna
bool Votacao::votar(Votante& votante, int idOpcao) {
    // Verifica se a votação está ATIVA e se a Urna existe
    if (status != "ATIVA" || !urna) {
        std::cerr << "ERRO: Votacao nao esta ATIVA ou Urna nao iniciada." << std::endl;
        return false;
    }
    
    // Passa a responsabilidade para a Urna
    return urna->votar(votante, idOpcao);
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