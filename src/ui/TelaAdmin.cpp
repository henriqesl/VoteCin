#include "ui/TelaAdmin.h"
#include "ui/TelaPrincipal.h"
#include "ui/TelaVotacao.h"
#include "ui/UtilsUI.h"

#include <iostream>
#include <thread> 
#include <chrono>

// Loop do menu de admin 
Tela* TelaAdmin::proximaTela() {
    int opcao = 0;
    
    // Este loop roda até o admin escolher "Voltar" (opção 8)
    do {
        UtilsUI::limparTela();
        
        // Pega o status ATUAL da votação para modularizar o menu
        std::string status = sistema.getStatus();

        std::cout << "\n--- PAINEL DO ADMINISTRADOR ---\n";
        std::cout << "Votacao: " << sistema.getTituloVotacao() << "\n";
        std::cout << "Status: " << status << "\n";
        std::cout << "---------------------------------\n";

        // Mostra opções de acordo com o status
        
        if (status == "NAO_INICIADA") {
            // Módulo "Antes de Iniciar"
            std::cout << "1. Adicionar Nova Opcao\n";
            std::cout << "2. Listar Opcoes Atuais\n";
            std::cout << "3. Remover Opcao \n";
            std::cout << "4. Iniciar Votacao [Abre para o publico]\n";
            std::cout << "5. Encerrar Votacao [BLOQUEADO]\n";
            std::cout << "6. Ver Resultados [BLOQUEADO]\n"; 
            std::cout << "7. Alterar Titulo da Votacao\n";
        } else if (status == "ATIVA") {
            // Módulo "Durante a Votação"
            std::cout << "1. Adicionar Nova Opcao [BLOQUEADO]\n";
            std::cout << "2. Listar Opcoes Atuais\n";
            std::cout << "3. Remover Opcao [BLOQUEADO]\n";
            std::cout << "4. Iniciar Votacao [JA INICIADA]\n";
            std::cout << "5. Encerrar Votacao e Gerar Relatorio Final\n";
            std::cout << "6. Ver Resultados Parciais\n"; 
            std::cout << "7. Alterar Titulo da Votacao [BLOQUEADO]\n";
        } else { // "ENCERRADA"
            // Módulo "Após Encerrar"
            std::cout << "1. Adicionar Nova Opcao [BLOQUEADO]\n";
            std::cout << "2. Listar Opcoes Atuais\n";
            std::cout << "3. Remover Opcao [BLOQUEADO]\n";
            std::cout << "4. Iniciar Votacao [BLOQUEADO]\n";
            std::cout << "5. Gerar Relatorio Final [JA ENCERRADA]\n";
            std::cout << "6. Ver Relatorio Final [JA ENCERRADA]\n"; 
            std::cout << "7. Alterar Titulo da Votacao [BLOQUEADO]\n";
        }

        std::cout << "---------------------------------\n";
        std::cout << "8. Voltar ao Menu Principal\n"; 
        std::cout << "Escolha uma opcao: " << std::flush;

        opcao = UtilsUI::lerOpcaoNumerica();
        bool devePausar = true; // Pausa a tela por padrão

        // Re-checamos o status aqui para garantir a lógica da AÇÃO
        status = sistema.getStatus();

        switch(opcao) {
            case 1: // CREATE (Adicionar)
                if (status == "NAO_INICIADA") {
                    fluxoAdicionarOpcao();
                } else {
                    std::cout << "[ERRO] Nao e possivel adicionar opcoes apos a votacao ser iniciada.\n" << std::flush;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    devePausar = false;
                }
                break;

            case 2: // READ (Listar)
                // Sempre disponível
                UtilsUI::limparTela();
                std::cout << "--- LISTA DE OPCOES ATUAIS ---\n";
                sistema.listarOpcoesAdmin(); 
                break;

            case 3: // DELETE (Remover)
                if (status == "NAO_INICIADA") {
                    fluxoRemoverOpcao();
                } else {
                    std::cout << "[ERRO] Nao e possivel remover opcoes apos a votacao ser iniciada.\n" << std::flush;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    devePausar = false;
                }
                break;

            case 4: { // INICIAR
                if (status == "NAO_INICIADA") {
                    bool sucesso = sistema.iniciarVotacao(); 
                    if (sucesso) {
                        // Se teve sucesso, faz a transição de tela
                        std::cout << "Votacao iniciada! Redirecionando para a tela de votacao...\n";
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        return new TelaVotacao(sistema); 
                    }
                } else {
                    std::cout << "[AVISO] A votacao ja foi iniciada ou encerrada.\n";
                }
                devePausar = true;
                break;
            };

            case 5: // ENCERRAR E RELATÓRIO
                 if (status == "NAO_INICIADA") {
                     std::cout << "[AVISO] A votacao nem sequer foi iniciada.\n";
                 } else {
                    // Se estiver ATIVA, encerra. Se já estiver ENCERRADA, só mostra o relatório.
                    fluxoEncerrarEGerarRelatorio(); 
                    devePausar = false; // O fluxo já pausa
                 }
                break;

            case 6: // RELATÓRIO PARCIAL / FINAL
                if (status == "NAO_INICIADA") {
                    std::cout << "[AVISO] A votacao nem sequer foi iniciada.\n";
                } else { // ATIVA ou ENCERRADA
                    UtilsUI::limparTela();
                    
                    if (status == "ATIVA") {
                        std::cout << "--- RESULTADOS PARCIAIS (A VOTACAO NAO FOI ENCERRADA) ---\n";
                    } else {
                        std::cout << "--- RESULTADOS FINAIS (A VOTACAO FOI ENCERRADA) ---\n";
                    }
                    
                    sistema.gerarResultadosParciais(); // Esta função serve para ambos os casos
                    
                    UtilsUI::pausar();
                    devePausar = false;
                }
                break;

            case 7: // ALTERAR TÍTULO
                if (status == "NAO_INICIADA") {
                    fluxoAlterarTitulo();
                } else {
                    std::cout << "[ERRO] Nao e possivel alterar o titulo apos a votacao ser iniciada.\n" << std::flush;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    devePausar = false;
                }
                break;

            case 8: 
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

    } while (opcao != 8);

    // Saiu do loop, retorna para a Tela Principal
    return new TelaPrincipal(sistema);
}

// Fluxo da UI para adicionar opção
void TelaAdmin::fluxoAdicionarOpcao() {
    UtilsUI::limparTela();
    std::cout << "--- Adicionar Nova Opcao Votavel ---\n";
    
    // UI coleta os dados
    std::string nome = UtilsUI::lerStringNaoVazia("Nome (ex: 'O Poderoso Chefao'): ");
    std::string descricao = UtilsUI::lerStringNaoVazia("Descricao (ex: 'Filme de Mafia'): ");
    std::cout << "Numero para Votacao (ex: 10): " << std::flush;
    int idNum = UtilsUI::lerOpcaoNumerica();
    
    if (idNum == -1) {
            std::cout << "[ERRO] Numero invalido. Operacao cancelada.\n";
    } else {
            // UI passa os dados para o gerenciador
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
        // Passa o ID para o sistema (gerenciador)
        sistema.removerOpcao(idNum);
    }
}

// Fluxo da UI para encerrar e mostrar o relatório
void TelaAdmin::fluxoEncerrarEGerarRelatorio() {
    // Checa o status antes de agir
    if (sistema.getStatus() == "NAO_INICIADA") {
        std::cout << "[AVISO] Votacao nem sequer foi iniciada.\n";
        UtilsUI::pausar();
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
    
    UtilsUI::pausar();
}

// Fluxo da UI para alterar o título
void TelaAdmin::fluxoAlterarTitulo() {
    UtilsUI::limparTela();
    std::cout << "--- Alterar Titulo da Votacao ---\n";
    std::cout << "Titulo Atual: " << sistema.getTituloVotacao() << std::endl;
    std::string novoTitulo = UtilsUI::lerStringNaoVazia("Digite o novo titulo: ");
    
    // Chama o gerenciador
    sistema.setTituloVotacao(novoTitulo);
}