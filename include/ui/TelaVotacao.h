#ifndef VOTECIN_TELAVOTACAO_H
#define VOTECIN_TELAVOTACAO_H

#include "Tela.h" // Classe base

// Tela onde a votação aberta (loop de votantes) acontece
class TelaVotacao : public Tela {
public:
    using Tela::Tela; // Herda o construtor
    
    // Inicia o loop da sessão de votação
    virtual Tela* proximaTela() override;
};

#endif //VOTECIN_TELAVOTACAO_H