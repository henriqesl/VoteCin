# Versão do CMake
cmake_minimum_required(VERSION 3.16)

project(VoteCinTerminal VERSION 0.1 LANGUAGES CXX)

# Configurações padrão do C++ (padrão C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Listagem de todos os ficheiros
set(PROJECT_SOURCES
    main.cpp
    src/Pessoa.cpp
    src/Eleitor.cpp
    src/Candidato.cpp
    src/Urna.cpp
    src/Eleicao.cpp
    src/Relatorio.cpp
    src/GerenciadorDados.cpp
    src/SistemaVotacao.cpp
)

# Cria o executável chamado "VoteCinTerminal" a partir dos seus ficheiros
add_executable(VoteCinTerminal ${PROJECT_SOURCES})

# direciona até os arquivos .h na pasta "include"
target_include_directories(VoteCinTerminal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
