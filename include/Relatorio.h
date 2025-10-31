#ifndef RELATORIO_H
#define RELATORIO_H

#include "Eleicao.h"
#include <iostream>

class Relatorio {
public:
    // Gera o relatorio consultando a Eleicao
    void gerarRelatorio(const Eleicao& eleicao) const;

private:
    // Funções internas, herdadas da eleição
    void apurarVencedor(const std::vector<Candidato*>& candidatos) const;
    void gerarEstatisticas(const Eleicao& eleicao) const;
};

#endif