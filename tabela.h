#ifndef TABELA_H
#define TABELA_H

#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 67

typedef struct {
	int id;
	char nome[11];
} Equipamento;

typedef struct NoEquipamento {
	int idIncidente;
	Equipamento *equipamento;
	struct NoEquipamento *prox;
} NoEquipamento;

void criarTabelaHash(NoEquipamento *vet[TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        vet[i] = NULL;
    }
}

int funcaoHashId(int id) {
	int indice = id % TAMANHO;

	return indice;
}

Equipamento *buscarEquipamento(NoEquipamento *vet[TAMANHO], int id, Arv *arv) {
	int indice = funcaoHashId(id);

	NoEquipamento *atual = vet[indice];
	while (atual != NULL) {
	    NoArv *no = busca(arv, id);
		if (no) {
		    return atual->equipamento;
		}
		atual = atual->prox;
	}
	return NULL;
}

int inserirEquipamento(NoEquipamento *vet[TAMANHO], Equipamento eq, Arv *arv) {
	if (eq.id < 1000 || eq.id > 9999) {
		printf("Código de equipamento inválido.\n");
		return 0;
	}

	if (buscarEquipamento(vet, eq.id, arv) != NULL) {
		printf("Equipamento já cadastrado.\n");
		return 0;
	}

	NoEquipamento *novo = (NoEquipamento *)malloc(sizeof(Equipamento));

	novo->equipamento = &eq;
	novo->idIncidente = NULL;

	int indice = funcaoHashId(eq.id);
	novo->prox = vet[indice];
	vet[indice] = novo;

	return 1;
}

#endif
