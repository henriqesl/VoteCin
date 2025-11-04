#ifndef VOTECIN_UTILUI_H
#define VOTECIN_UTILUI_H

#include <string>

// Funções utilitárias da Interface
namespace UtilsUI {
    
    void limparTela();

    // Lê uma linha e converte para int (retorna -1 em erro)
    int lerOpcaoNumerica();

    // Garante que o usuário não digite uma string vazia
    std::string lerStringNaoVazia(const std::string& prompt);

    // Mostra a tela inicial de seleção de template
    std::string selecionarArquivoDeOpcoes();

    // Pausa
    void pausar();

    bool loginAdmin();
}

#endif //VOTECIN_UTILUI_H