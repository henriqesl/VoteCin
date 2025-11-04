# Versão do CMake
cmake_minimum_required(VERSION 3.16)

project(VoteCinTerminal VERSION 0.1 LANGUAGES CXX)

# Configurações padrão do C++ (padrão C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Listagem de todos os ficheiros (ATUALIZADA com os nomes corretos)
set(PROJECT_SOURCES
    main.cpp
    src/Participante.cpp     # Antigo Pessoa.cpp
    src/Votante.cpp          # Antigo Eleitor.cpp
    src/Opcao.cpp            # Antigo Candidato.cpp
    src/Urna.cpp
    src/Votacao.cpp          # Antigo Eleicao.cpp
    src/Relatorio.cpp
    src/GerenciadorDados.cpp
    src/GerenciadorVotacoes.cpp # Antigo SistemaVotacao.cpp
)

# Cria o executável chamado "VoteCinTerminal" a partir dos seus ficheiros
add_executable(VoteCinTerminal ${PROJECT_SOURCES})

# direciona até os arquivos .h na pasta "include"
target_include_directories(VoteCinTerminal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)