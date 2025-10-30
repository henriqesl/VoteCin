#ifndef VOTO_H
#define VOTO_H

#include <string>

// Registra um voto, vinculando o eleitor ao candidato
class Voto {
private:
    std::string tituloEleitor;
    int numeroCandidato;
    
public:
    // Construtor
    Voto(const std::string& titulo, int numero) 
        : tituloEleitor(titulo), numeroCandidato(numero) {}

    // Getters
    std::string getTituloEleitor() const { return tituloEleitor; }
    int getNumeroCandidato() const { return numeroCandidato; }
};

#endif