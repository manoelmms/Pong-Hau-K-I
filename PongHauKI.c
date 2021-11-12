#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHA 7
#define COLUNA 7
#define JOGADOR_1 0
#define JOGADOR_2 1
#define tabuleiro {{'P','-','-','-','-','-','B'},{'|','\\',' ', ' ', ' ', '/',' '},{'|',' ','\\',' ','/',' ',' '},{'|',' ',' ','O',' ',' ',' '},{'|',' ','/',' ','\\',' ',' '},{'|','/',' ',' ',' ','\\',' '},{'p','-','-','-','-','-','b'}}

typedef struct _PONTO {
    int x, y;
} PONTO;

void limpa_tela(){
    /*Limpa a tela, opcional*/
    #ifdef _WIN32
        system("cls");    
    #else
        system("clear");
    #endif
}


void printa_matriz(char matriz[LINHA][COLUNA]){
    /*codigo que imprime uma matriz, eh usado pra imprimir o tabuleiro*/
    int i,j;
    for (i=0; i<LINHA; i++){
        for (j=0; j<COLUNA; j++){
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}


PONTO procura(char matriz[LINHA][COLUNA], char peca){
    /*Procura por uma peca no tabuleiro, atribui as coordenadas da peca a uma struc PONTO*/
    int i, j;
    PONTO posicao;
    for (i=0; i<LINHA; i++){
        for (j=0; j<COLUNA; j++){
            if (peca == matriz[i][j]){
                posicao.x = i;
                posicao.y = j;
            }
        }
    }
    return posicao;
}


int peca_valida (char peca, int jogador){
    /*So temos 4 pecas validas, 2 por jogador, so testando se o jogador e as pecas sao compativeis*/
    if ((jogador == JOGADOR_1) && ((peca == 'P') || (peca =='p'))) return 0;
    else if((jogador == JOGADOR_2) && ((peca == 'B') || (peca =='b'))) return 0;
    return 1;
}


void movimenta (char matriz[LINHA][COLUNA], char peca){
    PONTO posicao_peca;
    PONTO posicao_vazio;

    /*Descobre e assinala as variaveis da linha e coluna da peca jogada */
    posicao_peca = procura(matriz, peca);

    /*Descobre e assinala as variaveis da linha e coluna do espaco vazio */
    posicao_vazio = procura(matriz, 'O');

    /*Troca as posicoes*/
    matriz[posicao_vazio.x][posicao_vazio.y] = peca;
    matriz[posicao_peca.x][posicao_peca.y] = 'O';
}


int verifica_movimentos(char matriz[LINHA][COLUNA], char peca){
    PONTO posicao_peca;
    PONTO posicao_vazio;

    posicao_peca = procura(matriz, peca);
    posicao_vazio = procura(matriz, 'O');

    if(posicao_peca.x == 0 && posicao_peca.y == 0){
        /*O lugar vazio esta no outro lado do tabuleiro, logo o o movimento eh invalido*/
        if(posicao_vazio.x == 6 && posicao_vazio.y == 6) return 1;
    }
    else if(posicao_peca.x == 6 && posicao_peca.y == 0){
        /*O lugar vazio esta no outro lado do tabuleiro, logo o o movimento eh invalido*/
        if(posicao_vazio.x == 0 && posicao_vazio.y == 6) return 1;
    }
    else if(posicao_peca.x == 0 && posicao_peca.y == 6){
        /*Esta na parte superior direita do tabuleiro, logo, pelo formato do tabuleiro, nao consegue ir pra parte
        de baixo sem passar pelo centro primeiro*/
        if(posicao_vazio.x == 6) return 1;
    }
    else if(posicao_peca.x == 6 && posicao_peca.y == 6){
        /*Esta na parte inferior direita do tabuleiro, logo, pelo formato do tabuleiro, nao consegue ir pra parte
        de cima sem passar pelo centro primeiro*/
        if(posicao_vazio.x == 0) return 1;
    }
    return 0;
}


int aleatorio(){
    /*Escolhe um numero aleatorio depois tira o modulo 2 dele para que ele fique sendo somente 0 ou 1*/
    int n;
    srand (time (NULL));
    n = rand();
    if(n % 2) return 0;
    return 1;
}


void imprime_menu(){
    /*Menu do jogo*/ 
    limpa_tela();
    printf("\n     ****** PONG HAU K'I  ******\n\n"
                "\t** MENU DO JOGO **\n"
                "1.Iniciar o Jogo\n"
                "2.Creditos\n"
                "3.Regras\n"
                "Insira qualquer outra tecla para Sair\n");
}


void creditos(){
    /*Integrante e credito*/
    printf("\n\t Creditos:\n\n"
            "   Pedro Henrique Costa de Gois, DRE: 121096287\n\n"
            "   Manoel Marcelo da Silva, DRE: 121088349\n\n"
            "   Lucas de Lyra Monteiro, DRE: 121039714\n\n"
            " Programa criado na Data: 13/10/2021 as 19:00\n");
    printf("\nInsira qualquer tecla para sair\n ");
    while (getchar() != '\n');
}


int verifica_fim(char matriz[LINHA][COLUNA]){
    /*Verifica se o jogador com as pecas P,p ganhou*/
    if ((verifica_movimentos(matriz, 'B') && verifica_movimentos(matriz, 'b')) == 1) return 1;
    /*Verifica se o jogador com as pecas B,b ganhou*/
    else if ((verifica_movimentos(matriz, 'P') && verifica_movimentos(matriz, 'p')) == 1) return -1;
    return 0;
}


void reseta_tabuleiro(char matriz[LINHA][COLUNA]){
    /*Reinicia o tabuleiro para poder recomecar o jogo*/
    int i,j;
    char matriz_copia[LINHA][COLUNA] = tabuleiro;
    for (i=0; i<LINHA; i++){
        for (j=0; j<COLUNA; j++){
            matriz[i][j] = matriz_copia[i][j];
        }
    }
}


void regras(){
    /*Regras do jogo*/
    printf("\n");
    printf("O tabuleiro do jogo consiste em 5 vertices e 7 arestas  ligando cada vertice\n");
    printf("Cada jogador tem duas pecas\n");
    printf("A cada turno o jogador deve mover uma de suas pecas para uma casa adjacente vaga\n");
    printf("Caso o jogador nao tenha movimentos validos, este perde\n");
    printf("\nInsira qualquer tecla para sair\n ");
    while (getchar() != '\n');
}


void game_loop(char matriz[LINHA][COLUNA]){
    /*Faz o jogo funcionar*/
    int comeca, quem_venceu, pontuacao_jogador_1 = 0, pontuacao_jogador_2 = 0, vitoria = 0;
    char move, continua;


    do{
        /*Limpa a tela, opcional*/       
        limpa_tela();
        vitoria = 0; /*Ninguem ganhou*/

        comeca = aleatorio(); /*Decide aleatorio para decidir quem comeca o jogo*/
        if(comeca == 0){
            printf("O jogador 1 comeca o jogo com as pecas P e p!\n"
                   "O jogador 2 tem as pecas B e b\n");
        }
        else{
            printf("O jogador 2 comeca o jogo com as pecas B e b!\n"
                   "O jogador 1 tem as pecas P e p\n");
        }

        printf("\nAperte qualquer coisa para comecar! ");
        while (getchar() != '\n');

        while(vitoria == 0){
            /*Limpa a tela, opcional*/
            limpa_tela();

            printf("\n");
            printa_matriz(matriz);/*Imprime o tabuleiro*/
            printf("\nA vez eh do jogador %d, insira a letra da peca que deseja mover para o espaco vazio: ", (comeca % 2 + 1));
            /*Mostra para os jogadores quem comeca*/

            setbuf(stdin, NULL);/*limpa o buffer*/
            move = getchar();
            do {} while (getchar() != '\n');

            while ((verifica_movimentos(matriz, move) || peca_valida(move, (comeca%2) )) == 1){
                /*Verifica se o movimento eh valido de acordo com o jogador*/
                if (peca_valida(move, (comeca%2)) == 1){
                    printf("Peca invalida!\n");
                }
                else{
                    printf("Movimento invalido!\n");
                }
                setbuf(stdin, NULL);/*limpa o buffer*/
                move = getchar();
                do {} while (getchar() != '\n');
            }

            movimenta(matriz, move);/*Move a peca*/

            comeca++;/*Muda o jogador que esta jogando*/

            quem_venceu = verifica_fim(matriz); /*Verifica se alguem ganhou*/

            if (quem_venceu == 1){
                limpa_tela();/*Limpa a tela, opcional*/
                vitoria++; /*Sai do loop maior, acaba esse jogo especifico*/
                pontuacao_jogador_1++; /*Adiciona uma vitoria ao placar do jogador 1*/
                printf("\n");
                printa_matriz(matriz);
                printf("\n\nO Jogador 1 Venceu!!!");

            }
            else if (quem_venceu == -1){
                limpa_tela();/*Limpa a tela, opcional*/
                vitoria++;/*Sai do loop maior, acaba esse jogo especifico*/
                pontuacao_jogador_2++; /*Adiciona uma vitoria ao placar do jogador 2*/
                printf("\n");
                printa_matriz(matriz);
                printf("\n\nO Jogador 2 Venceu!!!");
            }
        }

    printf("\n%d X %d", pontuacao_jogador_1, pontuacao_jogador_2);
    reseta_tabuleiro(matriz); /*reinicia o tabuleiro*/

    printf("\nCaso desejem continuar digitem S ou s, caso desejem parar digitem qualquer outra coisa. ");
    setbuf(stdin, NULL);/*limpa o buffer*/
    continua = getchar();
    do {} while (getchar() != '\n');

    } while(continua == 's' || continua == 'S');
}


int main(void){ 
    char matriz[LINHA][COLUNA] = tabuleiro; /*Tabuleiro do jogo*/
    char resposta[10], *ptr;
    int ret;

    int k, sair = 0;
    while(sair==0){
        imprime_menu();
        fgets(resposta, 9, stdin);
        for (k=0; k < 10; k++){
            if (resposta[k] == '\n'){
                resposta[k] = '\0'; 
            }
        }/*Troca o ultimo caractere de enter para um \0*/
        ret = strtol(resposta, &ptr, 10);

        switch (ret){
            case 1:
                game_loop(matriz);
                break;
            case 2:
                creditos();
                break;
            case 3:
                regras();
                break;
            default:
                sair++;
                return 0;
            }
        }
    return 0;
}
