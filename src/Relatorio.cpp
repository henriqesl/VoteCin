#include "Relatorio.h"
#include "Opcao.h"
#include "Votante.h"
#include "Urna.h"
#include <iostream>
#include <algorithm>

void Relatorio::gerarRelatorio(const Votacao& votacao) const {
    // Checa se a votação já foi encerrada
    if (votacao.getStatus() != "ENCERRADA") {
        std::cout << "AVISO: Gerando relatorio parcial. A votacao ainda esta ATIVA." << std::endl;
        // Permite gerar relatórios parciais 
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "      RELATORIO DA VOTACAO: " << votacao.getTitulo() << std::endl;
    std::cout << "========================================" << std::endl;

    // Chama as funções helper internas para imprimir cada seção
    gerarEstatisticas(votacao);
    apurarVencedor(votacao.getOpcoes());
    listarParticipantes(votacao); // Lista quem votou

    std::cout << "========================================\n" << std::endl;
}

// Imprime as estatísticas gerais
void Relatorio::gerarEstatisticas(const Votacao& votacao) const {
    const auto& votantesMap = votacao.getVotantes(); 
    int totalVotantesCadastrados = votantesMap.size(); // Total no sistema
    int votantesQueVotaram = 0;

    // Conta a quantidade de votantes que 'jaVotaram'
    for (const auto& pair : votantesMap) {
        if (pair.second->getJaVotou()) {
            votantesQueVotaram++;
        }
    }
    
    int totalVotosUrna = 0;
    int votosNulos = 0;
    int votosBrancos = 0;

    // Pega os dados da Urna (se ela já tiver sido inicializada)
    if (votacao.getUrna()) { 
        Urna* urna = votacao.getUrna();
        totalVotosUrna = urna->getVotosRegistrados().size();
        votosNulos = urna->getVotosNulos();
        votosBrancos = urna->getVotosBrancos();
    } else {
        std::cout << "[INFO] A votacao nao foi iniciada, estatisticas de votos nao disponiveis." << std::endl;
    }

    std::cout << "Estatisticas Gerais:" << std::endl;
    std::cout << "- Votantes Registrados (Total): " << totalVotantesCadastrados << std::endl;
    std::cout << "- Votantes que Votaram (Nesta Sessao): " << votantesQueVotaram << std::endl; 
    std::cout << "- Total de Votos na Urna (Nesta Sessao): " << totalVotosUrna << std::endl;
    std::cout << "- Votos Nulos: " << votosNulos << std::endl;
    std::cout << "- Votos Brancos: " << votosBrancos << std::endl;
}

// Calcula e imprime o vencedor
void Relatorio::apurarVencedor(const std::vector<Opcao*>& opcoes) const {
    if (opcoes.empty()) {
        std::cout << "Nao ha opcoes cadastradas para apurar." << std::endl;
        return;
    }
    
    // Cria uma cópia do vetor de ponteiros para ordenar
    std::vector<Opcao*> opcoesOrdenadas = opcoes;
    
    // Ordena o vetor de maneira decrescente
    std::sort(opcoesOrdenadas.begin(), opcoesOrdenadas.end(), 
        [](Opcao* a, Opcao* b) {
            return a->getTotalVotos() > b->getTotalVotos(); // Mais votos primeiro
        });

    Opcao* vencedor = opcoesOrdenadas[0]; // O primeiro da lista

    // Verificação de empate
    bool houveEmpate = false;
    if (opcoesOrdenadas.size() >= 2) {
        Opcao* segundoColocado = opcoesOrdenadas[1];
        if (vencedor->getTotalVotos() > 0 && 
            vencedor->getTotalVotos() == segundoColocado->getTotalVotos()) {
            houveEmpate = true;
        }
    }
    
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Resultados por Opcao:" << std::endl;
    
    // Imprime o placar
    for (Opcao* o : opcoesOrdenadas) {
        std::cout << "  [#" << o->getIdNumerico() << "] " << o->getNome() 
                  << " (" << o->getDescricao() << ")"
                  << " - Votos: " << o->getTotalVotos() << std::endl;
    }

    std::cout << std::endl;

    // Imprime o resultado
    if (houveEmpate) {
        std::cout << ">>> HOUVE EMPATE NA LIDERANCA COM " << vencedor->getTotalVotos() << " VOTOS ENTRE:" << std::endl;
        // Lista os empates
        for (Opcao* o : opcoesOrdenadas) {
             if (o->getTotalVotos() == vencedor->getTotalVotos()) {
                 std::cout << "   - " << o->getNome() << " (" << o->getDescricao() << ")" << std::endl;
             } else {
                 break;
             }
        }
    } else if (vencedor->getTotalVotos() == 0) {
        std::cout << "AVISO: Nenhum voto foi registrado para as opcoes." << std::endl;
    } else {
        std::cout << "VENCEDOR(A): " << vencedor->getNome() 
                  << " (" << vencedor->getDescricao() << ") com " 
                  << vencedor->getTotalVotos() << " votos!" << std::endl;
    }
}

// Lista quem participou
void Relatorio::listarParticipantes(const Votacao& votacao) const {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Lista de Participantes (que votaram):" << std::endl;
    
    const auto& votantesMap = votacao.getVotantes(); 

    if (votantesMap.empty()) {
        std::cout << "- Nenhum votante registrado.\n";
        return;
    }

    int count = 0;
    // Itera sobre o mapa (pair.second é o Votante*)
    for (const auto& pair : votantesMap) {
        // Lista apenas quem tem o status 'jaVotou'
        if (pair.second->getJaVotou()) {
            std::cout << "- " << pair.second->getNome() << "\n";
            count++;
        }
    }
    
    if (count == 0) {
        std::cout << "- Nenhum participante votou nesta sessao.\n";
    }
}