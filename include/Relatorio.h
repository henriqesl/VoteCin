#ifndef RELATORIO_H
#define RELATORIO_H

#include "Votacao.h" 
#include <iostream>

// Classe utilitária que gera a impressão dos resultados
class Relatorio {
public:
    // Imprime o relatório completo (estatísticas, vencedor, participantes)
    void gerarRelatorio(const Votacao& votacao) const; 

private:
    // --- Funções helpers ---
    void apurarVencedor(const std::vector<Opcao*>& opcoes) const;
    void gerarEstatisticas(const Votacao& votacao) const;
    void listarParticipantes(const Votacao& votacao) const;
};

#endif