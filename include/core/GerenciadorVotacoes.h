#ifndef GERENCIADORVOTACOES_H
#define GERENCIADORVOTACOES_H

#include "Votacao.h"   
#include "Relatorio.h"
#include "Votante.h"   
#include "Opcao.h"     
#include <string>
#include <vector>

// Classe principal que orquestra todo o sistema.
// É a "dona" dos vetores de dados (opcoes e votantes).
class GerenciadorVotacoes {
private:
    Votacao votacaoAtual; // A sessão de votação (controla o status)
    Relatorio relatorio;  // Objeto que gera o relatório
    
    // Vetores "donos" dos objetos
    std::vector<Opcao> opcoes;
    std::vector<Votante> votantes;

    // Caminho do template (ex: "opcoes_filmes.txt")
    std::string arquivoOpcoesAtual; 

    // Atualiza os ponteiros na votacaoAtual após CRUD
    void atualizarPonteirosOpcoes();

    // Funções de salvamento automático
    void autoSalvarOpcoes();
    void autoSalvarVotantes();

public:
    GerenciadorVotacoes(const std::string& tituloVotacao, const std::string& dataVotacao);

    // Carrega os dados dos .txt para os vetores
    void carregarDadosIniciais(const std::string& arquivoOpcoes);

    // --- Controle de Fluxo (Admin) ---
    void iniciarVotacao();
    void encerrarVotacao();
    void gerarResultados();
    
    // --- Getters de Status (UI) ---
    std::string getStatus() const;
    std::string getTituloVotacao() const;

    // --- Lógica de Votação (UI) ---
    void executarVotacao(Votante& votante, int idOpcao); 
    
    // --- Helpers de Votante (Votação Aberta) ---
    Votante* getVotantePorNome(const std::string& nome);
    Votante* criarNovoVotante(const std::string& nome); // Cria e salva votante

    // --- Admin CRUD (UI) ---
    void adicionarNovaOpcao(int idNum, const std::string& nome, const std::string& descricao);
    void listarOpcoesAdmin() const;
    void removerOpcao(int idNum);
    
    // Lista opções formatadas para o votante
    void listarOpcoesParaVotacao() const;
};

#endif