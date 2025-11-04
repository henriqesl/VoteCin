#include "ui/TelaPrincipal.h"
#include "ui/TelaAdmin.h"    
#include "ui/TelaVotacao.h"  
#include "ui/UtilsUI.h"      

#include <iostream>
#include <thread>
#include <chrono>

// Mostra o menu e decide a próxima tela
Tela* TelaPrincipal::proximaTela() {
    UtilsUI::limparTela();
    std::cout << "\n\n--- BEM-VINDO AO SISTEMA DE VOTACAO ---\n";
    std::cout << "Votacao Atual: " << sistema.getTituloVotacao() << "\n";
    std::cout << "Status: " << sistema.getStatus() << "\n";
    std::cout << "----------------------------------------\n";
    std::cout << "1. Entrar como Administrador\n";
    std::cout << "2. Votar (Sessao Aberta)\n"; 
    std::cout << "3. Sair\n";
    std::cout << "Escolha uma opcao: " << std::flush;

    int tipoUsuario = UtilsUI::lerOpcaoNumerica(); 

    // Lógica de navegação (decide qual objeto Tela retornar)
    switch (tipoUsuario) {
        case 1: // Ir para a tela de Admin
            if (UtilsUI::loginAdmin()) {
                return new TelaAdmin(sistema); // Próxima tela: Admin
            }
            return new TelaPrincipal(sistema);

        case 2: // Ir para a tela de Votação
            if (sistema.getStatus() == "ATIVA") {
                return new TelaVotacao(sistema); // Próxima tela: Votação
            } else if (sistema.getStatus() == "NAO_INICIADA") {
                std::cout << "\n[AVISO] A votacao ainda nao foi iniciada pelo Administrador." << std::endl;
            } else { // ENCERRADA
                std::cout << "\n[AVISO] A votacao ja foi encerrada." << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return new TelaPrincipal(sistema); // Permanece nesta tela

        case 3:
            std::cout << "A encerrar programa...\n";
            return nullptr; // Sinaliza para o main.cpp encerrar o loop

        case -1:
        default:
            std::cout << "\n[AVISO] Opcao invalida. Tente novamente.\n" << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return new TelaPrincipal(sistema); // Recarrega esta tela
    }
}