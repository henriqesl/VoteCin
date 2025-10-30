#include "Relatorio.h"
#include <iostream>
#include <algorithm> // Para std::sort

void Relatorio::gerarRelatorio(const Eleicao& eleicao) const {
    if (eleicao.getStatus() != "ENCERRADA") {
        std::cout << "AVISO: A eleicao deve ser encerrada para um relatorio oficial." << std::endl;
        return;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "          RELATORIO DA ELEICAO          " << std::endl;
    std::cout << "========================================" << std::endl;

    gerarEstatisticas(eleicao);
    apurarVencedor(eleicao.getCandidatos());

    std::cout << "========================================\n" << std::endl;
}

void Relatorio::gerarEstatisticas(const Eleicao& eleicao) const {
    const auto& eleitoresMap = eleicao.getEleitores(); 
    int totalEleitores = eleitoresMap.size();
    int eleitoresVotantes = 0;

    // Itera sobre o mapa de eleitores (Agregação) para verificar o estado de voto
    for (const auto& pair : eleitoresMap) {
        if (pair.second->getJaVotou()) {
            eleitoresVotantes++;
        }
    }
    
    int totalVotos = 0;
    if (eleicao.getUrna()) {
        totalVotos = eleicao.getUrna()->getVotosRegistrados().size();
    }

    std::cout << "Estatisticas Gerais:" << std::endl;
    std::cout << "- Eleitores Cadastrados: " << totalEleitores << std::endl;
    std::cout << "- Eleitores Votantes: " << eleitoresVotantes << std::endl; 
    std::cout << "- Total de Votos na Urna: " << totalVotos << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void Relatorio::apurarVencedor(const std::vector<Candidato*>& candidatos) const {
    if (candidatos.empty()) return;
    
    std::vector<Candidato*> candidatosOrdenados = candidatos;
    
    // 1. Ordena apenas por votos (decrescente)
    std::sort(candidatosOrdenados.begin(), candidatosOrdenados.end(), 
        [](Candidato* a, Candidato* b) {
            return a->getTotalVotos() > b->getTotalVotos(); 
        });

    Candidato* vencedor = candidatosOrdenados[0]; // O primeiro da lista é o que tem mais votos

    // 2. VERIFICAÇÃO DE EMPATE
    bool houveEmpate = false;
    // Precisa de pelo menos 2 candidatos para ter empate
    if (candidatosOrdenados.size() >= 2) {
        // Compara os votos do 1º e do 2º colocado.
        Candidato* segundoColocado = candidatosOrdenados[1];
        
        if (vencedor->getTotalVotos() > 0 && 
            vencedor->getTotalVotos() == segundoColocado->getTotalVotos()) {
            
            houveEmpate = true;
        }
    }
    
    // 3. Imprime os resultados por candidato
    std::cout << "Resultados por Candidato:" << std::endl;
    
    for (Candidato* c : candidatosOrdenados) {
        std::cout << "  [#" << c->getNumeroCandidato() << "] " << c->getNome() 
                  << " - Votos: " << c->getTotalVotos() << std::endl;
    }

    std::cout << std::endl;

    // 4. Imprime o Vencedor ou o Empate
    if (houveEmpate) {
        // Encontra todos os empatados para imprimir
        std::cout << ">>> HOUVE EMPATE NA LIDERANCA COM " << vencedor->getTotalVotos() << " VOTOS ENTRE:" << std::endl;
        for (Candidato* c : candidatosOrdenados) {
             if (c->getTotalVotos() == vencedor->getTotalVotos()) {
                 std::cout << "   - " << c->getNome() << " (" << c->getPartido() << ")" << std::endl;
             } else {
                 break; 
             }
        }
    } else if (vencedor->getTotalVotos() == 0 && candidatosOrdenados.size() > 0) {
        // Se houver candidatos, mas zero voto, declara "voto nulo" ou similar
        std::cout << "AVISO: Nenhum voto foi registrado para os candidatos. Eleicao nula." << std::endl;
    } else {
        // Declara o vencedor único
        std::cout << "VENCEDOR(A): " << vencedor->getNome() 
                  << " (" << vencedor->getPartido() << ") com " 
                  << vencedor->getTotalVotos() << " votos!" << std::endl;
    }
}