#include "GerenciadorDados.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <exception> // Necessário para std::exception

// Função auxiliar para dividir a string por delimitador
std::vector<std::string> GerenciadorDados::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        // Limpar espaços em branco à esquerda/direita, se necessário
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<Candidato> GerenciadorDados::carregarCandidatos(const std::string& nomeArquivo) {
    std::vector<Candidato> listaCandidatos;
    std::ifstream arquivo(nomeArquivo);
    std::string linha;

    if (!arquivo.is_open()) {
        std::cerr << "[ERRO CRÍTICO] Nao foi possivel abrir o arquivo de candidatos: " << nomeArquivo << std::endl;
        return listaCandidatos;
    }

    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;

        std::vector<std::string> campos = split(linha, ',');

        if (campos.size() == 4) {
            try {
                // Converte o número do candidato de string para int
                int numero = std::stoi(campos[2]); 
                
                // Adiciona o novo candidato à lista
                listaCandidatos.emplace_back(
                    campos[0], // Nome
                    campos[1], // CPF
                    numero,    // Número
                    campos[3]  // Partido
                );
            } catch (const std::exception& e) {
                // Se std::stoi falhar (ex: texto em vez de número)
                std::cerr << "[AVISO] Linha invalida no arquivo de candidatos (ignorada): " << linha << std::endl;
            }
        } else {
            std::cerr << "[AVISO] Linha invalida no arquivo de candidatos (formato): " << linha << std::endl;
        }
    }
    return listaCandidatos;
}

std::vector<Eleitor> GerenciadorDados::carregarEleitores(const std::string& nomeArquivo) {
    std::vector<Eleitor> listaEleitores;
    std::ifstream arquivo(nomeArquivo);
    std::string linha;

    if (!arquivo.is_open()) {
        std::cerr << "[ERRO CRÍTICO] Nao foi possivel abrir o arquivo de eleitores: " << nomeArquivo << std::endl;
        return listaEleitores;
    }

    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;

        std::vector<std::string> campos = split(linha, ',');

        if (campos.size() == 5) {
            try {
                // Converte Seção e Zona de string para int
                int secao = std::stoi(campos[3]);
                int zona = std::stoi(campos[4]);
                
                // Adiciona o novo eleitor à lista
                listaEleitores.emplace_back(
                    campos[0], // Nome
                    campos[1], // CPF
                    campos[2], // Título
                    secao,     // Seção
                    zona       // Zona
                );
            } catch (const std::exception& e) {
                 // Se std::stoi falhar (ex: texto em vez de número)
                std::cerr << "[AVISO] Linha invalida no arquivo de eleitores (ignorada): " << linha << std::endl;
            }
        } else {
            std::cerr << "[AVISO] Linha invalida no arquivo de eleitores (formato): " << linha << std::endl;
        }
    }
    return listaEleitores;
}