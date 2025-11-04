#include <iostream>
#include <string>
#include <limits>    
#include <cstdlib>   
#include <thread>    
#include <chrono>    
#include <stdexcept> 
#include "GerenciadorVotacoes.h" 
#include "Votante.h"             

void limparTela() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

int lerOpcaoNumerica() {
    std::string input;
    std::getline(std::cin, input);
    try {
        if (input.empty()) return -1;
        return std::stoi(input);
    } catch (const std::exception& e) {
        return -1;
    }
}

std::string lerStringNaoVazia(const std::string& prompt) {
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

std::string selecionarArquivoDeOpcoes() {
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
            std::cout << "\nCarregando 'opcoes_viagens.txt'...\n";
            arquivoEscolhido = basePath + "opcoes_viagem.txt"; 
            break;
        case 4: 
        default:
            std::cout << "\nCarregando 'opcoes_vazia.txt' (votacao personalizada)...\n";
            arquivoEscolhido = basePath + "opcoes_vazia.txt"; 
            break;
    }
    return arquivoEscolhido;
}


bool loginAdmin();
void menuAdmin(GerenciadorVotacoes& sistema); 
void iniciarSessaoDeVotacao(GerenciadorVotacoes& sistema); 

int main() {
    limparTela();
    std::cout << "========================================\n";
    std::cout << "  INICIANDO GERENCIADOR DE VOTACOES \n";
    std::cout << "========================================\n\n";

    std::string arquivoOpcoes = selecionarArquivoDeOpcoes();
    GerenciadorVotacoes sistema("Votacao CIn", "04/11/2025");
    
    std::cout << "A carregar dados da votacao...\n";
    sistema.carregarDadosIniciais(arquivoOpcoes);

    std::cout << "Sistema pronto.\n\n";
    std::cout << "A iniciar menu principal em 3 segundos..." << std::endl << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    int tipoUsuario = 0;
    do {
        limparTela();
        std::cout << "\n\n--- BEM-VINDO AO SISTEMA DE VOTACAO ---\n";
        std::cout << "Votacao Atual: " << sistema.getTituloVotacao() << "\n";
        std::cout << "Status: " << sistema.getStatus() << "\n";
        std::cout << "----------------------------------------\n";
        std::cout << "1. Entrar como Administrador\n";
        std::cout << "2. Votar (Sessao Aberta)\n"; 
        std::cout << "3. Sair\n";
        std::cout << "Escolha uma opcao: " << std::flush;

        tipoUsuario = lerOpcaoNumerica(); 

        switch (tipoUsuario) {
            case 1:
                if (loginAdmin()) {
                    menuAdmin(sistema);
                } else {
                    std::cout << "A retornar ao menu principal em 2 segundos..." << std::endl << std::flush;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
                break;
            case 2:
                if (sistema.getStatus() == "ATIVA") {
                    iniciarSessaoDeVotacao(sistema); 
                    std::cout << "\nSessao de votacao encerrada. Pressione ENTER para voltar ao menu principal..." << std::endl << std::flush;
                    std::cin.get();
                } else if (sistema.getStatus() == "NAO_INICIADA") {
                    std::cout << "\n[AVISO] A votacao ainda nao foi iniciada pelo Administrador." << std::endl;
                    std::cout << "Volte mais tarde." << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                } else { 
                    std::cout << "\n[AVISO] A votacao ja foi encerrada." << std::endl;
                    std::cout << "Peca para um Admin gerar o relatorio." << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
                break;
            case 3:
                std::cout << "A encerrar programa...\n";
                break;
            case -1:
            default:
                std::cout << "\n[AVISO] Opcao invalida. Tente novamente.\n" << std::flush;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
        }
    } while (tipoUsuario != 3);

    limparTela();
    std::cout << "========================================\n";
    std::cout << "    SISTEMA DE VOTACAO FINALIZADO\n";
    std::cout << "========================================\n";

    return 0;
}

bool loginAdmin() {
    limparTela();
    std::string usuario, senha;
    std::cout << "--- LOGIN ADMIN ---\n";
    std::cout << "Utilizador: " << std::flush;
    std::getline(std::cin, usuario);
    std::cout << "Senha: " << std::flush;
    std::getline(std::cin, senha);

    if (usuario == "admin" && senha == "admin") {
        std::cout << "Login de admin bem-sucedido!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return true;
    }
    std::cout << "[ERRO] Credenciais invalidas.\n" << std::flush;
    return false;
}

void menuAdmin(GerenciadorVotacoes& sistema) { 
    int opcao = 0;
    do {
        limparTela();
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

        opcao = lerOpcaoNumerica();
        bool devePausar = true; 

        switch(opcao) {
            case 1: { 
                limparTela();
                std::cout << "--- Adicionar Nova Opcao Votavel ---\n";
                
                std::string nome = lerStringNaoVazia("Nome (ex: 'O Poderoso Chefao'): ");
                std::string descricao = lerStringNaoVazia("Descricao (ex: 'Filme de Mafia'): ");
                std::cout << "Numero para Votacao (ex: 10): " << std::flush;
                int idNum = lerOpcaoNumerica();
                
                if (idNum == -1) {
                     std::cout << "[ERRO] Numero invalido. Operacao cancelada.\n";
                } else {
                     sistema.adicionarNovaOpcao(idNum, nome, descricao);
                }
                break;
            }
            case 2: 
                limparTela();
                std::cout << "--- LISTA DE OPCOES ATUAIS ---\n";
                sistema.listarOpcoesAdmin(); 
                break;
            case 3: { 
                limparTela();
                std::cout << "--- Remover Opcao Votavel ---\n";
                sistema.listarOpcoesAdmin(); 
                
                std::cout << "\nDigite o NUMERO da opcao que deseja remover: " << std::flush;
                int idNum = lerOpcaoNumerica();
                
                if (idNum == -1) {
                    std::cout << "[ERRO] Numero invalido. Operacao cancelada.\n";
                } else {
                    sistema.removerOpcao(idNum);
                }
                break;
            }
            case 4: 
                sistema.iniciarVotacao();
                break;
            case 5: 
                if (sistema.getStatus() == "NAO_INICIADA") {
                    std::cout << "[AVISO] Votacao nem sequer foi iniciada.\n";
                    break;
                }
                if (sistema.getStatus() == "ENCERRADA") {
                    std::cout << "A votacao ja esta encerrada. Gerando relatorio novamente...\n";
                } else {
                    sistema.encerrarVotacao(); 
                }
                
                limparTela();
                std::cout << "--- VOTACAO ENCERRADA ---\n";
                sistema.gerarResultados(); 
                std::cout << "\n\nRelatorio gerado. Pressione ENTER para voltar...\n" << std::flush;
                std::cin.get();
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
             std::cout << "\n...pressione ENTER para continuar...\n" << std::flush;
             std::cin.get(); 
        }

    } while (opcao != 6);
}


void iniciarSessaoDeVotacao(GerenciadorVotacoes& sistema) { 
    
    std::string nomeVotante;
    while (true) {
        limparTela();
        std::cout << "--- SESSAO DE VOTACAO ATIVA ---\n";
        std::cout << "Votacao: " << sistema.getTituloVotacao() << "\n\n";

        sistema.listarOpcoesParaVotacao(); 

        std::cout << "\n----------------------------------------\n";
        std::cout << "Digite o seu NOME para votar (ou 'SAIR' para voltar ao menu):\n> " << std::flush;
        std::getline(std::cin, nomeVotante);

        if (nomeVotante.empty()) continue;

        if (nomeVotante == "SAIR" || nomeVotante == "sair") {
            std::cout << "Voltando ao menu principal...\n" << std::flush;
            break; 
        }

        Votante* votante = sistema.getVotantePorNome(nomeVotante);

        if (votante == nullptr) {
            votante = sistema.criarNovoVotante(nomeVotante);
            std::cout << "Bem-vindo(a), " << nomeVotante << "! Registrando seu primeiro voto.\n";
        } else {
             std::cout << "Bem-vindo(a) de volta, " << votante->getNome() << ".\n";
        }

        if (!votante->podeVotar()) {
            std::cout << "[AVISO] Voce (" << votante->getNome() << ") ja votou nesta votacao.\n" << std::flush;
        } else {
            std::cout << "\nDigite o NUMERO da sua opcao (ou 99 para Branco): " << std::flush;
            int idOpcao = lerOpcaoNumerica(); 

            if (idOpcao == -1) {
                std::cout << "[ERRO] Numero da opcao invalido.\n";
            } else {
                sistema.executarVotacao(*votante, idOpcao); 
            }
        }
        
        std::cout << "\n...pressione ENTER para o proximo votante (ou digite SAIR)...\n" << std::flush;
        std::cin.get();
    }
}