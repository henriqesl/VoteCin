#ifndef VOTANTE_H
#define VOTANTE_H

#include "Participante.h" // Classe base
#include <iostream>

// Representa um votante (Herda de Participante)
// Guarda o estado de voto 
class Votante : public Participante {
private:
    bool jaVotou; // Flag que controla o estado de voto

public:
    Votante(const std::string& nome, const std::string& id);
    
    bool podeVotar() const;
    void registrarVoto(); // Altera jaVotou para true

    // --- Getters ---
    bool getJaVotou() const;

    // Imprime os detalhes do Votante
    virtual void imprimirDetalhes() const override;
};

#endif