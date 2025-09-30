# ⚫🔴 Implementação de Árvore Rubro-Negra (Red-Black Tree) em C++

## 📜 Descrição do Projeto

Este repositório contém uma implementação educacional de uma **Árvore Rubro-Negra** (Red-Black Tree) em C++. Trata-se de um tipo de árvore de busca binária auto-balanceada que utiliza um sistema de cores (Vermelho e Preto) em seus nós para garantir que a árvore permaneça aproximadamente balanceada durante as inserções e remoções.

O resultado é uma estrutura de dados que garante a complexidade de tempo para busca, inserção e remoção em **$O(\log n)$** no pior caso.

## ⚖️ As 5 Regras da Árvore Rubro-Negra

O balanceamento é mantido através da aplicação rigorosa de 5 propriedades fundamentais:

1.  **Regra da Cor:** Todo nó é **VERMELHO** ou **PRETO**.
2.  **Regra da Raiz:** A raiz da árvore é sempre **PRETA**.
3.  **Regra das Folhas:** Todas as folhas (nós `nullptr`) são consideradas **PRETAS**.
4.  **Regra dos Filhos Vermelhos:** Se um nó é **VERMELHO**, então seus dois filhos devem ser **PRETOS**. (Isso impede que existam dois nós vermelhos em sequência direta).
5.  **Regra da Altura Negra:** Para cada nó, todos os caminhos que partem dele e chegam até seus descendentes (folhas) contêm o mesmo número de nós **PRETOS**.

## ✨ Como o Balanceamento Funciona na Inserção?

A mágica acontece na função `balancearInsercao`, que é chamada após cada nova inserção.

1.  **Inserção Inicial:** Um novo nó é sempre inserido na árvore como **VERMELHO**.
2.  **Verificação de Violação:** A inserção de um nó vermelho pode violar a "Regra da Raiz" (se for o primeiro nó) ou a "Regra dos Filhos Vermelhos" (se o pai do novo nó também for vermelho).
3.  **Correção ("Fixup"):** Para corrigir a violação, o algoritmo verifica a cor do **"tio"** do novo nó (o irmão do pai):
    -   **Caso 1: O tio é VERMELHO.** A correção é simples: o pai e o tio são recoloridos para **PRETO**, o avô é recolorido para **VERMELHO**, e a verificação continua a partir do avô, subindo na árvore.
    -   **Caso 2: O tio é PRETO (ou nulo).** A correção é mais complexa e exige **rotações** (simples ou duplas) além da recoloração para restaurar o balanceamento e as propriedades.

## 🚀 Funcionalidades do Código

-   **➕ Inserção com Balanceamento Automático**: Adiciona novos elementos e aplica a lógica de recoloração e rotações para manter as 5 propriedades da árvore.
-   **🎨 Lógica de Cores**: Todo o balanceamento é guiado pelas cores dos nós, sem a necessidade de calcular altura ou fator de balanceamento.
-   **🔄 Rotações Inteligentes**: As funções `rot_esq` e `rot_dir` foram adaptadas para atualizar os ponteiros de `pai`, algo essencial para a lógica da RB-Tree.
-   **🖨️ Impressão Detalhada**: Exibe a árvore em pré-ordem, mostrando o valor e a cor de cada nó para fácil verificação.

## 📂 Estrutura do Código

-   **`struct Vertice`**: Define a estrutura do nó, contendo `valor`, `cor` (enum), e ponteiros para os filhos `esq`, `dir` e, crucialmente, para o `pai`.
-   **`class RedBlack`**: Encapsula toda a lógica da árvore.
    -   `insere()`: Método público que inicia a inserção.
    -   `insereBST()`: Realiza uma inserção padrão de árvore de busca.
    -   `balancearInsercao()`: O coração da implementação, onde as regras são aplicadas.
    -   `rot_esq()` e `rot_dir()`: Funções de rotação que gerenciam os ponteiros de `pai`.
