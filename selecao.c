   // Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   
#include <stdbool.h> 

   // Definições
#define TAM_TEXTO 100 // tamanho máximo dos textos
#define MAX_COMB 5 // quantidade máxima de combustíveis por veículo
#define MAX_VEICULOS 500 // capacidade máxima de veículos lidos do arquivo

// TIPOS: em struct
   // Data
typedef struct
{
	int ano;
	int mes;
	int dia;
} Data;
 
   // Veículo
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

   // Ordenação por Seleção
void selecaoModelo(Veiculo *array, int n){
    for (int i = 0; i < (n - 1); i++){
      int menor = i;
      for (int j = (i + 1); j < n; j++){
         if (strcmp(array[menor].modelo, array[j].modelo) > 0)
         {
            menor = j;
         }
      }

      // Swap
      Veiculo tmp = array[menor];
      array[menor] = array[i];
      array [i] = tmp;
   }
}
 
   // Função para a Data
Data parseData(char* s) {
	Data d;
	char* token = strtok(s, "-");   
	d.ano = atoi(token);
	token = strtok(NULL, "-");
	d.mes = atoi(token);
	token = strtok(NULL, "-");
	d.dia = atoi(token);
	return d;
}
 
void formatData(Data d, char* buffer) {
	sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

   // Função para os veículos
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
	v->cilindrada = atof(atributos[7]);
	sprintf(v->transmissao, "%s", atributos[8]);
	sprintf(v->tracao, "%s", atributos[9]);
	v->consumoCidade = atof(atributos[10]);
	v->consumoEstrada = atof(atributos[11]);
	v->co2 = atof(atributos[12]);
	v->turbo = (strcmp(atributos[13], "true") == 0);
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
 
	sprintf(buffer, "[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]",
	        v.id, v.marca, v.modelo, v.ano, v.categoria, combustiveis, v.cilindros, v.cilindrada,
	        v.transmissao, v.tracao, v.consumoCidade, v.consumoEstrada, v.co2,
	        v.turbo ? "true" : "false", dataTexto);
}

   // Função de Leitura do CSV
Veiculo* lerCsv(char* caminhoArquivo, int* n) {
	FILE* f = fopen(caminhoArquivo, "r");
	if (f == NULL)
    {
		*n = 0;
		return NULL; // arquivo não encontrado
	}
 
	Veiculo* veiculos = malloc(MAX_VEICULOS * sizeof(Veiculo));
	char linha[1024];
	int cont = 0;
 
	fgets(linha, sizeof(linha), f);
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
			free(v);
			cont++;
		}
	}
 
	fclose(f);
	*n = cont;
	return veiculos;
}
 
   // Função Principal
int main() {
	int n;
	Veiculo* veiculos = lerCsv("/tmp/veiculos.csv", &n);  // VERDE
	// Veiculo* veiculos = lerCsv("veiculos.csv", &n);

	if (veiculos == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		return 1;
	}

   selecaoModelo(veiculos, n); // ordenar antes de imprimir

	char buffer[2048];
	char linha[100];
	char entrada[100];
    int pos = 0; // qual elemento do vetor ordenado sai a seguir

	while (fgets(linha, sizeof(linha), stdin) != NULL)
	{
		// Linha vazia, não lê nada
		if (sscanf(linha, "%s", entrada) != 1) continue;
		if (strcmp(entrada, "-1") == 0) break;

      if (pos < n) {
            formatVeiculo(veiculos[pos], buffer);
            printf("%s\n", buffer);
            pos++;
        }
	}

	free(veiculos); // libera memória do vetor
	return 0;
}