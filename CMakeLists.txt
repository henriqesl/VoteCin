# Versão mínima do CMake e definição do projeto (nome, versão, linguagem)
cmake_minimum_required(VERSION 3.16)
project(EDOO VERSION 0.1 LANGUAGES CXX)

# Configurações padrão do C++ (usar o padrão C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Habilita as ferramentas automáticas do Qt (MOC, UIC, RCC)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms)

# --- Dependências do Qt ---
# Procura pela instalação do Qt6 e pelos módulos que vamos usar.
# Esta é a única linha que você precisa mudar se adicionar mais módulos do Qt.
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)

# --- Fontes do Projeto ---
# Lista centralizada de todos os arquivos do seu projeto.
# Use os caminhos corretos para as pastas que criamos!
set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
    forms/mainwindow.ui
)

# --- Construção do Executável ---
# Cria o executável chamado "EDOO" a partir da sua lista de fontes.
qt_add_executable(EDOO ${PROJECT_SOURCES})

# Informa ao compilador para procurar por arquivos .h na pasta "include".
# Esta linha é ESSENCIAL para a nova organização de pastas funcionar.
target_include_directories(EDOO PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# "Linka" as bibliotecas do Qt que encontramos com o nosso executável.
target_link_libraries(EDOO PRIVATE
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::MultimediaWidgets
)

# Comando final necessário para projetos Qt6.
qt_finalize_executable(EDOO)
