#ifndef OPCAO_H
#define OPCAO_H

#include <string>
#include <iostream>

// Representa um item votável (ex: filme, jogo)
class Opcao {
private:
    int idNumerico;          // Número para votar (ex: 10)
    std::string nome;
    std::string descricao;
    int totalVotos;          // Contador de votos

public:
    Opcao(int id, const std::string& nome, const std::string& descricao);

    // Incrementa o contador de votos
    void adicionarVoto();

    // --- Getters ---
    int getIdNumerico() const;
    std::string getNome() const;
    std::string getDescricao() const;
    int getTotalVotos() const;

    // Imprime os detalhes formatados (usado no Admin)
    void imprimirDetalhes() const;
};

#endif