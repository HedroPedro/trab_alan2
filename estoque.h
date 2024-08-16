#ifndef ESTOQUE_H_
#define ESTOQUE_H_

#define OUTPUT_FILE "saida.txt"
#define INSERT_TOKEN "MEDICAMENTO"
#define PRINT_TOKEN "IMPRIME_ARVORE"
#define DELETE_TOKEN "RETIRA"
#define UPDATE_PRICE_TOKEN "ATUALIZA_PRECO"
#define VERIFY_ID_TOKEN "VERIFICA_ARVORE"
#define VERIFY_DATE_TOKEN "VERIFICA_VALIDADE"
#define END_TOKEN "FIM"

typedef struct medicamento Medicamento;
typedef struct arvore Arvore;

Medicamento *CriaMedicamento(char *nome, int codigo, float valor, int *data_de_validade);//ok
Arvore *CriaArvore();//ok
Arvore *InsereArvoreMedicamento(Arvore *a, Medicamento *m);//ok
Arvore *RetiraArvoreMedicamento(Arvore *a, int id_medicamento);//ok
int VerificaArvoreMedicamento(Arvore *a, int id_medicamento);//ok
int VerificaArvoreValidade(Arvore *a, int *data);//ok
int AtualizaArvoreMedicamento(Arvore *a, int id_medicamento, float novo_preco);//ok
void ImprimeArvoreMedicamento(Arvore *a);
void LimpaArvore(Arvore *a);
#endif
