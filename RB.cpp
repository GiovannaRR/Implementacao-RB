#include <iostream>
#include <string>

using namespace std;

enum Cor { VERMELHO, PRETO };

struct Vertice {
    int valor;
    Cor cor;
    Vertice *esq, *dir, *pai;

    // Construtor: Novo nó é sempre inserido como VERMELHO
    Vertice(int v) : valor(v), cor(VERMELHO), esq(nullptr), dir(nullptr), pai(nullptr) {}
};

class RedBlack {
public:
    RedBlack() : raiz(nullptr) {}

    void insere(int valor) {
        Vertice* novoVertice = new Vertice(valor);
        
        //Realiza uma inserção de Árvore de Busca Binária normal
        raiz = insereBST(raiz, novoVertice);
        
        //Corrige violações das propriedades da Árvore Rubro-Negra
        balancearInsercao(novoVertice);
    }

    void imprime() {
        imprime(raiz);
    }

private:
    Vertice *raiz;

    // Rotações agora precisam atualizar o ponteiro do pai
    void rot_esq(Vertice *v) {
        Vertice *u = v->dir;
        v->dir = u->esq;

        if (u->esq != nullptr) {
            u->esq->pai = v;
        }

        u->pai = v->pai;

        if (v->pai == nullptr) {
            raiz = u;
        } else if (v == v->pai->esq) {
            v->pai->esq = u;
        } else {
            v->pai->dir = u;
        }

        u->esq = v;
        v->pai = u;
    }

    void rot_dir(Vertice *v) {
        Vertice *u = v->esq;
        v->esq = u->dir;

        if (u->dir != nullptr) {
            u->dir->pai = v;
        }
        
        u->pai = v->pai;

        if (v->pai == nullptr) {
            raiz = u;
        } else if (v == v->pai->esq) {
            v->pai->esq = u;
        } else {
            v->pai->dir = u;
        }

        u->dir = v;
        v->pai = u;
    }
    
    // Inserção padrão de uma Árvore de Busca Binária
    Vertice* insereBST(Vertice* raiz_subarvore, Vertice* v) {
        if (raiz_subarvore == nullptr) {
            return v;
        }

        if (v->valor < raiz_subarvore->valor) {
            raiz_subarvore->esq = insereBST(raiz_subarvore->esq, v);
            raiz_subarvore->esq->pai = raiz_subarvore;
        } else if (v->valor > raiz_subarvore->valor) {
            raiz_subarvore->dir = insereBST(raiz_subarvore->dir, v);
            raiz_subarvore->dir->pai = raiz_subarvore;
        }

        return raiz_subarvore;
    }
    
    void balancearInsercao(Vertice *v) {
        // Itera enquanto o pai do nó atual for vermelho (violação da propriedade)
        while (v != raiz && v->pai->cor == VERMELHO) {
            Vertice *pai = v->pai;
            Vertice *avo = pai->pai;

            // Caso A: O pai é o filho da ESQUERDA do avô
            if (pai == avo->esq) {
                Vertice *tio = avo->dir;
                
                // Caso 1: O tio é VERMELHO -> Apenas recolorir
                if (tio != nullptr && tio->cor == VERMELHO) {
                    pai->cor = PRETO;
                    tio->cor = PRETO;
                    avo->cor = VERMELHO;
                    v = avo; 
                } else {
                    // Caso 2: O tio é PRETO e o nó é um filho à DIREITA (forma um "triângulo")
                    if (v == pai->dir) {
                        rot_esq(pai);
                        v = pai; 
                        pai = v->pai;
                    }
                    
                    // Caso 3: O tio é PRETO e o nó é um filho à ESQUERDA (forma uma "linha")
                    rot_dir(avo);
                    swap(pai->cor, avo->cor);
                    v = pai;
                }
            }
            // Caso B: O pai é o filho da DIREITA do avô (simétrico ao Caso A)
            else {
                Vertice *tio = avo->esq;

                // Caso 1: O tio é VERMELHO -> Apenas recolorir
                if (tio != nullptr && tio->cor == VERMELHO) {
                    pai->cor = PRETO;
                    tio->cor = PRETO;
                    avo->cor = VERMELHO;
                    v = avo;
                } else {
                    // Caso 2: O tio é PRETO e o nó é um filho à ESQUERDA
                    if (v == pai->esq) {
                        rot_dir(pai);
                        v = pai;
                        pai = v->pai;
                    }

                    // Caso 3: O tio é PRETO e o nó é um filho à DIREITA
                    rot_esq(avo);
                    swap(pai->cor, avo->cor);
                    v = pai;
                }
            }
        }
        
        // Garante que a raiz seja sempre preta (Propriedade 2)
        raiz->cor = PRETO;
    }

    void imprime(Vertice* v) {
        if (v == nullptr) return;
        
        string cor_str = (v->cor == VERMELHO) ? "VERMELHO" : "PRETO";
        cout << v->valor << " (" << cor_str << ")" << endl;
        
        imprime(v->esq);
        imprime(v->dir);
    }
};

int main() {
    RedBlack t;

    t.insere(100);
    t.insere(50);
    t.insere(200);
    t.insere(30);
    t.insere(60);
    t.insere(55);

    cout << "--- Arvore Rubro-Negra ---" << endl;
    t.imprime();
    cout << "--------------------------" << endl;

    return 0;
}