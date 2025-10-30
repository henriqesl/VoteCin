#include <iostream>
#include <string>
#include <limits> // Necessário para limpar o buffer de entrada
#include "SistemaVotacao.h" // Inclui a classe principal de coordenação

// Protótipo da função para exibir o menu
void exibirMenu();

// Função principal que gerencia o fluxo interativo do programa

int main() {
    // 1. Inicialização do Sistema
    std::cout << "========================================\n";
    std::cout << "  INICIANDO SISTEMA DE VOTACAO ELETRONICA \n";
    std::cout << "========================================\n";

    // Cria uma instância do SistemaVotacao para a data simulada
    SistemaVotacao sistema("04/11/2025"); 

    int opcao = 0;
    std::string tituloEleitor;
    int numeroCandidato;
    bool dadosCarregados = false; // Flag para garantir que os dados sejam carregados primeiro

    do {
        exibirMenu();
        std::cout << "Escolha uma opcao: ";
        
        // Garante que a entrada seja um número inteiro válido
        if (!(std::cin >> opcao)) {
            std::cout << "\n[ERRO] Entrada invalida. Por favor, digite um numero.\n";
            std::cin.clear(); // Limpa o estado de erro
            // Limpa o buffer para descartar a entrada inválida
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue; // Volta ao início do loop
        }
        
        // Limpa o buffer após a leitura do número para evitar problemas com std::getline ou outras leituras de string
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcao) {
            case 1:
                if (!dadosCarregados) {
                    sistema.carregarDadosIniciais();
                    dadosCarregados = true;
                } else {
                    std::cout << "[AVISO] Dados ja foram carregados.\n";
                }
                break;
                
            case 2:
                if (dadosCarregados) {
                    sistema.iniciarVotacao();
                } else {
                    std::cout << "[ERRO] Carregue os dados (Opcao 1) primeiro.\n";
                }
                break;
                
            case 3: // Votar
                if (sistema.getStatus() == "ATIVA") {
                    std::cout << "--- TELA DE VOTACAO ---\n";
                    std::cout << "Digite o Titulo de Eleitor: ";
                    std::getline(std::cin, tituloEleitor);
                    
                    std::cout << "Digite o Numero do Candidato: ";
                    if (!(std::cin >> numeroCandidato)) {
                        std::cout << "[ERRO] Numero do candidato invalido.\n";
                        // Limpa o buffer novamente em caso de erro na leitura do número
                        std::cin.clear(); 
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break; 
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    // A função 'executarVotacao' já lida com a lógica e imprime o resultado
                    sistema.executarVotacao(tituloEleitor, numeroCandidato);
                    
                } else {
                    std::cout << "[ERRO] A votacao nao esta ATIVA. Inicie-a (Opcao 2).\n";
                }
                break;
                
            case 4:
                sistema.encerrarVotacao();
                break;
                
            case 5:
                sistema.gerarResultados();
                break;

            case 6:
                std::cout << "Encerrando programa...\n";
                break;
                
            default:
                std::cout << "[AVISO] Opcao invalida. Tente novamente.\n";
                break;
        }

        if (opcao != 6) {
            std::cout << "\nPressione ENTER para continuar...\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (opcao != 6);

    std::cout << "========================================\n";
    std::cout << "    SISTEMA DE VOTACAO FINALIZADO\n";
    std::cout << "========================================\n";
    
    return 0;
}

// Exibe as opções do menu principal

void exibirMenu() {
    std::cout << "\n\n--- MENU PRINCIPAL ---\n";
    std::cout << "1. Carregar Dados Iniciais (Candidatos e Eleitores)\n";
    std::cout << "2. Iniciar Votacao\n";
    std::cout << "3. Votar (Requer votacao ATIVA)\n";
    std::cout << "4. Encerrar Votacao\n";
    std::cout << "5. Gerar Relatorio e Apuracao de Resultados\n";
    std::cout << "6. Sair\n";
    std::cout << "----------------------\n";
}