#ifndef GERENCIADORDADOS_H
#define GERENCIADORDADOS_H

#include <vector>
#include <list>
#include <string>
#include "models/Opcao.h"   
#include "models/Votante.h" 

// Classe utilitária para ler e escrever nos arquivos .txt.
class GerenciadorDados {
public:
    // Carrega a lista de opções (filmes, jogos, etc) de um arquivo
    static std::list<Opcao> carregarOpcoes(const std::string& nomeArquivo);

    // Carrega o histórico de votantes do votantes.txt
    static std::list<Votante> carregarVotantes(const std::string& nomeArquivo);
    
    // Salva as opções (CRUD do Admin) no arquivo de template
    static void salvarOpcoes(const std::string& nomeArquivo, const std::list<Opcao>& opcoes);
    
    // Salva o log de votantes (quem votou, novos votantes)
    static void salvarVotantes(const std::string& nomeArquivo, const std::list<Votante>& votantes);

    static void limparLogVotantes();

private:
    // Helper interno para quebrar linhas por vírgula
    static std::vector<std::string> split(const std::string& s, char delimiter);
};

#endif