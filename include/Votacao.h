#ifndef VOTACAO_H
#define VOTACAO_H

#include <string>
#include <vector>
#include <map>
#include <memory>

// Forward declarations
class Urna; 
class Votante;
class Opcao;

// Gerencia o ESTADO da sessão de votação (Ativa, Encerrada, etc)
class Votacao {
private:
    std::string titulo;
    std::string data;
    std::string status = "NAO_INICIADA";   // "NAO_INICIADA", "ATIVA", "ENCERRADA"
    
    std::vector<Opcao*> opcoes; 
    std::map<std::string, Votante*> votantes; // Mapa (ID -> Votante)
    
    // Votacao "possui" a Urna. A Urna só existe se a votação for iniciada.
    std::unique_ptr<Urna> urna; 

public:
    Votacao(const std::string& titulo, const std::string& data);
    
    // Impede cópias
    Votacao(const Votacao&) = delete; 
    Votacao& operator=(const Votacao&) = delete;

    // --- Gerenciamento de Listas  ---
    void adicionarOpcao(Opcao* o);
    void adicionarVotante(Votante* v);
    void limparOpcoes();                // Para o CRUD do Admin

    // --- Controle de Votação ---
    void iniciarVotacao(); // Cria a Urna
    void encerrarVotacao(); // "Fecha" a Urna

    // Direciona o voto para a Urna
    bool votar(Votante& votante, int idOpcao);
    
    // --- Getters ---
    const std::vector<Opcao*>& getOpcoes() const { return opcoes; }
    const std::map<std::string, Votante*>& getVotantes() const;
    Votante* getVotante(const std::string& id) const; 
    Urna* getUrna() const { return urna.get(); } 
    std::string getStatus() const { return status; }
    std::string getTitulo() const { return titulo; }
};

#endif