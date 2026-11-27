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

typedef struct NoReferenciaIncidente {
	int id;
	struct NoReferenciaIncidente *prox;
} NoReferenciaIncidente;

typedef struct NoEquipamento {
	Equipamento *equipamento;
	struct NoEquipamento *prox;
	NoReferenciaIncidente *incidentes;
} NoEquipamento;

void criarTabelaHash(NoEquipamento *vet[TAMANHO]);
int funcaoHashId(int id);
NoEquipamento *buscarEquipamento(NoEquipamento *vet[TAMANHO], int id);
int inserirEquipamento(NoEquipamento *vet[TAMANHO], Equipamento eq);
void imprimirEquipamento(Equipamento eq);
int excluirEq(NoEquipamento *vet[TAMANHO], int id, Arv *arv);
int inserirReferenciaIncidente(NoEquipamento *eq, int idIncidente);
int removerReferenciaIncidente(NoEquipamento *eq, int idIncidente);
void imprimirIncidentesEquipamento(NoEquipamento *eq, Arv *arv);
void liberarReferencias(NoEquipamento *eq);
void liberarTabela(NoEquipamento *vet[TAMANHO]);

void criarTabelaHash(NoEquipamento *vet[TAMANHO]) {
	int i;

	for (i = 0; i < TAMANHO; i += 1) {
		vet[i] = NULL;
	}
}

int funcaoHashId(int id) {
	int indice = id % TAMANHO;

	return indice;
}

NoEquipamento *buscarEquipamento(NoEquipamento *vet[TAMANHO], int id) {
	int indice = funcaoHashId(id);
	NoEquipamento *atual = vet[indice];

	while (atual != NULL) {
		if (atual->equipamento->id == id) {
			return atual;
		}
		atual = atual->prox;
	}

	return NULL;
}

int inserirEquipamento(NoEquipamento *vet[TAMANHO], Equipamento eq) {
	NoEquipamento *novo;
	int indice;

	if (eq.id < 1000 || eq.id > 9999) {
		printf("Código de equipamento inválido.\n");
		return 0;
	}

	if (buscarEquipamento(vet, eq.id) != NULL) {
		printf("Equipamento já cadastrado.\n");
		return 0;
	}

	novo = (NoEquipamento *)malloc(sizeof(NoEquipamento));
	novo->equipamento = (Equipamento *)malloc(sizeof(Equipamento));

	*novo->equipamento = eq;
	novo->incidentes = NULL;

	indice = funcaoHashId(eq.id);
	novo->prox = vet[indice];
	vet[indice] = novo;

	return 1;
}

void imprimirEquipamento(Equipamento eq) {
	printf("\n\tID do equipamento: %d\n", eq.id);

	printf("\n\tNome do equipamento: %s\n", eq.nome);
}

int excluirEq(NoEquipamento *vet[TAMANHO], int id, Arv *arv) {
	int indice = funcaoHashId(id);
	NoEquipamento *atual = vet[indice];
	NoEquipamento *ant = NULL;
	NoReferenciaIncidente *ref;

	while (atual != NULL) {
		if (atual->equipamento->id == id) {
			ref = atual->incidentes;
			while (ref != NULL) {
				remover(arv, ref->id);
				ref = ref->prox;
			}

			if (ant == NULL) {
				vet[indice] = atual->prox;
			} else {
				ant->prox = atual->prox;
			}

			liberarReferencias(atual);
			free(atual->equipamento);
			free(atual);

			printf("Equipamento removido com sucesso.\n");
			return 1;
		}

		ant = atual;
		atual = atual->prox;
	}

	printf("Equipamento não encontrado\n");
	return 0;
}

int inserirReferenciaIncidente(NoEquipamento *eq, int idIncidente) {
	NoReferenciaIncidente *atual;
	NoReferenciaIncidente *novo;

	if (eq == NULL) {
		return 0;
	}

	atual = eq->incidentes;
	while (atual != NULL) {
		if (atual->id == idIncidente) {
			return 0;
		}
		atual = atual->prox;
	}

	novo = (NoReferenciaIncidente *)malloc(sizeof(NoReferenciaIncidente));
	novo->id = idIncidente;
	novo->prox = eq->incidentes;
	eq->incidentes = novo;

	return 1;
}

int removerReferenciaIncidente(NoEquipamento *eq, int idIncidente) {
	NoReferenciaIncidente *atual;
	NoReferenciaIncidente *ant = NULL;

	if (eq == NULL) {
		return 0;
	}

	atual = eq->incidentes;
	while (atual != NULL) {
		if (atual->id == idIncidente) {
			if (ant == NULL) {
				eq->incidentes = atual->prox;
			} else {
				ant->prox = atual->prox;
			}
			free(atual);
			return 1;
		}
		ant = atual;
		atual = atual->prox;
	}

	return 0;
}

void imprimirIncidentesEquipamento(NoEquipamento *eq, Arv *arv) {
	NoReferenciaIncidente *atual;
	NoArv *no;

	if (eq != NULL) {
		atual = eq->incidentes;
		while (atual != NULL) {
			no = busca(arv, atual->id);
			if (no != NULL) {
				imprime_No(no);
			}
			atual = atual->prox;
		}
	}
}

void liberarReferencias(NoEquipamento *eq) {
	NoReferenciaIncidente *atual;
	NoReferenciaIncidente *prox;

	if (eq != NULL) {
		atual = eq->incidentes;
		while (atual != NULL) {
			prox = atual->prox;
			free(atual);
			atual = prox;
		}
		eq->incidentes = NULL;
	}
}

void liberarTabela(NoEquipamento *vet[TAMANHO]) {
	int i;
	NoEquipamento *atual;
	NoEquipamento *prox;

	for (i = 0; i < TAMANHO; i += 1) {
		atual = vet[i];
		while (atual != NULL) {
			prox = atual->prox;
			liberarReferencias(atual);
			free(atual->equipamento);
			free(atual);
			atual = prox;
		}
		vet[i] = NULL;
	}
}

#endif
