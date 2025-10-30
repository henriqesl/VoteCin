#ifndef SISTEMAVOTACAO_H
#define SISTEMAVOTACAO_H

#include "Eleicao.h"
#include "Relatorio.h"
#include "Eleitor.h"
#include "Candidato.h"
#include <string>
#include <vector>

class SistemaVotacao {
private:
    Eleicao eleicaoAtual; // Composicao: Gerencia o ciclo eleitoral
    Relatorio relatorio;  // Composicao: Usa a funcionalidade de relatorio
    
    // Armazena os objetos reais (Eleitor e Candidato)
    // Os ponteiros são usados na Eleicao
    std::vector<Candidato> candidatos;
    std::vector<Eleitor> eleitores;

public:
    // Construtor: Inicia o sistema com a data da eleicao
    SistemaVotacao(const std::string& dataEleicao);

    // Simulacao de carregamento de dados (prepara a Eleicao para a votacao)
    void carregarDadosIniciais();

    // Controle de fluxo principal (para a UI)
    void iniciarVotacao();
    void encerrarVotacao();
    void gerarResultados();
    
    // Metodo que a UI chamaria
    void executarVotacao(const std::string& tituloEleitor, int numeroCandidato);

    std::string getStatus() const;
};

#endif