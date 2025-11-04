#ifndef VOTECIN_TELA_H
#define VOTECIN_TELA_H

#include "core/GerenciadorVotacoes.h" 

// Classe base abstrata para todas as telas
class Tela {
public:
    // Construtor recebe o gerenciador
    Tela(GerenciadorVotacoes& sistema) : sistema(sistema) {}
    virtual ~Tela() = default;

    // Método principal: desenha a tela e retorna a PRÓXIMA tela
    virtual Tela* proximaTela() = 0; 

protected:
    // Referência para a camada de lógica
    GerenciadorVotacoes& sistema;
};

#endif //VOTECIN_TELA_H