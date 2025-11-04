#ifndef VOTECIN_TELAADMIN_H
#define VOTECIN_TELAADMIN_H

#include "Tela.h" // Classe base

// Tela do painel de administração (CRUD, Iniciar, Encerrar)
class TelaAdmin : public Tela {
public:
    using Tela::Tela; // Herda o construtor
    
    // Mostra o menu de admin em loop
    virtual Tela* proximaTela() override;

private:
    // Funções helper da UI para organizar o código
    void fluxoAdicionarOpcao();
    void fluxoRemoverOpcao();
    void fluxoEncerrarEGerarRelatorio();
};

#endif //VOTECIN_TELAADMIN_H