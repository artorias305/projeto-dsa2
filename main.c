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
	scanf(" %10[^\n]", equipamento.nome);

	int resultado = inserirEquipamento(vet, equipamento, arv);

	return resultado;
}

void cadastrarIncidente(NoEquipamento *vet[TAMANHO], Arv *arv) {
	NoArv incidente;
	int gravidade = 0;

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

		insere(arv, incidente.id, incidente.codigo_equipamento,
			   incidente.gravidade);
	}
}

void excluirIncidente(Arv *arv) {
	int incidenteEncontrado = 0;
	int idIncidente = 0;

	while (!incidenteEncontrado) {
		printf("Digite o ID do incidente: ");
		scanf("%d", &idIncidente);

		int achou = remover(arv, idIncidente);

		if (achou == 1) {
			break;
		}
		printf("\nINCIDENTE NÃO ENCONTRADO\n");
	}
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

	}
}

int excluirEquipamento(NoEquipamento *vet[TAMANHO]) {
	int codigoEquipmanneto;

	printf("Digite o código do equipamento: ");
	scanf(" %d", codigoEquipmanneto);

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
			// Registrar incidente
			cadastrarIncidente(tabela, incidentes);
			break;
		case 3:
			// Consultar Equipamento e Incidente
			break;
		case 4:
			imprime_InOrder(incidentes->raiz);
			break;
		case 5:
			// Excluir um incidente
			excluirIncidente(incidentes);
			break;
		case 6:
			// Excluir um Equipamento
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
