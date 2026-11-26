#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"
#include "tabela.h"

void printMenu() {
	printf(
		"======================================================================"
		"\nEscolha uma opção:\n\t1 - Cadastrar Equipamento "
		"\n\t2 - Remover Incidente\n\t3 - Consultar Equipamento e Incidente "
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
	int equipamentoEncontrado = 0;

    printf("Digite o ID do incidente: ");
    scanf("%d", &incidente.id);

    printf("Digite o código do equipamento: ");
    scanf(" %d", &incidente.codigo_equipamento);

	printf("Digite o nível de gravidade: ");
    scanf(" %d", &incidente.gravidade);

	while (gravidade > 3 || gravidade < 1) {
		printf("Digite o nível de gravidade: ");
		scanf(" %d", &incidente.gravidade);
		gravidade = &incidente.gravidade;
	}

	while (!equipamentoEncontrado) {
		NoEquipamento *eq = buscarEquipamento(vet, &incidente.codigo_equipamento, arv);
		if (eq != NULL) {
			break;
		}
		printf("\nEQUIPAMENTO NÃO ENCONTRADO\n");
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
			// Listar todos os Incidentes
			imprime_InOrder(incidentes);
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
