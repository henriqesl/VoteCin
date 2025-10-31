#include "SistemaVotacao.h"
#include "GerenciadorDados.h"
#include <iostream>

SistemaVotacao::SistemaVotacao(const std::string& dataEleicao)
    : eleicaoAtual(dataEleicao) {
    // Relatorio é inicializado por padrão
}

void SistemaVotacao::carregarDadosIniciais() {
    std::cout << "\n--- Preparacao da Eleicao ---" << std::endl;
    
    // 1. CARREGAR CANDIDATOS DO ARQUIVO EXTERNO
    candidatos = GerenciadorDados::carregarCandidatos("candidatos.txt");
    
    // 2. Passar ponteiros para a Eleicao (Agregação)
    std::cout << "--- Detalhes dos candidatos ---" << std::endl;
    for (Candidato& c : candidatos) {
        eleicaoAtual.adicionarCandidato(&c);

        Pessoa* p = &c; // Ponteiro da classe base
        p->imprimirDetalhes(); // Chama a função de Candidato (Candidato::imprimirDetalhes())
        std::cout << "--------------------------" << std::endl;
    }

    // 3. CARREGAR ELEITORES DO ARQUIVO EXTERNO
    eleitores = GerenciadorDados::carregarEleitores("eleitores.txt");

    // 4. Passar ponteiros para a Eleicao (Agregação)
    for (Eleitor& e : eleitores) {
        eleicaoAtual.adicionarEleitor(&e);
    }
    
    std::cout << "Dados carregados: " << candidatos.size() 
              << " Candidatos e " << eleitores.size() << " Eleitores." << std::endl;
}

void SistemaVotacao::iniciarVotacao() {
    eleicaoAtual.iniciarEleicao();
}

void SistemaVotacao::encerrarVotacao() {
    eleicaoAtual.encerrarEleicao();
}

void SistemaVotacao::executarVotacao(const std::string& tituloEleitor, int numeroCandidato) {
    // Abstração: O Sistema apenas chama o método votar da Eleicao.
    eleicaoAtual.votar(tituloEleitor, numeroCandidato);
}

void SistemaVotacao::gerarResultados() {
    // Chama encerrar caso não tenha sido feito antes
    if (eleicaoAtual.getStatus() == "ATIVA") {
        encerrarVotacao();
    }
    // Abstração: Chama o método gerarRelatorio, delegando a lógica de apuração.
    relatorio.gerarRelatorio(eleicaoAtual); 
}

std::string SistemaVotacao::getStatus() const {
    // Delega a chamada para a classe Eleicao interna
    return eleicaoAtual.getStatus();
}