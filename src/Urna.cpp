#include "Urna.h"

// Inicializa o mapaCandidatos com as referências (ponteiros)
Urna::Urna(const std::vector<Candidato*>& candidatos) {
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

    // 2. Validação do Candidato
    if (mapaCandidatos.find(numeroCandidato) == mapaCandidatos.end()) {
        std::cerr << "ERRO: Candidato com numero " << numeroCandidato << " nao encontrado." << std::endl;
        return false;
    }

    // 3. Processa e registra
    processarVoto(eleitor, numeroCandidato);
    eleitor.registrarVoto(); // Marca o Eleitor como votado (Encapsulamento)
    
    std::cout << "Voto registrado com sucesso." << std::endl;
    return true;
}

void Urna::processarVoto(const Eleitor& eleitor, int numeroCandidato) {
    // 1. Contabiliza no Candidato (Encapsulamento via adicionarVoto())
    mapaCandidatos.at(numeroCandidato)->adicionarVoto(); 

    // 2. Registra o Voto na Urna (Composição)
    Voto novoVoto(eleitor.getTituloEleitor(), numeroCandidato);
    votosRegistrados.push_back(novoVoto);
}