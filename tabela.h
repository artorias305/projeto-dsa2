#ifndef TABELA_H
#define TABELA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int id;
	char nome[11];
} Equipamento;

typedef struct NoIdIncidente {
	int idIncidente;
	struct NoIdIncidente *prox;
} NoIdIncidente;

typedef struct NoHashEquipamento {
	Equipamento equipamento;
	NoIdIncidente *lista_incidentes;
	struct NoHashEquipamento *prox;
} NoHashEquipamento;

typedef struct {
	int M;
	NoHashEquipamento **tabela;
} Hash;

Hash *criarTabelaHash(int tamanho) {
	Hash *h = (Hash *)malloc(sizeof(Hash));
	h->M = tamanho;
	h->tabela =
		(NoHashEquipamento **)malloc(tamanho * sizeof(NoHashEquipamento *));
	for (int i = 0; i < tamanho; i++) {
		h->tabela[i] = NULL;
	}

	return h;
}

int funcaoHashId(int id, int M) {
	int indice = id % M;

	return indice;
}

NoHashEquipamento *buscarEquipamento(Hash *h, int id) {
	int indice = funcaoHashId(id, h->M);

	NoHashEquipamento *atual = h->tabela[indice];
	while (atual != NULL) {
		if (atual->equipamento.id == id) {
			return atual;
		}
		atual = atual->prox;
	}
	return NULL;
}

int inserirEquipamento(Hash *h, Equipamento eq) {
	if (eq.id < 1000 || eq.id > 9999) {
		printf("Código de equipamento inválido.\n");
		return 0;
	}

	if (buscarEquipamento(h, eq.id) != NULL) {
		printf("Equipamento já cadastrado.\n");
		return 0;
	}

	NoHashEquipamento *novo =
		(NoHashEquipamento *)malloc(sizeof(NoHashEquipamento));

	novo->equipamento = eq;
	novo->lista_incidentes = NULL;

	int indice = funcaoHashId(eq.id, h->M);
	novo->prox = h->tabela[indice];
	h->tabela[indice] = novo;

	return 1;
}

#endif