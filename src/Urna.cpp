#include "Urna.h"
#include <iostream> 

// Inicializa o mapaCandidatos com as referências
Urna::Urna(const std::vector<Candidato*>& candidatos)
    // Inicializa os contadores
    : votosNulos(0),
      votosBrancos(0)
{
    for (Candidato* c : candidatos) {
        mapaCandidatos[c->getNumeroCandidato()] = c; 
    }
}

bool Urna::votar(Eleitor& eleitor, int numeroCandidato) {
    // Validação do Eleitor
    if (!eleitor.podeVotar()) {
        std::cerr << "ERRO: Eleitor " << eleitor.getNome() << " ja votou." << std::endl;
        return false;
    }

    bool votoProcessado = false; // Flag para indicar se o voto foi contabilizado

    // Classificação e Contagem do Voto
    
    // VOTO BRANCO: Convenção 99
    if (numeroCandidato == 99) {
        this->votosBrancos++;
        std::cout << "Voto BRANCO registrado com sucesso." << std::endl;
        votoProcessado = true;
    }
    // VOTO EM CANDIDATO CADASTRADO
    else if (mapaCandidatos.find(numeroCandidato) != mapaCandidatos.end()) {
        // Voto VÁLIDO. Chamamos o processamento normal.
        processarVoto(eleitor, numeroCandidato); 
        std::cout << "Voto registrado com sucesso." << std::endl;
        votoProcessado = true;
    }
    // VOTO NULO: Qualquer outro número que não é Candidato e não é 99
    else {
        this->votosNulos++;
        std::cerr << "AVISO: Numero " << numeroCandidato << " nao encontrado. Voto NULO registrado." << std::endl;
        votoProcessado = true; 
    }

    // Registro do Eleitor e do Voto
    if (votoProcessado) {
        eleitor.registrarVoto(); // Marca o Eleitor como votado
        
        // Registra o Voto na Urna 
        Voto novoVoto(eleitor.getTituloEleitor(), numeroCandidato);
        votosRegistrados.push_back(novoVoto);

        return true;
    }

    return false;
}

void Urna::processarVoto(const Eleitor& eleitor, int numeroCandidato) {
    // Contabiliza APENAS no Candidato
    mapaCandidatos.at(numeroCandidato)->adicionarVoto(); 
}