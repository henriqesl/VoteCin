#ifndef ELEICAO_H
#define ELEICAO_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Urna.h" 
#include "Eleitor.h"
#include "Candidato.h"

class Eleicao {
private:
    std::string data;
    std::string status = "NAO_INICIADA"; // Ex: NAO_INICIADA, ATIVA, ENCERRADA
    
    // Agregacao: Listas de participantes gerenciados externamente pelo SistemaVotacao
    std::vector<Candidato*> candidatos; 
    std::map<std::string, Eleitor*> eleitores; // Chave: Titulo de Eleitor
    
    // Composicao: A Eleicao cria e e dona da Urna
    std::unique_ptr<Urna> urna; 

public:
    // Construtor
    Eleicao(const std::string& data);
    
    // Desliga a copia para evitar duplicacao de ponteiros na Agregacao
    Eleicao(const Eleicao&) = delete; 
    Eleicao& operator=(const Eleicao&) = delete;

    // Gerenciamento de participantes (Agregacao)
    void adicionarCandidato(Candidato* c);
    void adicionarEleitor(Eleitor* e);

    // Controle de fluxo
    void iniciarEleicao();
    void encerrarEleicao();

    // Integracao central: Metodo chamado pelo SistemaVotacao
    bool votar(const std::string& tituloEleitor, int numeroCandidato);
    
    // Getters para Relatorio e SistemaVotacao
    const std::vector<Candidato*>& getCandidatos() const { return candidatos; }
    const std::map<std::string, Eleitor*>& getEleitores() const;
    Eleitor* getEleitor(const std::string& titulo) const; 
    Urna* getUrna() const { return urna.get(); } // Retorna o ponteiro bruto da Urna
    std::string getStatus() const { return status; }
};

#endif