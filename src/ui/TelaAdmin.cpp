#include "../../include/ui/TelaAdmin.h"
#include "../../include/ui/TelaPrincipal.h" 
#include "../../include/ui/UtilsUI.h"

#include <iostream>

// Método principal da TelaAdmin: loop do menu de admin
Tela* TelaAdmin::proximaTela() {
    int opcao = 0;
    do {
        UtilsUI::limparTela();
        std::cout << "\n--- PAINEL DO ADMINISTRADOR ---\n";
        std::cout << "Votacao: " << sistema.getTituloVotacao() << "\n";
        std::cout << "Status: " << sistema.getStatus() << "\n";
        std::cout << "---------------------------------\n";
        std::cout << "1. Adicionar Nova Opcao (Salva Automatico)\n";
        std::cout << "2. Listar Opcoes Atuais\n";
        std::cout << "3. Remover Opcao (Salva Automatico)\n";
        std::cout << "---------------------------------\n";
        std::cout << "4. Iniciar Votacao (Abre para o publico)\n";
        std::cout << "5. Encerrar Votacao e Gerar Relatorio\n";
        std::cout << "6. Voltar ao Menu Principal\n";
        std::cout << "Escolha uma opcao: " << std::flush;

        opcao = UtilsUI::lerOpcaoNumerica();
        bool devePausar = true; 

        switch(opcao) {
            case 1:
                fluxoAdicionarOpcao(); 
                break;
            case 2:
                UtilsUI::limparTela();
                std::cout << "--- LISTA DE OPCOES ATUAIS ---\n";
                sistema.listarOpcoesAdmin(); 
                break;
            case 3:
                fluxoRemoverOpcao(); 
                break;
            case 4:
                sistema.iniciarVotacao(); 
                break;
            case 5: 
                fluxoEncerrarEGerarRelatorio(); 
                devePausar = false; 
                break;
            case 6: 
                std::cout << "A retornar ao menu principal...\n";
                devePausar = false;
                break;
            case -1:
            default:
                std::cout << "Opcao invalida.\n" << std::flush;
                break;
        }

        if (devePausar) {
             UtilsUI::pausar();
        }

    } while (opcao != 6); // Continua no loop até o admin sair

    // Retorna para a Tela Principal
    return new TelaPrincipal(sistema);
}

// LOGIN ADMIN

// Fluxo da UI para adicionar opção
void TelaAdmin::fluxoAdicionarOpcao() {
    UtilsUI::limparTela();
    std::cout << "--- Adicionar Nova Opcao Votavel ---\n";
    
    // UI coleta os dados e envia para o gerenciador
    std::string nome = UtilsUI::lerStringNaoVazia("Nome (ex: 'O Poderoso Chefao'): ");
    std::string descricao = UtilsUI::lerStringNaoVazia("Descricao (ex: 'Filme de Mafia'): ");
    std::cout << "Numero para Votacao (ex: 10): " << std::flush;
    int idNum = UtilsUI::lerOpcaoNumerica();
    
    if (idNum == -1) {
            std::cout << "[ERRO] Numero invalido. Operacao cancelada.\n";
    } else {
            sistema.adicionarNovaOpcao(idNum, nome, descricao);
    }
}

// Fluxo da UI para remover opção
void TelaAdmin::fluxoRemoverOpcao() {
    UtilsUI::limparTela();
    std::cout << "--- Remover Opcao Votavel ---\n";
    sistema.listarOpcoesAdmin(); // Mostra a lista primeiro
    
    std::cout << "\nDigite o NUMERO da opcao que deseja remover: " << std::flush;
    int idNum = UtilsUI::lerOpcaoNumerica();
    
    if (idNum == -1) {
        std::cout << "[ERRO] Numero invalido. Operacao cancelada.\n";
    } else {
        // Verifica o ID
        sistema.removerOpcao(idNum);
    }
}

// Fluxo da UI para encerrar e mostrar o relatório
void TelaAdmin::fluxoEncerrarEGerarRelatorio() {
    // Checa o status antes de agir
    if (sistema.getStatus() == "NAO_INICIADA") {
        std::cout << "[AVISO] Votacao nem sequer foi iniciada.\n";
        return;
    }
    
    if (sistema.getStatus() == "ENCERRADA") {
        std::cout << "A votacao ja esta encerrada. Gerando relatorio novamente...\n";
    } else {
        sistema.encerrarVotacao(); 
    }
    
    UtilsUI::limparTela();
    std::cout << "--- VOTACAO ENCERRADA ---\n";
    sistema.gerarResultados(); 
    
    std::cout << "\n\nRelatorio gerado. Pressione ENTER para voltar...\n" << std::flush;
    std::cin.get(); // Pausa longa
}