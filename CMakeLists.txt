# Versão mínima do CMake
cmake_minimum_required(VERSION 3.16)

# Definição do projeto (use o nome da pasta ou o nome que preferir)
project(VoteCinTerminal VERSION 0.1 LANGUAGES CXX)

# Configurações padrão do C++ (usar o padrão C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Fontes do Projeto ---
# Lista de todos os ficheiros de implementação (.cpp) do seu projeto
set(PROJECT_SOURCES
    main.cpp
    src/Pessoa.cpp
    src/Eleitor.cpp
    src/Candidato.cpp
    # src/Voto.cpp  <- Adicione esta linha se tiver um Voto.cpp
    src/Urna.cpp
    src/Eleicao.cpp
    src/Relatorio.cpp
    src/GerenciadorDados.cpp
    src/SistemaVotacao.cpp
)

# --- Construção do Executável ---
# Cria o executável chamado "VoteCinTerminal" a partir dos seus ficheiros
add_executable(VoteCinTerminal ${PROJECT_SOURCES})

# Informa ao compilador para procurar por arquivos .h na pasta "include"
target_include_directories(VoteCinTerminal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)