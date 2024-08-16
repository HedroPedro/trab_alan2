#include "estoque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct medicamento {
    char nome[20];
    int codigo;
    float valor;
    int data[3];
};

struct arvore {
    Medicamento *m;
    Arvore *esquerda;
    Arvore *direita;
};

Medicamento *CriaMedicamento(char *nome, int codigo, float valor, int *data_de_validade){
    Medicamento *novo_med = (Medicamento *) malloc(sizeof(Medicamento));
    if(novo_med == NULL) {
        fprintf(stderr, "Erro ao criar medicamento, espaço totalmente alocado!");
        exit(-1);
    }
    strcpy(novo_med->nome, nome);
    novo_med->codigo = codigo;
    novo_med->valor = valor;
    for(int i = 0; i < 3; i++){
        novo_med->data[i] = data_de_validade[i];
    }
    return novo_med;
}

Arvore *CriaArvore() {
    return NULL;
}

Arvore *InsereArvoreMedicamento(Arvore *a, Medicamento *m){
    if(a == NULL){
        FILE *write = fopen(OUTPUT_FILE, "a");
        a = (Arvore *) malloc(sizeof(Arvore));
        if(a == NULL) {
            fprintf(stderr, "Erro ao criar no de arvore");
            exit(-1);
        }
        a->m = m;
        a->direita = a->esquerda = NULL;
        fprintf(write, "MEDICAMENTO %s %i INSERIDO\n", m->nome, m->codigo);
        fclose(write);
    }else if(a->m->codigo > m->codigo){
        a->esquerda = InsereArvoreMedicamento(a->esquerda, m);
    }else if(a->m->codigo <= m->codigo){
        a->direita = InsereArvoreMedicamento(a->direita, m);
    }

    return a;
}

Arvore *RetiraArvoreMedicamento(Arvore *a, int id_medicamento){
    if(a == NULL) return NULL;

    if(a->m->codigo > id_medicamento){
      a->esquerda = RetiraArvoreMedicamento(a->esquerda, id_medicamento);
    }else if(a->m->codigo < id_medicamento){
        a->direita = RetiraArvoreMedicamento(a->direita, id_medicamento);
    }else{
        if(a->direita == NULL && a->esquerda == NULL){
            FILE *write = fopen(OUTPUT_FILE, "a");
            fprintf(write, "MEDICAMENTO %s %i RETIRADO\n", a->m->nome, a->m->codigo);
            fclose(write);
            free(a->m);
            free(a);
            return NULL;
        }else if(a->esquerda == NULL){
            FILE *write = fopen(OUTPUT_FILE, "a");
            fprintf(write, "MEDICAMENTO %s %i RETIRADO\n", a->m->nome, a->m->codigo);
            fclose(write);
            Arvore *t = a;
            a = a->direita;
            free(t->m);
            free(t);
        }else if(a->direita == NULL){
            FILE *write = fopen(OUTPUT_FILE, "a");
            fprintf(write, "MEDICAMENTO %s %i RETIRADO\n", a->m->nome, a->m->codigo);
            fclose(write);
            Arvore *t = a;
            a = a->esquerda;
            free(t->m);
            free(t);
        }else {
            Arvore *t = a->esquerda;
            while(t->direita){
                t = t->direita;
            }
            a->m->codigo = t->m->codigo;
            a->m->valor = t->m->valor;
            for(int i = 0; i < 3; i++){
                a->m->data[i] = t->m->data[i];
            }
            strcpy(a->m->nome, t->m->nome);
            t->m->codigo = id_medicamento;
            a->esquerda = RetiraArvoreMedicamento(a->esquerda, id_medicamento);
        }
    }

    return a;
}

int VerificaArvoreMedicamento(Arvore *a, int id_medicamento){
    if(a == NULL) return 0;

    if(a->m->codigo == id_medicamento){
        FILE *write = fopen(OUTPUT_FILE, "a");
        fprintf(write, "MEDICAMENTO %s %i ENCONTRADO\n", a->m->nome, a->m->codigo);
        fclose(write);
        return 1;
    }

    if(a->m->codigo > id_medicamento) {
        return 0 || VerificaArvoreMedicamento(a->esquerda, id_medicamento);
    }

    return 0 || VerificaArvoreMedicamento(a->direita, id_medicamento);
}

int VerificaArvoreValidade(Arvore *a, int *data){
    if(a == NULL){
        return 0;
    }

    int ladoEsq = VerificaArvoreValidade(a->esquerda, data);
    int middle = (a->m->data[2] < data[2]) || (a->m->data[1] < data[1] && a->m->data[2] <= a->m->data[2])
    || (a->m->data[0] < data[0] && a->m->data[1] <= data[1] && a->m->data[2] <= data[2]);
    int ladoDir = VerificaArvoreValidade(a->direita, data);
    if(middle){
        FILE *output = fopen(OUTPUT_FILE, "a");
        fprintf(output, "MEDICAMENTO %s %i VENCIDO\n",a->m->nome, a->m->codigo);
        fclose(output);
    }

    return ladoEsq || middle || ladoDir;
}

int AtualizaArvoreMedicamento(Arvore *a, int id_medicamento, float novo_preco){
    if(a == NULL) return 0;

    if(a->m->codigo == id_medicamento){
        FILE *output = fopen(OUTPUT_FILE, "a");
        fprintf(output, "PRECO ATUALIZADO %s %i %.1f\n", a->m->nome, a->m->codigo, novo_preco);
        fclose(output);
        a->m->valor = novo_preco;
        return 1;
    }

    if(a->m->codigo > id_medicamento){
        return 0 || AtualizaArvoreMedicamento(a->esquerda, id_medicamento, novo_preco);
    }

    return 0 || AtualizaArvoreMedicamento(a->direita, id_medicamento, novo_preco);
}

void LimpaArvore(Arvore *a){
    if(a != NULL){
        LimpaArvore(a->esquerda);
        LimpaArvore(a->direita);
        free(a->m);
        free(a);
    }
}

void ImprimeArvoreMedicamento(Arvore *a){
    if(a==NULL) return;
    ImprimeArvoreMedicamento(a->esquerda);
    FILE *write = fopen(OUTPUT_FILE, "a");
    fprintf(write, "%s %i %.2f %i %i %i\n", a->m->nome, a->m->codigo, a->m->valor, a->m->data[0], a->m->data[1], a->m->data[2]);
    fclose(write);
    ImprimeArvoreMedicamento(a->direita);
}
