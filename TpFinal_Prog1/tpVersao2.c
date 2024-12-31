//Thiago Martins Zanete 24.2.4005
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define ANSI_RESET            "\x1b[0m"  // desativa os efeitos anteriores
#define ANSI_BOLD             "\x1b[1m"  // coloca o texto em negrito
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"

// macros para facilitar o uso
#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define CYAN(string)       ANSI_COLOR_CYAN       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET
#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_YELLOW(string)  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string)    ANSI_BG_COLOR_CYAN    string ANSI_RESET


// caracteres uteis para tabelas
#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL  "\u250F" // ┏ (top-left)
#define TAB_ML  "\u2523" // ┣ (middle-left)
#define TAB_BL  "\u2517" // ┗ (bottom-left)
#define TAB_TJ  "\u2533" // ┳ (top-join)
#define TAB_MJ  "\u254B" // ╋ (middle-join)
#define TAB_BJ  "\u253B" // ┻ (bottom-join)
#define TAB_TR  "\u2513" // ┓ (top-right)
#define TAB_MR  "\u252B" // ┫ (middle-right)
#define TAB_BR  "\u251B" // ┛ (bottom-right)
 typedef struct{
		int linhaDo0;
		int colunaDo0;
		int linhaDoNum;
		int colunaDoNum;
		int NUM;
	}mover;
 void tabela(int, int**);
 char* validaopcMenu(int *check);
 int** criaMatriz(int);
 void embaralha(int**, int, int);
 int validadif();
 int validaN();
 char* maiusculo(char *);
 void preencheord(int **, int);
 void salvar(char *, int **, int, int, int);
 int validaOpcao();
 int** leArq(int*, int*);
 void validaNum(int** jogo,int n, mover *ondeMover);
 void moveNUM(mover *ondeMover, int** jogo);
 int JAganhou(int**, int n);

 
 
 int main(){
	int n, **jogo, dif, menudnv = 0, dnv = 0, jogadas = 0, primeiraVez = 0, ganhou;
	char *opc;
	int check = 0;
	srand(time(NULL));
	//menu e funçaõ q valida as opcoes
	
	mover ondeMover;
	
	//opc = validaopcMenu();
	do{
		ganhou = 1;
		opc = validaopcMenu(&check);
		//se opc for continuar um novo jogo
		if(*opc == 'N'){
			primeiraVez++;
			system("clear");
			printf(GREEN(BOLD("NOVO JOGO\n")));
			n = validaN();
			jogo = criaMatriz(n);
			preencheord(jogo, n);
			tabela(n, jogo);
			printf(GREEN(BOLD("Tabuleiro ordenado!\n")));
			dif = validadif();
			printf("%d\n", dif);
			if(dif == 2){
				menudnv++;
				continue;
			}
			system("clear");
			printf(GREEN(BOLD("\nTabuleiro embaralhado. Vamos começar o jogo!\n")));
			embaralha(jogo, n, dif);
			tabela(n, jogo);
			do{//aqui dentro depois de chamar a validaNUm preciso verificar se na sruct é voltar ou salvar
				validaNum(jogo, n, &ondeMover);
				getchar();
				if(ondeMover.NUM == -1 ){//é pra voltar
					menudnv++;
					system("clear");
					break;

				}else if(ondeMover.NUM == -2){//é pra salvar
					char nome[50];//verificar se otamnho do nome nao é maior que 50 e limpar o buffer
					scanf("%s", nome);
					int tam = strlen(nome);
					salvar(nome, jogo, tam, n, jogadas);//função que salva
					dnv++;//volta pro loop
				

				}else if(ondeMover.NUM == -3){//número não pode mexer
					printf(RED(BOLD("Não é possível mover a peça %d\n")), ondeMover.linhaDoNum);
					dnv++;
					continue;

				}else if(ondeMover.NUM == -4){//aqui o numero nao existe na matriz;
					printf(RED(BOLD("ESTE NÚMERO NÃO ESTÁ NO JOGO\n")));
					dnv++;
				}else if(ondeMover.NUM == -5){//aqui o cara digitou uma letra
					printf(RED(BOLD("VOCÊ NÃO PODE DIGITAR LETRAS AGORA\n")));
					dnv++;
					continue;

				}else{
					system("clear");
					jogadas ++;
					moveNUM(&ondeMover, jogo);
					tabela(n, jogo);
					printf(GREEN(BOLD("O número de jogadas até agora é %d\n")), jogadas);
					ganhou = JAganhou(jogo, n);//quando ganho ganhou é 0
					if(ganhou == 0){
						printf(CYAN(BOLD("Parabéns! Você completou o quebra-cabeças com %d movimentos.\n\n")), jogadas);
						menudnv++;
						break;
					}else{
						dnv++;
					}
				}
			}while(dnv != 0);
			
		//se opc for pra continuar o atual
		}else if(*opc == 'C'){
			primeiraVez++;
			system("clear");
			printf(GREEN(BOLD("CONTINUAR ATUAL \n")));
			ganhou = 1;
			tabela(n, jogo);
			printf(GREEN(BOLD("o número de jogadas até agora é %d\n")), jogadas);
			do{//aqui dentro depois de chamar a validaNUm preciso verificar se na sruct é voltar ou salvar
				validaNum(jogo, n, &ondeMover);
				getchar();
				if(ondeMover.NUM == -1 ){//é pra voltar
					menudnv++;
					system("clear");
					break;

				}else if(ondeMover.NUM == -2){//é pra salvar
					char nome[50];
					scanf("%s", nome);
					int tam = strlen(nome);
					salvar(nome, jogo, tam, n, jogadas);//função que salva
					dnv++;//volta pro loop
				

				}else if(ondeMover.NUM == -3){//número não pode mexer
					printf(RED(BOLD("Não é possível mover a peça %d\n")), ondeMover.linhaDoNum);
					dnv++;
					continue;

				}else if(ondeMover.NUM == -4){//aqui o numero nao existe na matriz;
					printf(RED(BOLD("ESTE NÚMERO NÃO ESTÁ NO JOGO\n")));

				}else if(ondeMover.NUM == -5){//aqui o cara digitou uma letra
					printf(RED(BOLD("VOCÊ NÃO PODE DIGITAR LETRAS AGORA\n")));
					dnv++;
					continue;

				}else{
					system("clear");
					jogadas ++;
					moveNUM(&ondeMover, jogo);
					tabela(n, jogo);
					printf(GREEN(BOLD("O número de jogadas até agora é %d\n")), jogadas);
					ganhou = JAganhou(jogo, n);
					if(ganhou == 0){
						printf(CYAN(BOLD("Parabéns! Você completou o quebra-cabeças com %d movimentos.\n\n")), jogadas);
						menudnv++;
						break;
					}else{
						dnv++;
					}
				}

			}while(dnv != 0);
		
		//se opc for para continuar o salvo	
		}else if(*opc == 'S'){
			system("clear");
			printf(GREEN(BOLD("CONTINUAR SALVO\n")));
			ganhou = 1;
			if(primeiraVez == 0){//a matriz do jogo ainda não foi criada eu crio ela com o tamanho maximo e dps libero ela
				printf("ok\n");
			}
			
			int *N = &n;
			int *JOG = &jogadas;

			jogo = leArq(N, JOG);
			
			if(jogo == NULL){//aí é pra voltar pro menu
				menudnv++;
				continue;
			}

			tabela(n, jogo);
			printf(GREEN(BOLD("o número de jogadas até agora é %d\n")), jogadas);
			do{//aqui dentro depois de chamar a validaNUm preciso verificar se na sruct é voltar ou salvar
					validaNum(jogo, n, &ondeMover);
					getchar();
					if(ondeMover.NUM == -1 ){//é pra voltar
						menudnv++;
						system("clear");
						break;

					}else if(ondeMover.NUM == -2){//é pra salvar
						char nome[50];
						scanf("%s", nome);
						int tam = strlen(nome);
						salvar(nome, jogo, tam, n, jogadas);//função que salva
						dnv++;//volta pro loop

					}else if(ondeMover.NUM == -3){//número não pode mexer
						printf(RED(BOLD("Não é possível mover a peça %d\n")), ondeMover.linhaDoNum);
						dnv++;
						continue;

					}else if(ondeMover.NUM == -4){//aqui o numero nao existe na matriz;
						printf(RED(BOLD("ESTE NÚMERO NÃO ESTÁ NO JOGO\n")));

					}else if(ondeMover.NUM == -5){//aqui o cara digitou uma letra
						printf(RED(BOLD("VOCÊ NÃO PODE DIGITAR LETRAS AGORA\n")));
						dnv++;
						continue;

					}else{
						system("clear");
						jogadas ++;
						moveNUM(&ondeMover, jogo);
						tabela(n, jogo);
						printf(GREEN(BOLD("O número de jogadas até agora é %d\n")), jogadas);
						ganhou = JAganhou(jogo, n);
						if(ganhou == 0){
						printf(CYAN(BOLD("Parabéns! Você completou o quebra-cabeças com %d movimentos.\n\n")), jogadas);
						menudnv++;
						break;
						}else{
							dnv++;
						}
					}


				}while(ganhou == 1 || dnv != 0);//vou colocar uma funçao que vẽ se o usuario já ganhou

		//se for ajuda
		}else if(*opc == 'A'){
			system("clear");
			printf(GREEN(BOLD("AJUDA\n")));
			printf(RED(BOLD("COMO JOGAR:\n")));
			printf(CYAN(BOLD("O jogo começa com as peças embaralhadas em um tabuleiro.\nSua missão é organizar os números em ordem crescente, deixando a última posição vazia.\n")));
			printf(RED(BOLD("MOVER\n")));
			printf(CYAN(BOLD("Você pode mover as peças adjacentes ao espaço vazio (cima, baixo, esquerda ou direita).\nPara mover uma peça, digite o número da peça que você deseja mover.\nO número será movido para o espaço vazio, e o tabuleiro será atualizado.\nO jogo não permite movimentar peças que não estejam ao lado do espaço vazio.\n")));
			printf(RED(BOLD("COMANDOS\n")));
			printf(CYAN(BOLD("Durante o jogo você pode SALVAR progresso, VOLTAR para o menu ou MOVER uma peça.\n")));
			printf(RED(BOLD("BOA SORTE! ORGANIZE TODAS AS PEÇAS E RESOLVA O QUEBRA-CABEÇAS\n")));
			menudnv++;
			
		//se for salvar
		}else if(*opc == 'R'){
			printf(GREEN(BOLD("SALVAR\n")));
			int tam = strlen(opc); 
			jogadas = 5;
			salvar(opc, jogo, tam, n, jogadas);
			menudnv++;//volta para o menu
		//se for sair
		}else if(*opc == 'X'){
			printf(RED(BOLD("Finalizando...\nOBRIGADO POR JOGAR\n")));
			return 0;
		}else{//caso alguma coisa dẽ errado
			printf(RED(BOLD("ALGUM ERRO!!!\nVamos voltar para o menu\n")));
			opc[0] = 'Z';
		}
	}while(menudnv != 0);
	
	//como estou sobrescrevendo jogo , só libero quando finalizo o programa
	for(int i = 0; i < n; i++){
		free(jogo[i]);
	}
	free(jogo);
	return 0;
 }



void moveNUM(mover *ondeMover, int** jogo){//so vou chamar dse der pra mover
	//na struct esta a posicao do 0 e a posiçao que o usuario quer mover, nessa parte já esta validada, logo, eu apenas troco
	jogo[ondeMover -> linhaDo0][ondeMover -> colunaDo0] = ondeMover -> NUM;
	jogo[ondeMover -> linhaDoNum][ondeMover -> colunaDoNum] = 0;
}
 

//verifica se o usuário já ganhou
int JAganhou(int**jogo, int n){
	int **mat;
	if(jogo[n - 1][n - 1] == 0){//so entra se o 0 esta na ultima posição
		mat = malloc(n * sizeof(int*));
		for(int i = 0; i < n; i++){
			mat[i] = malloc(n * sizeof(int));
		}
		
		int k = 1;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				mat[i][j] = k;
				k++;
			}
		}
		mat[n-1][n-1] = '\0';
		int diferente = 0;//se tiver algum difernete o contador é incremnetado
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(jogo[i][j] != mat[i][j]){
					diferente++;
				}
			}
		}
		for(int i = 0; i < n; i++){
			free(mat[i]);
		}
		free(mat);
		if(diferente == 0){
			return 0;//retorna 0 se já ganhou
		}else{
			return 1;//retorna 1 se nao ganhou ainda 
		}
	}else{
		return 1;
	}
}

 void validaNum(int** jogo,int n, mover *ondeMover){//essa função me retorna pra qual lado mexer
	char comando[50];
	int l0, c0, lNUM, cNUM;
	int letra = 0;
	int num, noJog = 0;//linha e coluna
	printf(CYAN(BOLD("Digite salvar, voltar, ou um número que deseja mover\n")));
	scanf("%s", comando);
	//vou ver se é salvar ou voltar
	if(strcmp(maiusculo(comando), "VOLTAR") == 0){
		ondeMover -> NUM = -1;//coloco -1 para voltar
		return;
	}else if(strcmp(maiusculo(comando), "SALVAR") == 0){
		//scanf("%s", comando);
		ondeMover -> NUM = -2;//coloco -2 para salvar
		return; 

	}else{
		for (int i = 0; i < strlen(comando); i++) {
			if (!isdigit(comando[i])) { // Verifica se não é dígito
				 letra++; // Não é um número
				break;
			}
		}
	}


	if(letra != 0){//é uma letra retorno -5 pra esse caso
		ondeMover -> NUM = -5;
		return;
	}else{
		num = atoi(comando);//converto pra número
	} 
	//a partir daqui é um número vou encontrar onde esta o 0 no jogo;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(jogo[i][j] == num){//aqui vejo se o número digitado está na matriz
				noJog = 1;
			}
			if(jogo[i][j] == 0){
				l0 = i;//linha e coluna do 0
				c0 = j;
			}
			if(jogo[i][j] == num){
				lNUM = i;//linha e coluna do numero digitado
				cNUM = j;

			}
		}
	}
	//1 direita 	2 esquerda 	 	3 cima      4 baixo
	if(noJog != 1){//o número não está na matriz
		ondeMover -> NUM= -4;//se o numero não existe coloco -4
		return;
	}
	if(lNUM == l0 && cNUM == c0 + 1){//direita
		ondeMover -> linhaDo0 = l0;//linha e coluna do 0
		ondeMover -> colunaDo0 = c0;
		ondeMover -> linhaDoNum = lNUM;//linha e colna do número digitado pelo usuario
		ondeMover -> colunaDoNum = cNUM;

	}else if(lNUM == l0 && cNUM == c0 - 1){//esquerda
		ondeMover -> linhaDo0 = l0;//linha e coluna do 0
		ondeMover -> colunaDo0 = c0;
		ondeMover -> linhaDoNum = lNUM;//linha e colna do número digitado pelo usuario
		ondeMover -> colunaDoNum = cNUM;

	}else if(lNUM == l0 + 1 && cNUM == c0){//pra baixo
		ondeMover -> linhaDo0 = l0;//linha e coluna do 0
		ondeMover -> colunaDo0 = c0;
		ondeMover -> linhaDoNum = lNUM;//linha e colna do número digitado pelo usuario
		ondeMover -> colunaDoNum = cNUM;

	}else if(lNUM == l0 - 1 && cNUM == c0){//pra cima
		ondeMover -> linhaDo0 = l0;//linha e coluna do 0
		ondeMover -> colunaDo0 = c0;
		ondeMover -> linhaDoNum = lNUM;//linha e colna do número digitado pelo usuario
		ondeMover -> colunaDoNum = cNUM;

	}else{//não dá pra mover
		ondeMover -> NUM = -3;//coloco -3 para numero que nao move
		ondeMover -> linhaDoNum = num;
		return;
	}
	ondeMover -> NUM = num;//o num que vai mover vai pra struct isso facilita dps


 }


//função responsável por printar a tabela na tela (basicamente aqui é por teste e erro ate a formatação ficar certa)
void tabela(int n, int **mat){
	//parte de cima
	printf(GREEN(TAB_TL));//printa a quina direita
	for(int i = 0; i < n - 1; i++){
			printf(GREEN(TAB_HOR) GREEN(TAB_HOR) GREEN(TAB_HOR) GREEN(TAB_TJ));//as horizontais e divisões da parte de cima
		if(i == n - 2){//se i = n-2 é o fim das linhas, logo printa a quina superior direita
			printf(GREEN(TAB_HOR) GREEN(TAB_HOR) GREEN(TAB_HOR) GREEN(TAB_TR) "\n");
		}
	}

	
	//meios
	for(int i = 1; i < n; i++){
		int k = 0;
		for(int j = 0; j < n; j++){
			if(mat[i-1][j] == 0){
					printf(GREEN(TAB_VER) "   ");
					k++;
			}else{
				printf(GREEN(TAB_VER));//printa os números da matriz
				printf(CYAN(BOLD("%*d")), 3, mat[i-1][j]);
				k++;//incrementa k
			}
			if(k == n){//se k = n é a o útimo número da linha foi printado, jogo, finaliza com uma tabela vertical
				printf(GREEN(TAB_VER));
			}
		}
	
		printf("\n");//salta uma linha
		printf(GREEN(TAB_ML));//printa a as divisões entra uma linha e outra 
		for(int j = 1; j < n; j++){
			printf(GREEN(TAB_HOR) GREEN(TAB_HOR) GREEN(TAB_HOR) GREEN(TAB_MJ));
		}
		printf(GREEN(TAB_HOR) GREEN(TAB_HOR) GREEN(TAB_HOR) GREEN(TAB_MR));
		printf("\n");
		//depois daqui volta no for mais externo e continua com os números
	}

	//parte de baixo
	printf(GREEN(TAB_VER));//printa a 1 tabela vertical
	for(int i = 0; i < n; i++){
		if(mat[n - 1][i] == 0){
			printf("   ");
		}else{
			printf(CYAN(BOLD("%*d")), 3, mat[n-1][i]);//printa o número seguido de outra tabela vertical	
		}
		printf(GREEN(TAB_VER));
	}
	printf("\n");//quando acaba os números salta uma linha 
	printf(GREEN(TAB_BL));//printa a quina esquerda
	for(int i = 0; i < n - 1; i++){
		printf(GREEN(TAB_HOR) GREEN(TAB_HOR) GREEN(TAB_HOR) GREEN(TAB_BJ));//as horizontais e as divisões da parte de baixo
		if(i == n - 2){//se i for = a n - 2 é a última sequencia de horizontais e a quina direira inferior
			printf(GREEN(TAB_HOR) GREEN(TAB_HOR) GREEN(TAB_HOR) GREEN(TAB_BR) "\n");
		}
	}
}


//função que valida o .txt no nome do arquivo e salva ele
void salvar(char *nome, int **jogo, int tam, int n, int jogadas){
	if (tam >= 5 && strcmp(&nome[tam-4], ".txt") != 0) {
		strcat(nome, ".txt");
	}
	FILE *A = fopen(nome, "w");
	if (A == NULL) {
		printf(RED(BOLD("Erro ao abrir o arquivo\n")));
		return;
	}
	fprintf(A, "%d\n", n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fprintf(A, "%d ", jogo[i][j]);
		}
		fprintf(A, "\n");
	}
	fprintf(A, "%d", jogadas);
	fclose(A);
	printf(YELLOW(BOLD("Arquivo %s salvo com sucesso!\n\n")), nome);
}




// função que printa o menu e  valida a opção do usuário 
char* validaopcMenu(int *check){
	char *opc;
	opc = malloc(10 * sizeof(char));
	int dnv = 0;
	printf(CYAN(TAB_TL));
	//parte de cima do menu
	for(int i = 0; i < 35; i++){
		printf(CYAN(TAB_HOR));
	}
	printf(CYAN(TAB_TR) "\n");
	
	printf(CYAN(TAB_VER));
	printf(GREEN(BOLD("    Bem vindo ao Quebra Cabeças    ")));
	printf(CYAN(TAB_VER) "\n");

	printf(CYAN(TAB_BL));
	for(int i = 0; i < 35; i++){
		printf(CYAN(TAB_HOR));
	}
	printf(CYAN(TAB_BR) "\n");

	do{
		//printa as opcoes
		printf(CYAN(TAB_TL));
		for(int i = 0; i < 35; i++){
			printf(CYAN(TAB_HOR));
		}
		printf(CYAN(TAB_TR) "\n");

		printf(CYAN(TAB_VER));
		printf(RED(BOLD("X. Sair do Jogo                    ")));
		printf(CYAN(TAB_VER) "\n");

		printf(CYAN(TAB_VER));
		printf(GREEN(BOLD("N. Iniciar um novo jogo            ")));
		printf(CYAN(TAB_VER) "\n");

		printf(CYAN(TAB_VER));
		printf(GREEN(BOLD("C. Continuar o jogo atual          ")));
		printf(CYAN(TAB_VER) "\n");


		printf(CYAN(TAB_VER));
		printf(GREEN(BOLD("S. Continuar um jogo salvo         ")));
		printf(CYAN(TAB_VER) "\n");

		printf(CYAN(TAB_VER));
		printf(GREEN(BOLD("A. Ajuda com as instruçoes do jogo ")));
		printf(CYAN(TAB_VER) "\n");

		//fecha a tabela do menu
		printf(CYAN(TAB_BL));
		for(int i = 0; i < 35; i++){
			printf(CYAN(TAB_HOR));
		}
		printf(CYAN(TAB_BR) "\n");

		
		scanf("%s", opc);
		opc = maiusculo(opc);
		if(strcmp(maiusculo(opc), "VOLTAR") == 0){
			system("clear");
			printf(RED(BOLD(" NÃO É POSSÍVEL VOLTAR AGORA!\n SE DESEJA FINALIZAR APERTE 'X'\n")));
		}else if(strcmp(maiusculo(opc), "SALVAR") == 0){
			system("clear");
			printf(RED(BOLD(" NÃO É POSSÍVEL SALVAR AGORA")) "\n");
		}else if(strcmp(opc, "X") == 0){//aqui ele quer sair se nem comecou ainda
			return opc;
		}else if(strcmp(opc, "N") == 0){//novo jog0
			*check = 1;
			return opc;
		}else if(strcmp(opc, "C") == 0){//continuar um jogo 
			if(*check == 1){
				return opc;
			}else{
				printf(RED(BOLD(" NÃO É POSSÍVEL CONTINUAR O JOGO (VOCÊ DEVE INICIAR UM JOGO PRIMEIRO")) "\n");
				printf("não pode carregar jogo agr\n");
			}
			
		}else if(strcmp(opc, "S") == 0){
			*check = 1;
			return opc;
		}else if(strcmp(opc, "A") == 0){
			return opc;
		}else{
			system("clear");
			printf(RED(BOLD(" %s NÃO É UMA OPÇÃO VÁLIDA, DIGITE NOVAMENTE")) "\n", opc);
		}

	}while(dnv == 0);
	return opc;
}


//valida o tamanho do tabuleiro
int validaN(){
	int dnv = 0;
	int num;
	char n[20];
	do{
		printf(CYAN(BOLD("Digite o valor de n: ")));
		scanf("%s", n);
		getchar();
		//ate aqui n é uma string
		num = atoi(n);//a partir daqui é um inteiro
		if(num < 3 || num > 10){
			printf(CYAN(BOLD("Digite um valor válido para n (entre 3 e 10)\n")));
			dnv++;
		}else {
			return num;
		}
	}while(dnv != 0);
	return 0;
}


//valida a dificuldade
int validadif(){
	char dif[10];
	char DIF[10];//recebe dif maiúculo 
	int dificuldade = 0, dnv = 0;
	do{
		printf(CYAN(BOLD("Digite o nível de dificuldade para embaralhar, ")));
		printf(GREEN(BOLD("fácil (F), ")));
		printf(YELLOW(BOLD("médio (M), ")));
		printf(CYAN(BOLD("ou ")));
		printf(RED(BOLD("difícil (D): ")));
		scanf("%s", dif);
		getchar();
		strcpy(DIF, maiusculo(dif));//linha corrigida
		//vou ver se é salvar ou voltar
		if(strcmp(dif, "VOLTAR") == 0){//strcmp retorna 0 caso seja igual
			return 2;//retorno 2 para voltar
		
		}else if(strcmp (dif, "SALVAR") == 0){
			printf(RED(BOLD("VOCÊ NÃO PODE SALVAR O JOGO AGORA. DIGITE UMA OPÇÃO VÁLIDA\n")));
			dnv++;
		}else if(strcmp(dif, "F") == 0){//se veio aqui é uma opcão de dificuldade
			dificuldade = 5;
			return dificuldade;
		}else if(strcmp(dif, "M") == 0){
			dificuldade = 10;
			return dificuldade;
		}else if(strcmp(dif, "D") == 0){
			dificuldade = 15;
			return dificuldade;
		}else{
			printf(RED(BOLD("DIGITE UM COMANDO VÁLIDO")));
			dnv++;
			continue;
		}
	
	}while(dnv != 0);
	return dificuldade;
}


int** leArq(int *n, int *jogadas){
	int **jogo, dnv = 0;
	char nome[50], nomeCopia[50];

	do{
		printf(RED(BOLD("Digite o nome do arquivo: ")));
		scanf("%s", nome);
		strcpy(nomeCopia, nome);
		if(strlen(nome) >= 50){
			printf(CYAN(BOLD("Digite um nome menor para o arquivo\n")));
			dnv++;
			continue;
		}
		if(strcmp(maiusculo(nomeCopia), "VOLTAR") == 0){
			return NULL;
		}else if(strcmp(maiusculo(nomeCopia), "SALVAR") == 0){
			printf(CYAN(BOLD("Voce não pode salvar um arquivo agr\n")));
			dnv++;
			continue;
		}else{
			FILE *A;
			A = fopen(nome, "r");
			if(A == NULL){
				printf(CYAN(BOLD("Não foi possível abrir o arquivo\nTente Novamente\n")));
				dnv++;
			}else{//le o q tá no arquivo
				fscanf(A, "%d", n);//valor de n
				jogo = malloc(*n * sizeof(int*));//memoria para as colunas
				for(int i = 0; i < *n; i++){
					jogo[i] = malloc(*n * sizeof(int));//memória para cada linha
					if(jogo[i] == NULL){
						printf(RED(BOLD("Erro ao alocar a memória\n")));
						for(int k = 0; k < i; k++){
							free(jogo[k]);
						}
						free(jogo);
						fclose(A);
						return NULL;
					}
				}
				for(int i = 0; i < *n; i++){//elementos da matriz
					for(int j = 0; j < *n; j++){
						fscanf(A, "%d", &jogo[i][j]);
					}
				}
				fscanf(A, "%d", jogadas);
				fclose(A);
				return jogo;
				}
		}
	}while(dnv != 0);
	
	return NULL;
}


//essa função recebe uma string com a opção e e vẽ oq é pra fzr (salvar voltar ou mover)
int validaOpcao(){//retorna 1 se for um número, retorna 2 se for voltar, retorna 3 se for salvar
	char opc[70];
	char nome[50];
	printf(GREEN(BOLD("Digite um comando ou número da peça que quer mover: ")));
	getchar();
	scanf("%s", opc);
	int tamOpc = strlen(opc);
	int numero = 1; // Assume que é um número
	
	for (int i = 0; i < tamOpc; i++) {
		if (!isdigit(opc[i])) { // Verifica se não é dígito
			numero = 0; // Não é um número
			break;
		}
	}
	
	if(numero == 1){//se entro aqui sabemos q é um número agr tem q ver se ele pode mexer, ou se está na matriz
		return 1;//vou retornar 1 e fazer outra função que converte para número e valida ele;
	}else if(strcmp(maiusculo(opc), "VOLTAR") == 0){
		return 2;//retorno 2 para voltar
	}else if(strcmp(maiusculo(opc), "SALVAR") == 0){
		while(strlen(opc) >= 50){
			printf(RED(BOLD("Digite um nome de arquivo menor que 50 caracteres")));
			scanf("%s", nome);
		}	
		strcpy(opc, nome);//
		
		return 3;//retorno 3 para slvar, no entanto já mudei o validei o tamanho do nome do arquivo e se preciso alterei ele(pois é um ponteiro, logo nao preciso retornar ele)
	}else{
		return 4;//isso aqui é só pra controle
	}
	return 5; //isso aqui tbm é só controle
}

//converte uma string para maiúsculo
char* maiusculo(char *str) {
	int i = 0;
	while (str[i]) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] = str[i] - 32;  // Converte minúsculas para maiúsculas com base na tabela ascii
		}
		i++;
	}
	return str;
}

//função que cria a matriz conforme o tamanho escolhido pelo usuário
int** criaMatriz(int n){
	int **mat = malloc(n * sizeof(int*));
		if(mat == NULL){//verifica aqui para maior eficiencia
			return NULL;
		}
	for(int i = 0; i < n; i++){
		mat[i] = malloc(n * sizeof(int*));
		if(mat[i] == NULL){//tbm verifica se foi possível criar, se não retorna NULL e limpa a memória
			for(int j = 0; j < i; j++){
				free (mat[j]);
			}
			free (mat);
			return NULL;
		}
	}
	return mat;//caso tenha criado retorna a matriz
 }

//prrenche a matriz de forma ordenada pela primeira vez
void preencheord(int **mat, int n){
	int k = 1;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			mat[i][j] = k;
			k ++;
		if(i == n - 1 && j == n - 1)
			mat[i][j] = 0;
		}
	}
	//return mat;
}

//funçaõ que embaralha 
void embaralha(int **mat, int n, int dif){
	
	//1 pra direira   2 para esquerda    3 para cima   4 pra baixo
	typedef struct{
		int x;
		int y;
	}Posicao;
	int mover = 0, lado, ultimo = 1;
	Posicao posicao;
	posicao.x = n - 1;
	posicao.y = n - 1;
	while(mover < (n * dif)){
		do{
			lado = (rand() % 4) + 1;
		}while((lado == 1 && ultimo == 2) || (lado == 2 && ultimo == 1) || (lado == 3 && ultimo == 4) || (lado == 4 && ultimo == 3));
		// Verifica o lado e tenta mover o 0 de acordo com a posição atual
		switch(lado){
			case 1: // direita
				if(posicao.y + 1 < n){
					int aux = mat[posicao.x][posicao.y + 1];
					mat[posicao.x][posicao.y + 1] = 0;
					mat[posicao.x][posicao.y] = aux;
					posicao.y++;
					mover++;
					ultimo = 1;
					//imprime(mat, n);
				}
				break;
			case 2: // esquerda
				if(posicao.y - 1 >= 0){
					int aux = mat[posicao.x][posicao.y - 1];
					mat[posicao.x][posicao.y - 1] = 0;
					mat[posicao.x][posicao.y] = aux;
					posicao.y--;
					mover++;
					ultimo = 2;
					//imprime(mat, n);
				}
				break;
			case 3: // para cima
				if(posicao.x - 1 >= 0){
					int aux = mat[posicao.x - 1][posicao.y];
					mat[posicao.x - 1][posicao.y] = 0;
					mat[posicao.x][posicao.y] = aux;
					posicao.x--;
					mover++;
					ultimo = 3;
					//imprime(mat, n);
				}
				break;
			case 4: // para baixo
				if(posicao.x + 1 < n){
					int aux = mat[posicao.x + 1][posicao.y];
					mat[posicao.x + 1][posicao.y] = 0;
					mat[posicao.x][posicao.y] = aux;
					posicao.x++;
					mover++;
					ultimo = 4;
					//imprime(mat, n);
				}
				break;
			default:
				//se o lado for inválido nao faz nada
				break;
		}
	}
}

