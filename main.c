#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"
#include "tabela.h"

void printMenu() {
	printf(
		"======================================================================"
		"\nEscolha uma opção:\n\t1 - Cadastrar Equipamento "
		"\n\t2 - Registrar Incidente\n\t3 - Consultar Equipamento e Incidente "
		"\n\t4 - Listar todos os incidentes"
		"\n\t5 - Excluir um incidente\n\t6 "
		"- Excluir um equipameno\n\t7 - Finalizar"
		"\n===================================================================="
		"=="
		"\nEscolha: ");
}

int cadastrarEquipamento(NoEquipamento *vet[TAMANHO], Arv *arv) {
	Equipamento equipamento;

	printf("Digite o ID do equipamento: ");
	scanf("%d", &equipamento.id);

	printf("Digite o nome do equipamento: ");
	scanf("%10s", equipamento.nome);

	int resultado = inserirEquipamento(vet, equipamento, arv);

	return resultado;
}

void cadastrarIncidente(NoEquipamento *vet[TAMANHO], Arv *arv) {
	NoArv incidente;

	do {
		printf("Digite o ID do incidente: ");
		scanf("%d", &incidente.id);
	} while (incidente.id < 10 || incidente.id > 99);

	do {
		printf("Digite o código do equipamento: ");
		scanf(" %d", &incidente.codigo_equipamento);
	} while (incidente.codigo_equipamento < 1000 ||
			 incidente.codigo_equipamento > 9999);

	NoEquipamento *eq =
		buscarEquipamento(vet, incidente.codigo_equipamento, arv);

	if (eq == NULL) {
		printf("\nEQUIPAMENTO NÃO ENCONTRADO\n");
	} else {
		do {
			printf("Digite o nível de gravidade: ");
			scanf(" %d", &incidente.gravidade);
		} while (incidente.gravidade > 3 || incidente.gravidade < 1);

		int resultado = insere(arv, incidente.id, incidente.codigo_equipamento,
							   incidente.gravidade);

		if (resultado == 1) {
			printf("Incidente registrado.\n");
		} else if (resultado == 0) {
			printf("Já existe um incidente com esse ID.\n");
		} else {
			printf("Não foi possível cadastrar: dados inválidos.\n");
		}
	}
}

void excluirIncidente(Arv *arv) {
	int idIncidente = 0;

	do {
		printf("Digite o ID do incidente: ");
		scanf("%d", &idIncidente);

		int achou = remover(arv, idIncidente);

		if (achou) {
			printf("Incidente removido.\n");
			break;
		}

		printf("Incidente não encontrado.\n");

	} while (idIncidente < 10 || idIncidente > 99);
}

void consultarEqEIncidentes(NoEquipamento *vet[TAMANHO], Arv *arv) {
	int codigo_equipamento = 0;
	do {
		printf("Insira o código do equipamento: ");
		scanf("%d", &codigo_equipamento);
	} while (codigo_equipamento < 1000 || codigo_equipamento > 9999);

	NoEquipamento *eq = buscarEquipamento(vet, codigo_equipamento, arv);

	if (eq == NULL) {
		printf("Equipamento não encontrado\n");
	} else {
		imprimirEquipamento(*eq->equipamento);
	}

	printf("\nINCIDENTES RELACIONADOS: \n\n");

	imprime_InOrder(arv->raiz, eq->equipamento->id);
}

int excluirEquipamento(NoEquipamento *vet[TAMANHO]) {
	int codigoEquipmanneto = 0;

	printf("Digite o código do equipamento: ");
	scanf(" %d", &codigoEquipmanneto);

	int resultado = excluirEq(vet, codigoEquipmanneto);
	return resultado;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	int escolha = -1;

	NoEquipamento *tabela[TAMANHO];
	criarTabelaHash(tabela);
	Arv *incidentes = Criar_Arvore();

	do {
		printMenu();
		scanf("%d", &escolha);

		switch (escolha) {
		case 1:
			cadastrarEquipamento(tabela, incidentes);
			break;
		case 2:
			cadastrarIncidente(tabela, incidentes);
			break;
		case 3:
			consultarEqEIncidentes(tabela, incidentes);
			break;
		case 4:
			imprime_InOrder(incidentes->raiz, 0);
			break;
		case 5:
			excluirIncidente(incidentes);
			break;
		case 6:
			excluirEquipamento(tabela);
			break;
		default:
			if (escolha != 7) {
				printf("Escolha inv�lida.\n");
			}
			break;
		}
	} while (escolha != 7);

	liberaArvore(incidentes->raiz);
	free(incidentes);

	return 0;
}
