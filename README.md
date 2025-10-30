## **Estrutura do Projeto**

O sistema será composto por várias classes principais, cada uma responsável por uma parte específica do programa:

| Classe | Responsabilidade |
| :---- | :---- |
| Eleitor | Representa um eleitor, armazena dados pessoais e verifica se já votou. |
| Candidato | Representa um candidato, armazena dados e contabiliza votos recebidos. |
| Voto | Registra um voto, vinculando o eleitor ao candidato escolhido. |
| Urna | Gerencia ações de votação, armazenamento de votos e validação. |
| Eleicao | Controla o processo eleitoral, datas, status e regras. |
| Relatorio | Gera o resultado final e estatísticas da votação. |
| SistemaVotacao | Interface principal, coordenando todas as demais estruturas e integrando com a UI em Qt Creator. |

## **Divisão de Tarefas**

Para distribuir as atividades entre os membros do grupo, recomendo a seguinte abordagem:

## **Sugestão de Distribuição por Membro**

- Estruturar classes Eleitor e Candidato, fazer testes dessas partes. (**Robson**)  
- Implementar, Voto e Urna, com integração na votação. (**Mateus Barbosa**)  
- Criar Eleição e integração na votação. ()  
- Relatorio e lógica para gerar resultados. ()  
- Desenvolver interface gráfica e integração com a classe SistemaVotacao. (**Henrique**)  

## **Observações**

- Priorize o uso de encapsulamento e abstração nos atributos e métodos das classes.  
- Utilize relacionamentos (composição e agregação) para conectar as classes.  
- Utilize comentários explicativos em seu código
- Os .TXTs contêm nomes e CPFs fictícios no formato CSV