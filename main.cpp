#include "include/GerenciadorVotacoes.h"
#include "include/ui/TelaPrincipal.h"
#include "include/ui/UtilsUI.h"

// Ponto de entrada do programa.
// Responsável pela configuração inicial e pelo loop principal da máquina de estados (Telas).
int main() {
    
    
    // Mostra a UI de seleção de template
    std::string arquivoOpcoes = UtilsUI::selecionarArquivoDeOpcoes();
    
    GerenciadorVotacoes sistema("Votacao CIn", "04/11/2025");
    
    // Carrega os dados iniciais
    std::cout << "A carregar dados da votacao...\n";
    sistema.carregarDadosIniciais(arquivoOpcoes);
    
    std::cout << "Sistema pronto.\n\n";
    std::cout << "A iniciar menu principal em 3 segundos..." << std::endl << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    // Começa pela TelaPrincipal
    Tela* telaAtual = new TelaPrincipal(sistema);
    
    // O loop continua enquanto a telaAtual não for nula
    while (telaAtual != nullptr) {
        // Executa a tela atual e pede a próxima
        Tela* proxima = telaAtual->proximaTela();
        
        // Limpa a memória da tela que acabamos de usar
        delete telaAtual;  
        
        // Avança para a próxima tela
        telaAtual = proxima; 
    }

    // Função CLEANUP
    UtilsUI::limparTela();
    std::cout << "========================================\n";
    std::cout << "    SISTEMA DE VOTACAO FINALIZADO\n";
    std::cout << "========================================\n";

    return 0;
}