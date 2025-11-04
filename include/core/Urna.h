#ifndef URNA_H
#define URNA_H

#include <vector>
#include <map>
#include <string>
#include "Voto.h"      
#include "Votante.h" 
#include "Opcao.h"   

// Controla a lógica do "ato de votar"
// Verifica duplicidade, conta nulos/brancos
class Urna {
private:
    std::vector<Voto> votosRegistrados; 
    std::map<int, Opcao*> mapaOpcoes;   // Atalho para encontrar opções por ID

    int votosNulos;
    int votosBrancos;

public:
    // Construtor: "Abre" a urna com as opções válidas
    Urna(const std::vector<Opcao*>& opcoes);

    // Tenta registrar o voto
    bool votar(Votante& votante, int idOpcao); 

    // --- Getters ---
    const std::vector<Voto>& getVotosRegistrados() const { return votosRegistrados; }
    int getVotosNulos() const { return votosNulos; }
    int getVotosBrancos() const { return votosBrancos; }

private:
    // Helper interno para adicionar o voto na Opcao correta
    void processarVoto(int idOpcao); 
};

#endif