#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NoArv {
	int id;
	int gravidade;
	int codigo_equipamento;
	struct NoArv *esq;
	struct NoArv *dir;
} NoArv;

typedef struct {
	NoArv *raiz;
} Arv;

Arv *Criar_Arvore();
int ArvVazia(Arv *arv);

int insere(Arv *arv, int num, int codEquip, int gravidade);
NoArv *busca(Arv *arv, int num);

int remover(Arv *RAIZ, int num);
NoArv *remover_aux(NoArv *pai, int num, int *achou);

void imprime_No(NoArv *no);
void imprime_InOrder(NoArv *pai);

void liberaArvore(NoArv *pai);

Arv *Criar_Arvore() {
	Arv *arv = (Arv *)malloc(sizeof(Arv));

	arv->raiz = NULL;

	return arv;
}

int ArvVazia(Arv *arv) {
	if (arv->raiz == NULL) {
		return 1;
	} else {
		return 0;
	}
}

int insere(Arv *arv, int num, int codEquip, int gravidade) {
	int flag;
	NoArv *Pai;
	NoArv *novo;

	if (num < 10 || num > 99 || codEquip < 1000 || codEquip > 9999 ||
		gravidade < 1 || gravidade > 3) {
		return -1;
	}

	novo = (NoArv *)malloc(sizeof(NoArv));

	novo->id = num;
	novo->codigo_equipamento = codEquip;
	novo->gravidade = gravidade;
	novo->esq = NULL;
	novo->dir = NULL;

	if (arv->raiz == NULL) {
		arv->raiz = novo;
		return 1;
	} else {
		Pai = arv->raiz;
		flag = 0;
		while (flag == 0) {
			if (Pai->id < num) {
				if (Pai->dir == NULL) {
					Pai->dir = novo;
					flag = 1;
				} else {
					Pai = Pai->dir;
				}
			} else {
				if (Pai->id > num) {
					if (Pai->esq == NULL) {
						Pai->esq = novo;
						flag = 1;
					} else {
						Pai = Pai->esq;
					}
				} else {
					flag = 2;
					free(novo);
				}
			}
		}
	}

	if (flag == 1) {
		return 1;
	} else {
		return 0;
	}
}

NoArv *busca(Arv *arv, int num) {
	int flag;
	NoArv *Pai;

	if (ArvVazia(arv)) {
		return NULL;
	}

	Pai = arv->raiz;
	flag = 0;

	while (flag == 0) {
		if (num > Pai->id) {
			if (Pai->dir == NULL) {
				flag = 2;
			} else {
				Pai = Pai->dir;
			}
		} else {
			if (num < Pai->id) {
				if (Pai->esq == NULL) {
					flag = 2;
				} else {
					Pai = Pai->esq;
				}
			} else {
				flag = 1;
			}
		}
	}

	if (flag == 1) {
		return Pai;
	} else {
		return NULL;
	}
}

int remover(Arv *RAIZ, int num) {
	int achou = 0;
	RAIZ->raiz = remover_aux(RAIZ->raiz, num, &achou);
	return achou;
}

NoArv *remover_aux(NoArv *pai, int id, int *achou) {
	if (pai == NULL) {
		return NULL;
	} else {
		if (id > pai->id) {
			pai->dir = remover_aux(pai->dir, id, achou);
		} else {
			if (id < pai->id) {
				pai->esq = remover_aux(pai->esq, id, achou);
			} else {
				*achou = 1;

				if (pai->dir == NULL && pai->esq == NULL) {
					free(pai);
					pai = NULL;
				} else {
					if (pai->esq == NULL) {
						NoArv *aux = pai;
						pai = pai->dir;
						free(aux);
					} else {
						if (pai->dir == NULL) {
							NoArv *aux = pai;
							pai = pai->esq;
							free(aux);
						} else {
							NoArv *aux;
							aux = pai->esq;
							while (aux->dir != NULL) {
								aux = aux->dir;
							}
							pai->id = aux->id;
							pai->codigo_equipamento = aux->codigo_equipamento;
							pai->gravidade = aux->gravidade;
							aux->id = id;
							pai->esq = remover_aux(pai->esq, id, achou);
						}
					}
				}
			}
		}
	}
	return pai;
}

void imprime_No(NoArv *no) {
	if (no != NULL) {
		printf("Incidente %02d | Equipamento: %d | Gravidade: %d\n", no->id,
			   no->codigo_equipamento, no->gravidade);
	}
}

void imprime_InOrder(NoArv *pai) {
	if (pai != NULL) {
		imprime_InOrder(pai->esq);
		imprime_No(pai);
		imprime_InOrder(pai->dir);
	}
}

void liberaArvore(NoArv *pai) {
	if (pai != NULL) {
		liberaArvore(pai->esq);
		liberaArvore(pai->dir);
		free(pai);
	}
}

#endif
