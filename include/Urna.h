#ifndef URNA_H
#define URNA_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "Voto.h"      
#include "Eleitor.h"   
#include "Candidato.h" 

class Urna {
private:
    std::vector<Voto> votosRegistrados; // A urna é dona desses votos
    std::map<int, Candidato*> mapaCandidatos; 

    int votosNulos;
    int votosBrancos;

public:
    // Recebe a lista de candidatos disponiveis para referencia-los
    Urna(const std::vector<Candidato*>& candidatos);

    // Metodo principal para realizar o voto
    bool votar(Eleitor& eleitor, int numeroCandidato);

    // Getters para o Relatorio
    const std::vector<Voto>& getVotosRegistrados() const { return votosRegistrados; }
    const std::map<int, Candidato*>& getMapaCandidatos() const { return mapaCandidatos; }
    int getVotosNulos() const { return votosNulos; }
    int getVotosBrancos() const { return votosBrancos; }

private:
    // Encapsulamento
    void processarVoto(const Eleitor& eleitor, int numeroCandidato);
};

#endif