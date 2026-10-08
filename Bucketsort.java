import java.util.Scanner;
import java.io.File;
import java.util.Locale; // utilizar ponto decimal

// Classe que representa um veículo: guarda os dados de uma linha do CSV
class Veiculo{

	// "public" = qualquer classe pode acessar diretamente
	public int id;
	public String marca;
	public String modelo;
	public int ano;
	public String categoria;
	public String[] combustivel;
	public int cilindros;
	public double cilindrada;
	public String transmissao;
	public String tracao;
	public double consumoCidade;
	public double consumoEstrada;
	public double co2;
	public boolean turbo;
	public Data dataRegistro;

	// Construtor: método chamado ao criar um objeto com "new Veiculo( )"
	public Veiculo(int id, String marca, String modelo, int ano, String categoria, String[] combustivel, int cilindros, double cilindrada,
	               String transmissao, String tracao, double consumoCidade, double consumoEstrada, double co2, boolean turbo, Data dataRegistro){
		
		// this.X: atributo do objeto; X: parâmetro recebido
		this.id = id;
		this.marca = marca;
		this.modelo = modelo;
		this.ano = ano;
		this.categoria = categoria;
		this.combustivel = combustivel;
		this.cilindros = cilindros;
		this.cilindrada = cilindrada;
		this.transmissao = transmissao;
		this.tracao = tracao;
		this.consumoCidade = consumoCidade;
		this.consumoEstrada = consumoEstrada;
		this.co2 = co2;
		this.turbo = turbo;
		this.dataRegistro = dataRegistro;
	}

		// "static" = o método pertence à classe, não a um objeto
	// Transforma uma linha de texto do CSV em um objeto Veiculo
	public static Veiculo parseVeiculo(String s) {
    String[] atributos = s.split(","); // split(","): corta o texto em cada vírgula

    int id = Integer.parseInt(atributos[0]);
    String marca = atributos[1];
    String modelo = atributos[2];
    int ano = Integer.parseInt(atributos[3]);
    String categoria = atributos[4];
    String[] combustivel = atributos[5].split(";");
    int cilindros = Integer.parseInt(atributos[6]);
    double cilindrada = Double.parseDouble(atributos[7]);
    String transmissao = atributos[8];
    String tracao = atributos[9];
    double consumoCidade = Double.parseDouble(atributos[10]);
    double consumoEstrada = Double.parseDouble(atributos[11]);
    double co2 = Double.parseDouble(atributos[12]);
    boolean turbo = Boolean.parseBoolean(atributos[13]);
    Data dataRegistro = Data.parseData(atributos[14]);

	// Cria o objeto com todos os valores lidos e o devolve
    return new Veiculo(id, marca, modelo, ano, categoria, combustivel, cilindros, cilindrada,
                       transmissao, tracao, consumoCidade, consumoEstrada, co2, turbo, dataRegistro);
	}

		// "private" = só pode ser usado dentro da própria classe Veiculo
	// Junta os combustíveis em um único texto, separados por ";"
	private String formatCombustivel(){
    String resultado = "[";
    for(int i = 0; i < combustivel.length; i++)
	{
        resultado += combustivel[i];
        if(i < combustivel.length - 1)
		{
            resultado += ",";
        }
    }
    resultado += "]";
    return resultado;
	}

	// Devolve o veículo em forma de texto
	public String format(){
    	return "[" + id + " ## " + marca + " ## " + modelo + " ## " + ano + " ## " + categoria
           + " ## " + formatCombustivel() + " ## " + cilindros + " ## " + cilindrada
           + " ## " + transmissao + " ## " + tracao
           + " ## " + String.format(Locale.US, "%.2f", consumoCidade)
           + " ## " + String.format(Locale.US, "%.2f", consumoEstrada)
           + " ## " + co2 + " ## " + turbo
           + " ## " + dataRegistro.format() + "]";
	}
}

// Classe que representa uma data
class Data{
	public int ano;
	public int mes;
	public int dia;

	// Construtor: cria uma Data a partir de ano, mês e dia
	public Data(int ano, int mes, int dia){
		this.ano = ano;
		this.mes = mes;
		this.dia = dia;
	}

	// Transforma um texto no formato "ano-mês-dia"
	public static Data parseData(String s){
		String[] atributos = s.split("-");
		int ano = Integer.parseInt(atributos[0]);
		int mes =Integer.parseInt(atributos[1]);
		int dia =Integer.parseInt(atributos[2]);
		return new Data(ano, mes, dia);
	}

	// Devolve a data como texto no formato "dia / mês / ano"
	public String format(){
    	return String.format("%02d/%02d/%04d", dia, mes, ano);
	}
}

// Classe responsável por ler o arquivo CSV e transformar cada linha em um Veiculo
class LeitorCsv{
	public static Veiculo[] ler(String caminhoArquivo) throws Exception {
		File f = new File(caminhoArquivo);
		Scanner sc = new Scanner(f); // abre o arquivo para leitura
		String cabecalho = sc.nextLine();
		Veiculo[] veiculos = new Veiculo[500];	
		int cont = 0;
		while(sc.hasNextLine()){
			String linha = sc.nextLine();
			if(linha.equals("")) continue;
			veiculos[cont] = Veiculo.parseVeiculo(linha);
			cont++;
		}

		sc.close(); // fecha o arquivo
		
		// Criar um vetor do tamanho exato
		Veiculo[] resultado = new Veiculo[cont];
		for(int i = 0; i < cont; i++) // copiar somente os veículos lidos
		{
			resultado[i] = veiculos[i];
		}
		return resultado; // devolve o vetor sem posições vazias
	}
}

// Classe responsável por ordenar o vetor de veículos
class Ordenador{

	// Ordena por marca, usando inserção (exercício 4)
	public static void insercao(Veiculo[] veiculos){
		for(int i = 1; i < veiculos.length; i++){
			Veiculo atual = veiculos[i];
			int j = i - 1;
			while(j >= 0 && veiculos[j].marca.compareTo(atual.marca) > 0){
				veiculos[j + 1] = veiculos[j];
				j--;
			}
			veiculos[j + 1] = atual;
		}
	}

	// Ordena um balde (vetor menor) por cilindrada, usando inserção
	public static void insercaoPorCilindrada(Veiculo[] balde){
		for(int i = 1; i < balde.length; i++){
			Veiculo atual = balde[i];
			int j = i - 1;
			while(j >= 0 && balde[j].cilindrada > atual.cilindrada){
				balde[j + 1] = balde[j];
				j--;
			}
			balde[j + 1] = atual;
		}
	}

	// Descobre em qual balde um veículo cai, a partir da cilindrada
	private static int indiceDoBalde(double cilindrada, double normalizador, int numBaldes){
		int indice = (int)((cilindrada / normalizador) * numBaldes);
		// Prende no último balde caso o valor normalizado chegue a 1.0 (cilindrada == normalizador)
		if(indice >= numBaldes){
			indice = numBaldes - 1;
		}
		return indice;
	}

	// Ordena o vetor de veiculos por cilindrada, usando Bucketsort (sem ArrayList)
	public static void bucketSort(Veiculo[] veiculos){
		int numBaldes = 10;
		double normalizador = 8.1;

		// 1ª passada: conta quantos veículos caem em cada balde
		int[] contagem = new int[numBaldes];
		for(int i = 0; i < veiculos.length; i++){
			int indice = indiceDoBalde(veiculos[i].cilindrada, normalizador, numBaldes);
			contagem[indice]++;
		}

		// Aloca cada balde já com o tamanho exato
		Veiculo[][] baldes = new Veiculo[numBaldes][];
		for(int i = 0; i < numBaldes; i++){
			baldes[i] = new Veiculo[contagem[i]];
		}

		// 2ª passada: distribui os veículos nos baldes
		int[] posicaoAtual = new int[numBaldes]; // controla a próxima posição livre em cada balde
		for(int i = 0; i < veiculos.length; i++){
			int indice = indiceDoBalde(veiculos[i].cilindrada, normalizador, numBaldes);
			int pos = posicaoAtual[indice];
			baldes[indice][pos] = veiculos[i];
			posicaoAtual[indice]++;
		}

		// Ordena cada balde individualmente, por inserção
		for(int i = 0; i < numBaldes; i++){
			insercaoPorCilindrada(baldes[i]);
		}

		// Junta os baldes de volta no vetor original, em ordem
		int pos = 0;
		for(int i = 0; i < numBaldes; i++){
			for(int j = 0; j < baldes[i].length; j++){
				veiculos[pos] = baldes[i][j];
				pos++;
			}
		}
	}
}

// Classe principal
class Bucketsort{

	public static void main(String[] args) throws Exception {
		Veiculo[] veiculos = LeitorCsv.ler("/tmp/veiculos.csv"); // VERDE
		// Veiculo[] veiculos = LeitorCsv.ler("veiculos.csv");
		Scanner sc = new Scanner(System.in);

		Veiculo[] selecionados = new Veiculo[veiculos.length];
		int cont = 0;

		while(sc.hasNextLine())
		{
			String entrada = sc.nextLine();
			if(entrada.equals("")) continue;

			int id = Integer.parseInt(entrada);
			if(id == -1) break;

			for(int i = 0; i < veiculos.length; i++)
			{
				if(veiculos[i].id == id)
				{
					selecionados[cont] = veiculos[i];
					cont++;
					break;
				}
			}
		}
		sc.close();

		Veiculo[] resultado = new Veiculo[cont];
		for(int i = 0; i < cont; i++){
			resultado[i] = selecionados[i];
		}

		// Ordena por cilindrada com Bucketsort
		Ordenador.bucketSort(resultado);

		for(int i = 0; i < resultado.length; i++){
			System.out.println(resultado[i].format());
		}
	}
}