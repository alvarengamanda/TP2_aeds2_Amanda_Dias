#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   
#include <stdbool.h>  
 
#define TAM_TEXTO 100 // tamanho máximo dos textos
#define MAX_COMB 5 // quantidade máxima de combustíveis por veículo
#define MAX_VEICULOS 500 // capacidade máxima de veículos lidos do arquivo
 
// TIPOS: em struct
    // Data: guarda ano, mês e dia
typedef struct
{
	int ano;
	int mes;
	int dia;
} Data;
 
    // Veiculo: guarda todos os dados de uma linha do CSV
typedef struct
{
	int id;
	char marca[TAM_TEXTO];
	char modelo[TAM_TEXTO];
	int ano;
	char categoria[TAM_TEXTO];
	char combustivel[MAX_COMB][TAM_TEXTO];
	int cilindros;
	double cilindrada;
	char transmissao[TAM_TEXTO];
	char tracao[TAM_TEXTO];
	double consumoCidade;
	double consumoEstrada;
	double co2;
	bool turbo;
	Data dataRegistro;
} Veiculo;
 
// Função para a Data
    // Converte um texto "ano-mês-dia" em uma Data
Data parseData(char* s) {
    // strtok: quebra o texto em pedaços a partir de um delimitador
    // atoi: converte texto em int
    // token: cada pedaço que o strtok forneceu
	Data d; // Java: Data d = new Data(ano, mes, dia); 
	char* token = strtok(s, "-");   
	d.ano = atoi(token);
	token = strtok(NULL, "-");
	d.mes = atoi(token);
	token = strtok(NULL, "-");
	d.dia = atoi(token);
	return d;
}
 
// Escreve a data como "dia / mês / ano"
void formatData(Data d, char* buffer) {
	// buffer: reserva o espaço para o texto
	sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}
 
// Função para os Veículos 
    // Converte uma linha do CSV em um Veiculo alocado na memória (malloc)
    // Devolve NULL se a linha tiver menos de 15 colunas (todos os atributos)
Veiculo* parseVeiculo(char* s) {
	char* atributos[15];
	int i = 0;
	char* token = strtok(s, ",\r\n");
	while (token != NULL && i < 15)
    {
		atributos[i] = token;
		i++;
		token = strtok(NULL, ",\r\n");
	}
	if (i < 15)
    {
		return NULL; // linha incompleta
	}
 
	Veiculo* v = malloc(sizeof(Veiculo));
 
	v->id = atoi(atributos[0]);
	sprintf(v->marca, "%s", atributos[1]);
	sprintf(v->modelo, "%s", atributos[2]);
	v->ano = atoi(atributos[3]);
	sprintf(v->categoria, "%s", atributos[4]);
 
	// Junta os combustíveis em um único texto, separados por ";"
	for (int j = 0; j < MAX_COMB; j++)
    {
		v->combustivel[j][0] = '\0';
	}
	int k = 0;
	char* comb = strtok(atributos[5], ";");
	while (comb != NULL && k < MAX_COMB)
    {
		sprintf(v->combustivel[k], "%s", comb);
		k++;
		comb = strtok(NULL, ";");
	}
 
	v->cilindros = atoi(atributos[6]);
	v->cilindrada = atof(atributos[7]); // atof: converte texto em double
	sprintf(v->transmissao, "%s", atributos[8]);
	sprintf(v->tracao, "%s", atributos[9]);
	v->consumoCidade = atof(atributos[10]);
	v->consumoEstrada = atof(atributos[11]);
	v->co2 = atof(atributos[12]);
	v->turbo = (strcmp(atributos[13], "true") == 0); // strcmp: devolve 0 quando os textos são iguais
	v->dataRegistro = parseData(atributos[14]);
 
	return v;
}
 
// Escreve o veículo como texto no buffer
void formatVeiculo(Veiculo v, char* buffer) {
	// Monta o texto dos combustíveis
	char combustiveis[TAM_TEXTO * MAX_COMB];
	int pos = 0;
	pos += sprintf(combustiveis + pos, "[");
	for (int i = 0; i < MAX_COMB && v.combustivel[i][0] != '\0'; i++)
	{
		if (i > 0)
		{
			pos += sprintf(combustiveis + pos, ",");
		}
		pos += sprintf(combustiveis + pos, "%s", v.combustivel[i]);
	}
	pos += sprintf(combustiveis + pos, "]");
	combustiveis[pos] = '\0';
 
	// Formata a data usando a função da Data
	char dataTexto[30];
	formatData(v.dataRegistro, dataTexto);
 
    // %g = double sem zeros à direita
	sprintf(buffer, "[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]",
	        v.id, v.marca, v.modelo, v.ano, v.categoria, combustiveis, v.cilindros, v.cilindrada,
	        v.transmissao, v.tracao, v.consumoCidade, v.consumoEstrada, v.co2,
	        v.turbo ? "true" : "false", dataTexto);
}
 
// Função de Leitura do CSV
Veiculo* lerCsv(char* caminhoArquivo, int* n) {
	FILE* f = fopen(caminhoArquivo, "r"); // abre o arquivo para leitura
	if (f == NULL)
    {
		*n = 0;
		return NULL; // arquivo não encontrado
	}
 
	Veiculo* veiculos = malloc(MAX_VEICULOS * sizeof(Veiculo));
	char linha[1024];
	int cont = 0;
 
	fgets(linha, sizeof(linha), f); // lê e descarta o cabeçalho
	while (fgets(linha, sizeof(linha), f) != NULL && cont < MAX_VEICULOS)
    {
        // pula linhas em branco
		if (linha[0] == '\n' || linha[0] == '\r' || linha[0] == '\0')
        {
			continue;
		}

		Veiculo* v = parseVeiculo(linha);
		if (v != NULL)
        {
			veiculos[cont] = *v;
			free(v); // libera a memória do Veiculo temporário
			cont++;
		}
	}
 
	fclose(f); // fecha o arquivo
	*n = cont; // quantos veículos foram lidos
	return veiculos;
}

// Troca duas structs Veiculo de lugar
void trocar(Veiculo* a, Veiculo* b) {
	Veiculo temp = *a;
	*a = *b;
	*b = temp;
}

// Ordena o vetor de veiculos por modelo, usando ordenação por seleção
void selecao(Veiculo* veiculos, int n) {
	for (int i = 0; i < n - 1; i++) {
		int indiceMenor = i;

		// Procura o menor modelo entre i+1 e o fim
		for (int j = i + 1; j < n; j++) {
			if (strcmp(veiculos[j].modelo, veiculos[indiceMenor].modelo) < 0) {
				indiceMenor = j;
			}
		}

		// Se achou um menor diferente de i, troca
		if (indiceMenor != i) {
			trocar(&veiculos[i], &veiculos[indiceMenor]);
		}
	}
}

// Busca binária por modelo. Devolve 1 se encontrou, 0 se não encontrou.
// Pré-condição: veiculos já está ordenado por modelo.
int buscaBinaria(Veiculo* veiculos, int n, char* modeloProcurado) {
	int inicio = 0;
	int fim = n - 1;

	while (inicio <= fim) {
		int meio = (inicio + fim) / 2;
		int cmp = strcmp(modeloProcurado, veiculos[meio].modelo);

		if (cmp == 0) {
			return 1; // achou
		} else if (cmp < 0) {
			fim = meio - 1; // procurado é "menor": olha só a metade da esquerda
		} else {
			inicio = meio + 1; // procurado é "maior": olha só a metade da direita
		}
	}

	return 0; // não achou
}

// Função Principal
int main() {
	int n;
	Veiculo* veiculos = lerCsv("/tmp/veiculos.csv", &n);  // VERDE
	// Veiculo* veiculos = lerCsv("veiculos.csv", &n);

	if (veiculos == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		return 1;
	}

	Veiculo* selecionados = malloc(n * sizeof(Veiculo));
	int cont = 0;

	char linha[100];
	char entrada[100];

	// Parte 1: ids até -1, monta o arranjo-base
	while (fgets(linha, sizeof(linha), stdin) != NULL) {
		if (sscanf(linha, "%s", entrada) != 1) continue;
		if (strcmp(entrada, "-1") == 0) break;

		int id = atoi(entrada);

		for (int i = 0; i < n; i++) {
			if (veiculos[i].id == id) {
				selecionados[cont] = veiculos[i];
				cont++;
				break;
			}
		}
	}

	// Ordena o arranjo-base por modelo, para a busca binária funcionar
	selecao(selecionados, cont);

	// Parte 2: várias linhas com modelo, até "FIM"
	while (fgets(linha, sizeof(linha), stdin) != NULL) {
		if (sscanf(linha, "%[^\n]", entrada) != 1) continue;
		if (strcmp(entrada, "FIM") == 0) break;

		if (buscaBinaria(selecionados, cont, entrada)) {
			printf("SIM\n");
		} else {
			printf("NAO\n");
		}
	}

	free(veiculos);
	free(selecionados);
	return 0;
}