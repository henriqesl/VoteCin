#ifndef GERENCIADORDADOS_H
#define GERENCIADORDADOS_H

#include <vector>
#include <string>
#include "Candidato.h"
#include "Eleitor.h"

class GerenciadorDados {
public:
    // Le o arquivo de candidatos e preenche um vetor de Candidato

    static std::vector<Candidato> carregarCandidatos(const std::string& nomeArquivo);

    // Le o arquivo de eleitores e preenche um vetor de Eleitor

    static std::vector<Eleitor> carregarEleitores(const std::string& nomeArquivo);
    
private:
    // Funcao auxiliar para dividir a linha por virgula
    static std::vector<std::string> split(const std::string& s, char delimiter);
};

#endif