#include "GerenciadorDados.h"
#include <fstream>   
#include <sstream>   
#include <iostream> 
#include <exception> 

// Função helper interna para quebrar uma string com vírgulas
std::vector<std::string> GerenciadorDados::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s); // Usa um stream de string
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Carrega o arquivo de Opções (template)
std::vector<Opcao> GerenciadorDados::carregarOpcoes(const std::string& nomeArquivo) {
    std::vector<Opcao> listaOpcoes;
    std::ifstream arquivo(nomeArquivo);
    std::string linha;

    if (!arquivo.is_open()) {
        std::cerr << "[AVISO] Nao foi possivel abrir o arquivo de opcoes: " << nomeArquivo << ". Um novo sera criado ao salvar." << std::endl;
        return listaOpcoes; // Retorna lista vazia
    }

    // Lê o arquivo linha por linha
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue; // Pula linhas vazias
        std::vector<std::string> campos = split(linha, ',');

        // Formato esperado: 'Nome,Descricao,ID'
        if (campos.size() == 3) {
            try {
                int id = std::stoi(campos[2]); // Converte o ID para número
                // Cria a Opcao e adiciona ao vetor
                listaOpcoes.emplace_back(id, campos[0], campos[1]);
            } catch (const std::exception& e) {
                std::cerr << "[AVISO] Linha invalida no arquivo de opcoes (ignorada): " << linha << std::endl;
            }
        } else {
            std::cerr << "[AVISO] Linha invalida no arquivo de opcoes (formato): " << linha << std::endl;
        }
    }
    return listaOpcoes;
}

// Carrega o arquivo de Votantes
std::vector<Votante> GerenciadorDados::carregarVotantes(const std::string& nomeArquivo) {
    std::vector<Votante> listaVotantes;
    std::ifstream arquivo(nomeArquivo);
    std::string linha;

    if (!arquivo.is_open()) {
        std::cerr << "[AVISO] Nao foi possivel abrir o arquivo de votantes: " << nomeArquivo << ". Um novo sera criado ao salvar." << std::endl;
        return listaVotantes; // Retorna lista vazia
    }

    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;
        std::vector<std::string> campos = split(linha, ',');

        // Formato esperado: 'Nome,ID'
        if (campos.size() == 2) {
            // Cria o Votante e adiciona ao vetor
            listaVotantes.emplace_back(campos[0], campos[1]);
        } else {
            std::cerr << "[AVISO] Linha invalida no arquivo de votantes (formato): " << linha << std::endl;
        }
    }
    return listaVotantes;
}

// Salva o arquivo de Opções (usado no autosave do Admin)
void GerenciadorDados::salvarOpcoes(const std::string& nomeArquivo, const std::vector<Opcao>& opcoes) {
    std::ofstream arquivo(nomeArquivo); // Abre o arquivo para escrita (sobrescreve)
    if (!arquivo.is_open()) {
        std::cerr << "[ERRO CRÍTICO] Nao foi possivel salvar o arquivo de opcoes: " << nomeArquivo << std::endl;
        return;
    }
    
    // Itera sobre o vetor de Opcoes e escreve no formato CSV
    for (const auto& o : opcoes) {
        arquivo << o.getNome() << ","
                << o.getDescricao() << ","
                << o.getIdNumerico() << "\n";
    }
}

// Salva o arquivo de Votantes (usado no autosave da votação)
void GerenciadorDados::salvarVotantes(const std::string& nomeArquivo, const std::vector<Votante>& votantes) {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "[ERRO CRÍTICO] Nao foi possivel salvar o arquivo de votantes: " << nomeArquivo << std::endl;
        return;
    }

    // Itera sobre o vetor de Votantes e escreve no formato CSV
    for (const auto& v : votantes) {
        arquivo << v.getNome() << ","
                << v.getId() << "\n";
        // NOTA: O status 'jaVotou' não é salvo
    }
}