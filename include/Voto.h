#ifndef VOTO_H
#define VOTO_H

#include <string>

// Classe de dados simples (struct)
// Representa um registro de log: "Quem votou em quê"
class Voto {
private:
    std::string idVotante;   // ID (nome) do votante
    int idOpcao;             // Número da opção

public:
    Voto(const std::string& idVotante, int idOpcao) 
        : idVotante(idVotante), idOpcao(idOpcao) {}

    // --- Getters ---
    std::string getIdVotante() const { return idVotante; }
    int getIdOpcao() const { return idOpcao; }
};

#endif