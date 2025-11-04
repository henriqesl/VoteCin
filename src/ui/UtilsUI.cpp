#include "../../include/ui/UtilsUI.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <stdexcept>
#include <thread>
#include <chrono>

// Limpa o terminal
void UtilsUI::limparTela() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

// Lê uma linha inteira e converte para int
int UtilsUI::lerOpcaoNumerica() {
    std::string input;
    std::getline(std::cin, input);
    try {
        if (input.empty()) return -1;
        return std::stoi(input); // Converte string para int
    } catch (const std::exception& e) {
        return -1; // Retorna -1 se a conversão falhar
    }
}

// Garante que o usuário não digite uma string vazia
std::string UtilsUI::lerStringNaoVazia(const std::string& prompt) {
    std::string input;
    do {
        std::cout << prompt << std::flush;
        std::getline(std::cin, input);
        if (input.empty()) {
            std::cout << "[AVISO] Entrada nao pode ser vazia. Tente novamente.\n";
        }
    } while (input.empty());
    return input;
}

// Mostra o menu de seleção de template e retorna o caminho do arquivo
std::string UtilsUI::selecionarArquivoDeOpcoes() {
    limparTela();
    std::cout << "--- CONFIGURACAO INICIAL DO SISTEMA ---\n";
    std::cout << "Selecione o template de votacao que deseja carregar:\n\n";
    std::cout << "1. Votacao de Filmes\n";
    std::cout << "2. Votacao de Jogos\n";
    std::cout << "3. Votacao de Destinos de Viagem\n";
    std::cout << "4. Votacao Personalizada (Comecar do zero)\n\n";
    std::cout << "Escolha uma opcao: " << std::flush;

    int tipo = lerOpcaoNumerica();
    std::string basePath = "../resources/"; 
    std::string arquivoEscolhido;

    // Seleção do modo de votação
    switch (tipo) {
        case 1:
            std::cout << "\nCarregando 'opcoes_filmes.txt'...\n";
            arquivoEscolhido = basePath + "opcoes_filmes.txt";
            break;
        case 2:
            std::cout << "\nCarregando 'opcoes_jogos.txt'...\n";
            arquivoEscolhido = basePath + "opcoes_jogos.txt";
            break;
        case 3:
            std::cout << "\nCarregando 'opcoes_viagem.txt'...\n";
            arquivoEscolhido = basePath + "opcoes_viagem.txt";
            break;
        case 4: 
        default:
            std::cout << "\nCarregando 'opcoes_vazia.txt' (votacao personalizada)...\n";
            arquivoEscolhido = basePath + "opcoes_vazia.txt";
            break;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Pausa para feedback
    return arquivoEscolhido;
}

// Pausa a execução até o usuário pressionar ENTER
void UtilsUI::pausar() {
    std::cout << "\n...pressione ENTER para continuar...\n" << std::flush;
    // Limpa o buffer de entrada antes de esperar
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Lida com a lógica de login do admin
bool UtilsUI::loginAdmin() {
    limparTela();
    std::cout << "--- LOGIN ADMIN ---\n";
    std::string usuario = lerStringNaoVazia("Utilizador: ");
    std::string senha = lerStringNaoVazia("Senha: ");

    // Login fixo
    if (usuario == "admin" && senha == "admin") {
        std::cout << "Login de admin bem-sucedido!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return true;
    }
    
    std::cout << "[ERRO] Credenciais invalidas.\n" << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return false;
}