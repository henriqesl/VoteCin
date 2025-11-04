#include "../../include/ui/TelaVotacao.h"
#include "../../include/ui/TelaPrincipal.h" // Para onde ela volta
#include "../../include/ui/UtilsUI.h"

#include <iostream>

// loop da sessão de votação
Tela* TelaVotacao::proximaTela() {
    
    std::string nomeVotante;
    // Loop infinito, só sai com o comando "SAIR"
    while (true) {
        UtilsUI::limparTela();
        std::cout << "--- SESSAO DE VOTACAO ATIVA ---\n";
        std::cout << "Votacao: " << sistema.getTituloVotacao() << "\n\n";

        // UI chama gerenciador para listar opções
        sistema.listarOpcoesParaVotacao(); 

        std::cout << "\n----------------------------------------\n";
        std::cout << "Digite o seu NOME para votar (ou 'SAIR' para voltar ao menu):\n> " << std::flush;
        std::getline(std::cin, nomeVotante);

        if (nomeVotante.empty()) continue; // Pede de novo se for vazio

        // Comando de saída do loop
        if (nomeVotante == "SAIR" || nomeVotante == "sair") {
            std::cout << "Voltando ao menu principal...\n" << std::flush;
            break; 
        }

        // UI chama gerenciador para obter ou criar o votante
        Votante* votante = sistema.getVotantePorNome(nomeVotante);

        if (votante == nullptr) {
            votante = sistema.criarNovoVotante(nomeVotante); // BLL (com autosave)
            std::cout << "Bem-vindo(a), " << nomeVotante << "! Registrando seu primeiro voto.\n";
        } else {
             std::cout << "Bem-vindo(a) de volta, " << votante->getNome() << ".\n";
        }

        // UI checa o estado do votante
        if (!votante->podeVotar()) {
            std::cout << "[AVISO] Voce (" << votante->getNome() << ") ja votou nesta votacao.\n" << std::flush;
        } else {
            // UI coleta o voto
            std::cout << "\nDigite o NUMERO da sua opcao (ou 99 para Branco): " << std::flush;
            int idOpcao = UtilsUI::lerOpcaoNumerica(); 

            if (idOpcao == -1) {
                std::cout << "[ERRO] Numero da opcao invalido.\n";
            } else {
                // UI chama o gerenciador para processar o voto
                sistema.executarVotacao(*votante, idOpcao); 
            }
        }
        
        UtilsUI::pausar();
    }

    // Retorna para a Tela Principal
    return new TelaPrincipal(sistema);
}