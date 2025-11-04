# VoteCIN — Sistema de Gerenciamento de Votações

O **VoteCIN** é um sistema modular de votação desenvolvido em **C++**, com ênfase na **programação orientada a objetos (POO)** e **organização em camadas**.  
O projeto busca oferecer uma solução didática e flexível para gerenciamento de votações via terminal, permitindo controle total por parte do administrador e participação aberta de usuários.

---

## Resumo do Projeto

O sistema foi desenvolvido com o propósito de aplicar conceitos de arquitetura de software e POO em um contexto prático.  
O **VoteCIN** simula um ambiente de votação no qual um administrador é responsável por criar, configurar e encerrar votações, enquanto usuários podem registrar votos de forma simples e segura.  

A aplicação é totalmente executada no **terminal**, priorizando clareza na interface e modularidade no código.

---

## Objetivos do Sistema

- Facilitar o gerenciamento de votações genéricas (como eleições internas ou enquetes).  
- Permitir que administradores configurem, iniciem e encerrem votações com liberdade.  
- Demonstrar o uso de **camadas de software**, **abstração**, **encapsulamento** e **polimorfismo** em um projeto real.  
- Servir como base para estudos e experimentação com POO e arquitetura em C++.

---

## Organização do Projeto

O código é estruturado segundo uma **arquitetura em camadas**, separando responsabilidades entre interface (UI), lógica (CORE) e dados (DATA).  
Essa divisão garante legibilidade, reuso e facilidade de manutenção.

```
├── include/         # Cabeçalhos (.h) públicos de cada módulo
│ ├── core/          # GerenciadorVotacoes, Urna, Relatorio
│ ├── data/          # GerenciadorDados
│ ├── models/        # Votante, Opcao, Voto, Participante
│ └── ui/            # Telas e Utilitários
│
├── src/ # Implementações (.cpp)
│ ├── core/
│ ├── data/
│ ├── models/
│ └── ui/
│
├── resources/       # Templates e arquivos de votação (.txt)
├── main.cpp         # Ponto de entrada da aplicação
├── CMakeLists.txt   # Configuração de build (CMake)
└── .gitignore
```


Cada camada possui um papel bem definido:

- **UI (User Interface):** controla toda a interação com o usuário via terminal.  
- **Core:** implementa as regras de negócio (gerenciamento de votos, relatórios, controle de sessão).  
- **Data:** faz leitura e escrita de arquivos, centralizando o acesso aos dados.  
- **Models:** define as estruturas básicas (entidades) usadas em todo o sistema.

---

## Conceitos de POO e Design Aplicados

- **Abstração:** classes base como `Tela` e `Participante` definem o comportamento geral das subclasses.  
- **Encapsulamento:** atributos são privados e acessados por métodos controlados.  
- **Herança:** `Votante` herda de `Participante`, e telas específicas derivam de `Tela`.  
- **Polimorfismo:** o programa principal manipula ponteiros genéricos de `Tela`, permitindo transição dinâmica entre estados.  
- **Arquitetura em Camadas:** separa claramente lógica, dados e interface.  
- **Padrão State:** a navegação entre telas é tratada como uma máquina de estados.

---

## Compilação e Execução

### Pré-requisitos
- Compilador C++17 (g++, clang ou equivalente).  
- CMake 3.16+ instalado.  

### Passo a passo para executar o projeto:
#### No VSCode:
```bash
# Clone o repositório
git clone https://github.com/henriqesl/voteCin.git
cd voteCin

# Crie e entre na pasta de build
mkdir build && cd build

# Gere os arquivos de compilação
cmake ..

# Compile o projeto
cmake --build .

# Execute
./VoteCinTerminal     # Linux/Mac
.\VoteCinTerminal.exe # Windows
```

#### No CLion:
Inicialmente você pode rodar o nosso CMakeLists.txt (run CMAKE), que irá criar uma pasta build em seu diretório do projeto.
Após isso, você pode buildar e/ou dar run em nosso projeto, que deve compilar e iniciar automaticamente.

## Desenvolvedores

