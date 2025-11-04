# Versão do CMake
cmake_minimum_required(VERSION 3.16)

project(VoteCinTerminal VERSION 0.1 LANGUAGES CXX)

# Configurações padrão do C++ (padrão C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Listagem de todos os ficheiros 
set(PROJECT_SOURCES
    # Lógica Principal (BLL e DAL)
    src/data/GerenciadorDados.cpp
    src/core/GerenciadorVotacoes.cpp
    src/models/Opcao.cpp
    src/models/Participante.cpp
    src/core/Relatorio.cpp
    src/core/Urna.cpp
    src/core/Votacao.cpp
    src/models/Votante.cpp

    # Nova Camada de UI
    src/ui/UtilsUI.cpp
    src/ui/TelaPrincipal.cpp
    src/ui/TelaAdmin.cpp
    src/ui/TelaVotacao.cpp

    # O Ponto de Entrada 
    main.cpp
)

# Cria o executável
add_executable(VoteCinTerminal ${PROJECT_SOURCES})

# direciona até os arquivos .h
target_include_directories(VoteCinTerminal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)