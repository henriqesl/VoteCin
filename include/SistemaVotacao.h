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
    Eleicao eleicaoAtual; // Ciclo eleitoral
    Relatorio relatorio;  // Funcionalidade de relatorio
    
    // Armazena os Eleitores e Candidatos
    std::vector<Candidato> candidatos;
    std::vector<Eleitor> eleitores;

public:
    // Inicia o sistema com a data da eleicao
    SistemaVotacao(const std::string& dataEleicao);

    // Carregamento de dados
    void carregarDadosIniciais();

    // Controle de fluxo principal (UI)
    void iniciarVotacao();
    void encerrarVotacao();
    void gerarResultados();
    
    // Metodo que a UI chamaria
    void executarVotacao(const std::string& tituloEleitor, int numeroCandidato);

    std::string getStatus() const;
};

#endif