# Trabalho Prático II — Explorando Veículos

Repositório com os programas desenvolvidos no **Trabalho Prático II**, cujo tema é a manipulação de um dataset de veículos. O trabalho reúne 13 programas em **Java** e **C**, abordando modelagem de dados, algoritmos de ordenação, pesquisa e estruturas de dados.

> **Disciplina:** Algoritmos e Estrutura de Dados II
> **Instituição:** PUC Minas Unidade Coração Eucarístico
> **Autor:** Amanda Alvarenga Dias

---

## Sumário

- [Sobre o dataset](#sobre-o-dataset)
- [Modelo de dados](#modelo-de-dados)
- [Programas do trabalho](#programas-do-trabalho)
- [Descrição dos programas](#descrição-dos-programas)
- [Estrutura do repositório](#estrutura-do-repositório)
- [Restrições do trabalho](#restrições-do-trabalho)
- [Como compilar e executar](#como-compilar-e-executar)
- [Conceitos abordados](#conceitos-abordados)

---

## Sobre o dataset

O dataset **Explorando Veículos** é uma coleção diversificada de veículos de diferentes fabricantes, categorias e anos, reunindo modelos com variadas características mecânicas e tecnologias de propulsão. A base contempla veículos com diferentes tipos de combustível, transmissões, sistemas de tração, cilindradas e níveis de consumo, permitindo uma visão ampla da evolução e da diversidade do setor automotivo.

Com esses dados é possível explorar padrões como:

- a relação entre características do motor e o consumo de combustível;
- diferenças de eficiência entre categorias de veículos;
- variações nas emissões de CO2;
- a presença de diferentes tecnologias de transmissão e propulsão ao longo dos anos.

Cada registro representa uma configuração única de veículo, formando um conjunto de dados rico e multifacetado. O dataset estimula o desenvolvimento de soluções que simulam aplicações do mundo real, como sistemas de busca, recomendação e organização de informações, e permite explorar organização e tipagem de dados, modelagem de entidades do mundo real, manipulação de estruturas (listas, registros etc.), consultas, filtragens e ordenações.

---

## Modelo de dados

Cada linha do arquivo CSV representa um veículo, com **15 colunas separadas por vírgula**, nesta ordem:

| # | Atributo | Tipo (Java) | Tipo (C) | Descrição |
|---|----------|-------------|----------|-----------|
| 0 | `id` | `int` | `int` | Identificador do veículo |
| 1 | `marca` | `String` | `char[]` | Fabricante |
| 2 | `modelo` | `String` | `char[]` | Modelo |
| 3 | `ano` | `int` | `int` | Ano do modelo |
| 4 | `categoria` | `String` | `char[]` | Categoria do veículo |
| 5 | `combustivel` | `String[]` | `char[][]` | Tipos de combustível (vários valores separados por `;`) |
| 6 | `cilindros` | `int` | `int` | Quantidade de cilindros |
| 7 | `cilindrada` | `double` | `double` | Cilindrada do motor |
| 8 | `transmissao` | `String` | `char[]` | Tipo de transmissão |
| 9 | `tracao` | `String` | `char[]` | Sistema de tração |
| 10 | `consumoCidade` | `double` | `double` | Consumo no ciclo urbano |
| 11 | `consumoEstrada` | `double` | `double` | Consumo no ciclo rodoviário |
| 12 | `co2` | `double` | `double` | Emissão de CO2 |
| 13 | `turbo` | `boolean` | `bool` | Indica se o veículo possui turbo |
| 14 | `dataRegistro` | `Data` | `Data` | Data de registro, no formato `ano-mês-dia` |

O tipo **`Data`** guarda três inteiros: `ano`, `mes` e `dia`.

### Exemplo de linha do CSV

```csv
15337,Saab,9-3 SPORT SEDAN,2012,Compact Cars,Gasoline,4,2.0,Manual,Front-Wheel Drive,8.5,14.03,220.9,true,2011-03-01
```

Veículos com mais de um combustível usam `;` dentro da coluna 5, por exemplo `Gasoline;Electricity`.

### Formato de saída

Cada veículo é impresso em uma linha, com os campos separados por ` ## `, entre colchetes, e a data no formato `dia / mês / ano`:

```
[15337 ## Saab ## 9-3 SPORT SEDAN ## 2012 ## Compact Cars ## Gasoline ## 4 ## 2.0 ## Manual ## Front-Wheel Drive ## 8.5 ## 14.03 ## 220.9 ## true ## 1 / 3 / 2011]
```

---

## Programas do trabalho

| # | Programa | Linguagem | Categoria | Status |
|---|----------|-----------|-----------|--------|
| 1 | Modelagem | Java | Modelagem | ✅ Concluído |
| 2 | Modelagem | C | Modelagem | ✅ Concluído |
| 3 | Ordenação por seleção | C | Ordenação | ⬜ Pendente |
| 4 | Ordenação por inserção | Java | Ordenação | ⬜ Pendente |
| 5 | Ordenação por Counting Sort | C | Ordenação | ⬜ Pendente |
| 6 | Ordenação por Radix Sort | C | Ordenação | ⬜ Pendente |
| 7 | Ordenação por Bucket Sort | Java | Ordenação | ⬜ Pendente |
| 8 | Pesquisa binária | C | Pesquisa | ⬜ Pendente |
| 9 | Lista com alocação sequencial | Java | Estrutura de dados | ⬜ Pendente |
| 10 | Fila circular com alocação sequencial | C | Estrutura de dados | ⬜ Pendente |
| 11 | Lista com alocação flexível | C | Estrutura de dados | ⬜ Pendente |
| 12 | Pilha com alocação flexível | Java | Estrutura de dados | ⬜ Pendente |
| 13 | Lista dupla com alocação flexível | Java | Estrutura de dados | ⬜ Pendente |


---

## Descrição dos programas

### Modelagem (programas 1 e 2)

Representam o veículo e a data do mundo real em código e leem o arquivo CSV.

- **Java:** classes `Veiculo`, `Data`, `LeitorCsv` e `Modelagem` (classe principal). Cada classe tem um método `parse` (texto → objeto) e um `format` (objeto → texto).
- **C:** `struct Veiculo` e `struct Data`, com as funções `parseVeiculo`, `formatVeiculo`, `parseData`, `formatData` e `lerCsv`, seguindo o diagrama UML do enunciado. O texto formatado é escrito em um `buffer` fornecido por quem chama a função, e `lerCsv` devolve a quantidade de veículos lidos por um ponteiro (`int* n`).

### Ordenação (programas 3 a 7)

Algoritmos que organizam os veículos segundo um atributo, definido no enunciado de cada questão.

| Algoritmo | Ideia principal |
|-----------|-----------------|
| **Seleção** | A cada passo, seleciona o menor elemento restante e o coloca na posição correta. |
| **Inserção** | Percorre o vetor inserindo cada elemento na posição certa dentro da parte já ordenada. |
| **Counting Sort** | Conta quantas vezes cada valor ocorre e usa essas contagens para posicionar os elementos, sem fazer comparações entre eles. |
| **Radix Sort** | Ordena dígito por dígito (do menos ao mais significativo), usando uma ordenação estável em cada passo. |
| **Bucket Sort** | Distribui os elementos em "baldes" por faixa de valores, ordena cada balde e concatena o resultado. |

### Pesquisa (programa 8)

- **Pesquisa binária:** localiza um elemento em um vetor **já ordenado**, dividindo o intervalo de busca ao meio a cada passo.

### Estruturas de dados (programas 9 a 13)

| Estrutura | Ideia principal |
|-----------|-----------------|
| **Lista com alocação sequencial** | Elementos guardados em um vetor, em posições consecutivas. |
| **Fila circular com alocação sequencial** | Fila (o primeiro a entrar é o primeiro a sair) implementada em vetor, em que o fim "dá a volta" e reaproveita o início. |
| **Lista com alocação flexível** | Lista encadeada: cada célula guarda o dado e um ponteiro (referência) para a próxima. |
| **Pilha com alocação flexível** | Pilha (o último a entrar é o primeiro a sair) implementada com células encadeadas. |
| **Lista dupla com alocação flexível** | Lista encadeada em que cada célula aponta para a anterior e para a próxima. |

---


## Restrições do trabalho

O enunciado limita as funções e métodos que podem ser usados, então os programas evitam qualquer recurso fora da lista.

### Java

Da classe `String`, além dos métodos que convertem `String` para tipos primitivos (como `Integer.parseInt`, `Double.parseDouble` e `Boolean.parseBoolean`), podem ser usados apenas:

- `int compareTo(String str)`
- `boolean equals(String str)`
- `String[] split(String str)`
- `static String format(String str, Object... args)`

Por isso não são usados métodos como `trim`, `isEmpty` ou `String.join`.

### C

Além das funções básicas de leitura de arquivo, impressão e alocação de memória, podem ser usadas apenas:

- `int strcmp(char* str1, char* str2)` e `char* strtok(char* str, const char* delimiters)` (de `string.h`)
- `int sscanf(char* str, char* format, ...)` e `int sprintf(char* buffer, char* format, ...)` (de `stdio.h`)
- as funções que convertem string para tipos primitivos (como `atoi` e `atof`)

Por isso a cópia de texto é feita com `sprintf` (no lugar de `strcpy`), e não são usadas funções como `strlen`, `strcat` ou `strcpy`.

---

## Como compilar e executar

Os programas leem o arquivo `veiculos.csv`. Na versão de entrega, o caminho usado é `/tmp/veiculos.csv`; para testar localmente, existe no `main` uma linha comentada que lê `veiculos.csv` da pasta atual. Ajuste o caminho conforme onde for executar.

---

## Conceitos abordados

- Organização e tipagem de dados
- Modelagem de entidades do mundo real (classes em Java, `struct` em C)
- Leitura e conversão de arquivos CSV (`split` e `strtok`)
- Manipulação de vetores e registros
- Algoritmos de ordenação (por comparação e sem comparação)
- Pesquisa binária
- Estruturas de dados lineares: listas, filas e pilhas, com alocação sequencial e flexível
- Alocação dinâmica de memória em C (`malloc` e `free`)
- Consultas, filtragens e ordenações sobre um conjunto de dados
