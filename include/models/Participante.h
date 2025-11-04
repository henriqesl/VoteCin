#ifndef PARTICIPANTE_H
#define PARTICIPANTE_H

#include <string>

// Classe base ABSTRATA para Votante
class Participante {
private:
    std::string nome;
    std::string id; // ID genérico

public:
    Participante();
    Participante(const std::string& nome, const std::string& id);
    virtual ~Participante() = default; // Destrutor virtual

    // --- Getters e Setters ---
    std::string getNome() const;
    std::string getId() const;
    void setNome(const std::string& nome);
    void setId(const std::string& id);

    virtual void imprimirDetalhes() const = 0;
};

#endif