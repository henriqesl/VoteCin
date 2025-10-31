#ifndef GERENCIADORDADOS_H
#define GERENCIADORDADOS_H

#include <vector>
#include <string>
#include "Candidato.h"
#include "Eleitor.h"

class GerenciadorDados {
public:
    // Lê o arquivo de candidatos e preenche um vetor dos Candidatos
    static std::vector<Candidato> carregarCandidatos(const std::string& nomeArquivo);

    // Lê o arquivo de eleitores e preenche um vetor dos Eleitores
    static std::vector<Eleitor> carregarEleitores(const std::string& nomeArquivo);
    
private:
    static std::vector<std::string> split(const std::string& s, char delimiter);
};

#endif