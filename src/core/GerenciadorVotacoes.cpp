#include "core/GerenciadorVotacoes.h"
#include "data/GerenciadorDados.h"
#include "core/Votacao.h"
#include <iostream>
#include <limits> 
#include <algorithm>
#include <list>

// Construtor: Inicializa a Votacao com título e data
GerenciadorVotacoes::GerenciadorVotacoes(const std::string& tituloVotacao, const std::string& dataVotacao)
    : votacaoAtual(tituloVotacao, dataVotacao) {
    // Relatorio é inicializado por padrão
}

// Carrega os dados dos arquivos .txt para os vetores da classe
void GerenciadorVotacoes::carregarDadosIniciais(const std::string& arquivoOpcoes) {
    this->arquivoOpcoesAtual = arquivoOpcoes; // Lembra qual template foi carregado
    
    opcoes = GerenciadorDados::carregarOpcoes(arquivoOpcoesAtual);
    votantes = GerenciadorDados::carregarVotantes("../resources/votantes.txt");
    
    // Preenche a sessão de votação (votacaoAtual) com os dados carregados
    atualizarPonteirosOpcoes();
    for (Votante& v : votantes) {
        votacaoAtual.adicionarVotante(&v);
    }

    std::cout << "Dados carregados: " << opcoes.size()
              << " Opcoes e " << votantes.size() << " Votantes (do historico)." << std::endl;
}

// --- Funções de Controle de Votação (delegam para Votacao) ---
bool GerenciadorVotacoes::iniciarVotacao() {
    return votacaoAtual.iniciarVotacao();
}

void GerenciadorVotacoes::encerrarVotacao() {
    votacaoAtual.encerrarVotacao();
}

// Gera o relatório final 
void GerenciadorVotacoes::gerarResultados() {
    // Força o encerramento somente se a votação ainda estiver ativa
    if (votacaoAtual.getStatus() == "ATIVA") {
        std::cout << "[AVISO] Encerrando votacao automaticamente para gerar o relatorio.\n";
        encerrarVotacao();
    }
    // Direciona a impressão para a classe Relatorio
    relatorio.gerarRelatorio(votacaoAtual);
}

void GerenciadorVotacoes::gerarResultadosParciais() const {
    relatorio.gerarRelatorio(votacaoAtual);
}

std::string GerenciadorVotacoes::getStatus() const {
    return votacaoAtual.getStatus();
}

std::string GerenciadorVotacoes::getTituloVotacao() const {
    return votacaoAtual.getTitulo();
}

void GerenciadorVotacoes::setTituloVotacao(const std::string& novoTitulo) {
    votacaoAtual.setTitulo(novoTitulo);
    std::cout << "Titulo da votacao alterado para: " << novoTitulo << std::endl;
}

// --- Lógica de Votação ---
void GerenciadorVotacoes::executarVotacao(Votante& votante, int idOpcao) {
    // Tentativa de voto
    bool sucesso = votacaoAtual.votar(votante, idOpcao);
    
    // Se o voto foi registrado (válido, nulo ou branco), salva o status do votante
    if (sucesso) {
        autoSalvarVotantes();
    }
}
    
// --- Helpers de Votante ---
Votante* GerenciadorVotacoes::getVotantePorNome(const std::string& nome) {
    // Procura um votante existente no vetor 'donos'
    for (Votante& v : votantes) {
        if (v.getNome() == nome) {
            return &v; 
        }
    }
    return nullptr; // Não encontrado
}

Votante* GerenciadorVotacoes::criarNovoVotante(const std::string& nome) {
    // Adiciona um novo Votante ao vetor 'donos'
    votantes.emplace_back(nome, nome); // Nome = ID
    
    Votante* novoVotantePtr = &votantes.back();
    votacaoAtual.adicionarVotante(novoVotantePtr); // Adiciona na sessão atual
    
    autoSalvarVotantes(); // Salva o novo votante no .txt
    
    return novoVotantePtr;
}

// --- Funções Admin ---

// CREATE 
void GerenciadorVotacoes::adicionarNovaOpcao(int idNum, const std::string& nome, const std::string& descricao) {
    // Não pode adicionar se a votação estiver ATIVA
    if (getStatus() != "NAO_INICIADA") {
        std::cout << "[ERRO] Nao e possivel adicionar opcoes apos a votacao ser iniciada.\n";
        return;
    }
    
    // ID não pode ser duplicado
    for(const auto& op : opcoes) {
        if(op.getIdNumerico() == idNum) {
            std::cout << "[ERRO] Ja existe uma opcao com o numero " << idNum << ". Operacao cancelada.\n";
            return;
        }
    }

    opcoes.emplace_back(idNum, nome, descricao);                                   // Adiciona ao vetor 'donos'
    atualizarPonteirosOpcoes();                                                    // Atualiza a sessão
    std::cout << "Opcao '" << nome << "' (Numero " << idNum << ") adicionada.\n";
    
    autoSalvarOpcoes();                                                            // Salva a mudança no .txt
}

// READ
void GerenciadorVotacoes::listarOpcoesAdmin() const {
    if (opcoes.empty()) {
        std::cout << "[INFO] Nenhuma opcao cadastrada.\n";
        return;
    }
    // Itera e pede para cada Opcao se imprimir
    for (const auto& o : opcoes) {
        o.imprimirDetalhes();
        std::cout << "--------------------\n";
    }
}

// DELETE
void GerenciadorVotacoes::removerOpcao(int idNum) {

     if (getStatus() != "NAO_INICIADA") {
        std::cout << "[ERRO] Nao e possivel remover opcoes apos a votacao ser iniciada.\n";
        return;
    }
    
    // Encontra a opção no vetor 'donos' pelo ID
    auto it = std::find_if(opcoes.begin(), opcoes.end(), 
                           [idNum](const Opcao& o) { return o.getIdNumerico() == idNum; });

    if (it != opcoes.end()) {
        std::cout << "Opcao '" << it->getNome() << "' removida.\n";
        opcoes.erase(it);                                    
        atualizarPonteirosOpcoes(); 
        autoSalvarOpcoes();                     // Salva a remoção no .txt
    } else {
        std::cout << "[ERRO] Opcao com numero " << idNum << " nao encontrada.\n";
    }
}

// --- Funções de Autosave (Privadas) ---

void GerenciadorVotacoes::autoSalvarOpcoes() {
    // VAZIO
}

void GerenciadorVotacoes::autoSalvarVotantes() {
    GerenciadorDados::salvarVotantes("../resources/votantes.txt", votantes);
    std::cout << "[AUTOSAVE] Log de votantes foi salvo em votantes.txt.\n";
}

// Helper interno para garantir que Votacao use os ponteiros corretos
void GerenciadorVotacoes::atualizarPonteirosOpcoes() {
    votacaoAtual.limparOpcoes(); // Limpa a lista de ponteiros antiga
    // Preenche com os ponteiros do vetor 'donos' (opcoes)
    for (Opcao& o : opcoes) {
        votacaoAtual.adicionarOpcao(&o);
    }
}

// --- Função de Votação (UI) ---
void GerenciadorVotacoes::listarOpcoesParaVotacao() const {
    // Pede à Votacao a lista de ponteiros de opções ativas
    const auto& opcoesList = votacaoAtual.getOpcoes();

    if (opcoesList.empty()) {
        std::cout << "[INFO] Nenhuma opcao registrada para esta votacao.\n";
        return;
    }

    std::cout << "--- OPCOES DISPONIVEIS (" << votacaoAtual.getTitulo() << ") ---\n";
    // Itera sobre os ponteiros e imprime nome/descrição
    for (const Opcao* o : opcoesList) {
        std::cout << "  [Numero: " << o->getIdNumerico() << "] "
                  << o->getNome() << " (" << o->getDescricao() << ")\n";
    }
}