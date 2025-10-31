#include "Urna.h"
#include <iostream> // Incluído para garantir que std::cerr e std::cout funcionem

// Inicializa o mapaCandidatos com as referências (ponteiros)
Urna::Urna(const std::vector<Candidato*>& candidatos)
    // NOVO: Inicializa os contadores
    : votosNulos(0),
      votosBrancos(0)
{
    for (Candidato* c : candidatos) {
        mapaCandidatos[c->getNumeroCandidato()] = c; 
    }
}

bool Urna::votar(Eleitor& eleitor, int numeroCandidato) {
    // 1. Validação do Eleitor (Encapsulamento via podeVotar())
    if (!eleitor.podeVotar()) {
        std::cerr << "ERRO: Eleitor " << eleitor.getNome() << " ja votou." << std::endl;
        return false;
    }

    bool votoProcessado = false; // Flag para indicar se o voto foi contabilizado

    // 2. Classificação e Contagem do Voto
    
    // A) VOTO BRANCO: Convenção 99
    if (numeroCandidato == 99) {
        this->votosBrancos++;
        std::cout << "Voto BRANCO registrado com sucesso." << std::endl;
        votoProcessado = true;
    }
    // B) VOTO EM CANDIDATO CADASTRADO
    else if (mapaCandidatos.find(numeroCandidato) != mapaCandidatos.end()) {
        // Voto VÁLIDO. Chamamos o processamento normal.
        processarVoto(eleitor, numeroCandidato); 
        std::cout << "Voto registrado com sucesso." << std::endl;
        votoProcessado = true;
    }
    // C) VOTO NULO: Qualquer outro número que não é Candidato e não é 99
    else {
        this->votosNulos++;
        std::cerr << "AVISO: Numero " << numeroCandidato << " nao encontrado. Voto NULO registrado." << std::endl;
        votoProcessado = true; 
    }

    // 3. Registro do Eleitor e do Voto (para qualquer voto processado)
    if (votoProcessado) {
        eleitor.registrarVoto(); // Marca o Eleitor como votado
        
        // Registra o Voto na Urna (Composição) para a contagem total/estatísticas
        Voto novoVoto(eleitor.getTituloEleitor(), numeroCandidato);
        votosRegistrados.push_back(novoVoto);

        return true;
    }

    return false;
}

void Urna::processarVoto(const Eleitor& eleitor, int numeroCandidato) {
    // 1. Contabiliza APENAS no Candidato (Encapsulamento via adicionarVoto())
    mapaCandidatos.at(numeroCandidato)->adicionarVoto(); 


}