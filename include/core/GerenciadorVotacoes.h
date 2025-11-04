#ifndef GERENCIADORVOTACOES_H
#define GERENCIADORVOTACOES_H

#include "Votacao.h"   
#include "Relatorio.h"
#include "models/Votante.h"
#include "models/Opcao.h"     
#include <string>
#include <list>

// Classe principal que orquestra todo o sistema.
class GerenciadorVotacoes {
private:
    Votacao votacaoAtual; 
    Relatorio relatorio;  
    
    std::list<Opcao> opcoes;
    std::list<Votante> votantes;

    std::string arquivoOpcoesAtual; 

    void atualizarPonteirosOpcoes();
    void autoSalvarOpcoes();
    void autoSalvarVotantes();

public:
    GerenciadorVotacoes(const std::string& tituloVotacao, const std::string& dataVotacao);

    void carregarDadosIniciais(const std::string& arquivoOpcoes);

    // --- Controle de Fluxo (Admin) ---
    bool iniciarVotacao();
    void encerrarVotacao();
    void gerarResultados();
    void gerarResultadosParciais() const; 
    
    // --- Getters e Setters ---
    std::string getStatus() const;
    std::string getTituloVotacao() const;
    void setTituloVotacao(const std::string& novoTitulo); 

    // --- Lógica de Votação ---
    void executarVotacao(Votante& votante, int idOpcao); 
    
    // --- Helpers de Votante ---
    Votante* getVotantePorNome(const std::string& nome);
    Votante* criarNovoVotante(const std::string& nome);

    // --- Admin CRUD ---
    void adicionarNovaOpcao(int idNum, const std::string& nome, const std::string& descricao);
    void listarOpcoesAdmin() const;
    void removerOpcao(int idNum);
    
    void listarOpcoesParaVotacao() const;
};

#endif