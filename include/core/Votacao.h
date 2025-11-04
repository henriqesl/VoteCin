#ifndef VOTACAO_H
#define VOTACAO_H

#include <string>
#include <vector>
#include <map>
#include <memory> 

class Urna; 
class Votante;
class Opcao;

// Gerencia o ESTADO da sessão de votação (Ativa, Encerrada, etc)
class Votacao {
private:
    std::string titulo;
    std::string data;
    std::string status = "NAO_INICIADA"; 
    
    std::vector<Opcao*> opcoes; 
    std::map<std::string, Votante*> votantes;
    
    std::unique_ptr<Urna> urna; 

public:
    Votacao(const std::string& titulo, const std::string& data);
    ~Votacao();
    
    Votacao(const Votacao&) = delete; 
    Votacao& operator=(const Votacao&) = delete;

    // --- Gerenciamento de Listas ---
    void adicionarOpcao(Opcao* o);
    void adicionarVotante(Votante* v);
    void limparOpcoes();

    // --- Controle de Fluxo ---
    bool iniciarVotacao(); 
    void encerrarVotacao();

    bool votar(Votante& votante, int idOpcao);
    
    // --- Getters ---
    const std::vector<Opcao*>& getOpcoes() const;
    const std::map<std::string, Votante*>& getVotantes() const;
    Votante* getVotante(const std::string& id) const; 
    Urna* getUrna() const { return urna.get(); } 
    std::string getStatus() const;
    std::string getTitulo() const;

    // --- Setters ---
    void setTitulo(const std::string& novoTitulo); // NOVO
};

#endif