#include "SistemaVotacao.h"
#include "GerenciadorDados.h"
#include <iostream>

SistemaVotacao::SistemaVotacao(const std::string& dataEleicao)
    : eleicaoAtual(dataEleicao) {
    // Relatorio é inicializado por padrão
}

void SistemaVotacao::carregarDadosIniciais() {
    std::cout << "\n--- Preparacao da Eleicao ---" << std::endl;
    
    // Carrega candidatos no arquivo externo
    candidatos = GerenciadorDados::carregarCandidatos("candidatos.txt");
    
    // Passar ponteiros para a Eleicao
    std::cout << "--- Detalhes dos candidatos ---" << std::endl;
    for (Candidato& c : candidatos) {
        eleicaoAtual.adicionarCandidato(&c);

        Pessoa* p = &c; // Ponteiro da classe base
        p->imprimirDetalhes(); 
        std::cout << "--------------------------" << std::endl;
    }

    // Carregar eleitores no arquivo externo
    eleitores = GerenciadorDados::carregarEleitores("eleitores.txt");

    // Passar ponteiros para a Eleicao
    std::cout << "\n--- Detalhes dos Eleitores (Teste Polimorfismo) ---" << std::endl;
    for (Eleitor& e : eleitores) {
        eleicaoAtual.adicionarEleitor(&e);

        Pessoa* p = &e;
        p->imprimirDetalhes(); 
        std::cout << "--------------------------" << std::endl;
    }
    
    std::cout << "\nDados carregados: " << candidatos.size() 
              << " Candidatos e " << eleitores.size() << " Eleitores." << std::endl;
}

void SistemaVotacao::iniciarVotacao() {
    eleicaoAtual.iniciarEleicao();
}

void SistemaVotacao::encerrarVotacao() {
    eleicaoAtual.encerrarVotacao();
}

void SistemaVotacao::executarVotacao(const std::string& tituloEleitor, int numeroCandidato) {
    eleicaoAtual.votar(tituloEleitor, numeroCandidato);
}

void SistemaVotacao::gerarResultados() {
    // Chama encerrar caso não tenha sido feito antes
    if (eleicaoAtual.getStatus() == "ATIVA") {
        encerrarVotacao();
    }
    relatorio.gerarRelatorio(eleicaoAtual); 
}

std::string SistemaVotacao::getStatus() const {
    // Delega a chamada para a classe Eleicao interna
    return eleicaoAtual.getStatus();
}