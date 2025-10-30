#ifndef URNA_H
#define URNA_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "Voto.h"      // Composicao: Urna armazena Votos
#include "Eleitor.h"   // Agregacao: Para validar Eleitores
#include "Candidato.h" // Agregacao: Para contabilizar Candidatos

class Urna {
private:
    std::vector<Voto> votosRegistrados; // Composicao: A Urna eh dona desses votos
    
    // Agregacao: Usa ponteiros para Candidatos gerenciados pela Eleicao
    // Chave: numero do candidato (int), Valor: ponteiro para o objeto Candidato
    std::map<int, Candidato*> mapaCandidatos; 

public:
    // Construtor: Recebe a lista de candidatos disponiveis para referencia-los
    Urna(const std::vector<Candidato*>& candidatos);

    // Abstracao: Metodo principal para efetuar o voto, lida com a validacao interna
    bool votar(Eleitor& eleitor, int numeroCandidato);

    // Getters para o Relatorio
    const std::vector<Voto>& getVotosRegistrados() const { return votosRegistrados; }
    const std::map<int, Candidato*>& getMapaCandidatos() const { return mapaCandidatos; }

private:
    // Detalhe interno do processo (Ocultamento/Encapsulamento)
    void processarVoto(const Eleitor& eleitor, int numeroCandidato);
};

#endif