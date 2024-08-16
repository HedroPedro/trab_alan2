#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

int main(){
    Arvore *arv = CriaArvore();
    char nome[20];
    char comando[512];
    int codigo, data[3];
    float valor;
    FILE *input = fopen("entrada.txt", "r"), *to_create_or_clean = fopen(OUTPUT_FILE, "w");
    if(!input || !to_create_or_clean){
        fprintf(stderr,"IMPOSSIVEL ABRIR ARQUIVO DE ENTRADA OU ARQUIVO DE SAIDA");
        exit(1);
    }
    fclose(to_create_or_clean);


    while(fscanf(input, "%s", comando) != EOF){
        if(!strcmp(comando, INSERT_TOKEN)){
            fscanf(input, " %s %i %f %i %i %i", nome, &codigo, &valor, &data[0], &data[1], &data[2]);
            arv = InsereArvoreMedicamento(arv, CriaMedicamento(nome, codigo, valor, data));
            continue;
        }

        if(!strcmp(comando, PRINT_TOKEN)){
            ImprimeArvoreMedicamento(arv);
            continue;
        }

        if(!strcmp(comando, DELETE_TOKEN)){
            fscanf(input, " %i", &codigo);
            arv = RetiraArvoreMedicamento(arv, codigo);
            continue;
        }

        if(!strcmp(comando, UPDATE_PRICE_TOKEN)){
            fscanf(input, " %i %f", &codigo, &valor);
            AtualizaArvoreMedicamento(arv, codigo, valor);
            continue;
        }

        if(!strcmp(comando, VERIFY_ID_TOKEN)){
            fscanf(input, " %i", &codigo);
            if(!VerificaArvoreMedicamento(arv, codigo)){
                to_create_or_clean = fopen(OUTPUT_FILE, "a");
                fprintf(to_create_or_clean, "MEDICAMENTO NAO ENCONTRADO NA ARVORE\n");
                fclose(to_create_or_clean);
            }
            continue;
        }

        if(!strcmp(comando, VERIFY_DATE_TOKEN)){
            fscanf(input, " %i %i %i", &data[0], &data[1], &data[2]);
            if(!VerificaArvoreValidade(arv, data)){
                to_create_or_clean = fopen(OUTPUT_FILE, "a");
                fprintf(to_create_or_clean, "MEDICAMENTO VENCIDO NAO ENCONTRADO NA ARVORE\n");
                fclose(to_create_or_clean);
            }
            continue;
        }

        if(!strcmp(comando, END_TOKEN)){
            break;
        }
    }
    fclose(input);
    LimpaArvore(arv);
    return 0;
}
