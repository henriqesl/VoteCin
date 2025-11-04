#include "core/Urna.h"
#include <iostream> 

// Inicializa os contadores e o mapa de opções válidas
Urna::Urna(const std::vector<Opcao*>& opcoes)
    : votosNulos(0),
      votosBrancos(0)
{
    // Preenche o mapa para acesso rápido
    for (Opcao* o : opcoes) {
        mapaOpcoes[o->getIdNumerico()] = o; 
    }
}

// Método principal: Processa o ato de votar
bool Urna::votar(Votante& votante, int idOpcao) {
    // Verifica se o votante PODE votar
    if (!votante.podeVotar()) {
        std::cout << "[AVISO] Votante " << votante.getNome() << " (ID: " << votante.getId() << ") ja votou." << std::endl;
        return false; // Voto falhou, não registra
    }

    bool votoProcessado = false; // Flag para registrar o votante

    // Classificação do Voto
    
    // VOTO BRANCO (convenção: 99)
    if (idOpcao == 99) {
        this->votosBrancos++;
        std::cout << "Voto BRANCO registrado com sucesso." << std::endl;
        votoProcessado = true;
    }
    // VOTO VÁLIDO (número existe no mapa)
    else if (mapaOpcoes.find(idOpcao) != mapaOpcoes.end()) {
        processarVoto(idOpcao); // Chama helper para contar
        // Confirmação para o usuário
        Opcao* op = mapaOpcoes.at(idOpcao);
        std::cout << "Voto confirmado para: [" << op->getIdNumerico() << "] " 
                  << op->getNome() << " - " << op->getDescricao() << std::endl;
        votoProcessado = true;
    }
    // VOTO NULO (qualquer outro número)
    else {
        this->votosNulos++;
        std::cerr << "AVISO: Numero " << idOpcao << " nao e uma opcao valida. Voto NULO registrado." << std::endl;
        votoProcessado = true; // Voto nulo ainda conta como "ter votado"
    }

    // Finalização
    if (votoProcessado) {
        votante.registrarVoto(); // Marca o Votante como 'jaVotou'
        
        // Adiciona ao log da Urna
        votosRegistrados.emplace_back(votante.getId(), idOpcao);
        return true; // Voto registrado com sucesso
    }

    return false; 
}

// Helper interno para incrementar o voto na Opcao
void Urna::processarVoto(int idOpcao) {
    mapaOpcoes.at(idOpcao)->adicionarVoto(); 
}