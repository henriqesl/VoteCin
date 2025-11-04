#ifndef VOTECIN_TELAPRINCIPAL_H
#define VOTECIN_TELAPRINCIPAL_H

#include "Tela.h" // Classe base

// Tela do menu principal (Admin, Votar, Sair)
class TelaPrincipal : public Tela {
public:
    using Tela::Tela; // Herda o construtor
    
    // Desenha o menu principal e decide a próxima tela
    virtual Tela* proximaTela() override;
};

#endif //VOTECIN_TELAPRINCIPAL_H