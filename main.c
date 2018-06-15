//Paulo Inay Cruz - Nro USP: 10388691

#include <stdio.h>
#include <stdlib.h>

typedef struct valormatriz {
    float valor;
    int coord_i;
    int coord_j;
} valormatriz;

void Gauss_Seidel(valormatriz *Valores, int linhas, int colunas, int quantidade_de_valores){
    if (colunas - linhas){
        printf("Erro! Para a resolucao da matriz, e necessario que ela seja quadrada.\n");
        return;
    }

    float *checkall;
    checkall = (float *) calloc(linhas, sizeof(float));
    if (!checkall){
        printf("Erro na alocacao dinamica dos dados!\n");
        exit(0);
    }

    int contador;
    for (contador = 0; contador < linhas; contador++){
        checkall[contador] = 0;
    }
    for (contador = 0; contador < quantidade_de_valores; contador++){
        if(Valores[contador].coord_i == Valores[contador].coord_j){
            checkall[Valores[contador].coord_i] = Valores[contador].valor;
        }
    }
    for (contador = 0; contador < linhas; contador++){
        if (checkall[contador] == 0){
            printf("Erro! A matriz deve ter todos os valores na diagonal principal diferentes de 0.\n");
            return;
        }
    }
    int intera;
    printf("\nDe o numero de iteracoes do metodo:\n");
    scanf("%d", &intera);
    fflush(stdin);
    float *chute;
    chute = (float *) calloc(linhas, sizeof(float));
    if (!chute){
        printf("Erro na alocacao dinamica dos dados!\n");
        exit(0);
    }
    for (contador =0 ; contador < linhas; contador++){
        chute[contador] = 0;
    }
    printf("De os resultados do sistema linear de cada linha, de 0 para n:\n");
    float *resultados;
    resultados = (float *) calloc(linhas, sizeof(float));
    if (!resultados){
        printf("Erro na alocacao dinamica dos dados!\n");
        exit(0);
    }
    for (contador = 0; contador < linhas; contador++){
        scanf("%f", &resultados[contador]);
        fflush(stdin);
    }

    float *soma;
    soma = (float *) calloc(linhas, sizeof(float));
    if (!soma){
        printf("Erro na alocacao dinamica dos dados!\n");
        exit(0);
    }

    for (contador = 0; contador < intera; contador++){
        int contador2;
        for (contador2 = 0; contador2 < linhas; contador2++){
            int contador3;
            soma[contador2] = 0;
            for (contador3 = 0; contador3 < quantidade_de_valores; contador3++){
                if (Valores[contador3].coord_i == contador2){
                    if (Valores[contador3].coord_j != contador2){
                        soma[contador2] -= ((Valores[contador3].valor * chute[Valores[contador3].coord_j]) / checkall[contador2]);
                    }
                }
            }
            soma[contador2] += (resultados[contador2] / checkall[contador2]);
            chute[contador2] = soma[contador2];
        }
    }
    printf("Resultados:\n");
    for (contador = 0; contador < linhas - 1; contador++){
        printf("X[%d]: %.4f, ", contador, chute[contador]);
    }
    printf("X[%d]: %.4f.\n", contador, chute[contador]);
    free(chute);
    free(soma);
    free(resultados);
    free(checkall);

}

void Atribui_valor(valormatriz *Valores, int linhas, int colunas, int quantidade_de_valores, int quantmax, int add){
    int contador;
    printf("\n");
    for (contador = 0; contador < add; contador++){
        int flag = 1;
        while(flag){
            while(1){
                printf("Insira o indice i do valor na matriz (a qual linha pertence, partindo do 0):\n");
                scanf("%d", &Valores[quantidade_de_valores+contador].coord_i);
                fflush(stdin);
                if (Valores[quantidade_de_valores+contador].coord_i >= linhas){
                    printf("Este numero extrapola o numero de linhas da matriz!\n");
                    continue;
                }
                if (Valores[quantidade_de_valores+contador].coord_i < 0){
                    printf("Valor invalido!\n");
                    continue;
                }
                break;
            }

            while(1){
                printf("Insira o indice j do valor na matriz (a qual coluna pertence, partindo do 0):\n");
                scanf("%d", &Valores[quantidade_de_valores+contador].coord_j);
                fflush(stdin);
                if (Valores[quantidade_de_valores+contador].coord_j >= colunas){
                    printf("Este numero extrapola o numero de colunas da matriz!\n");
                    continue;
                }
                if (Valores[quantidade_de_valores+contador].coord_j < 0){
                    printf("Valor invalido!\n");
                    continue;
                }
                break;
            }
            int flag2=0;
            int contador2;
            for (contador2 = 0; contador2 < (quantidade_de_valores + contador); contador2++){
                if (Valores[contador2].coord_i == Valores[quantidade_de_valores+contador].coord_i && Valores[contador2].coord_j == Valores[quantidade_de_valores+contador].coord_j){
                    printf("Este indice ja possui um valor! Insira outro.\n");
                    flag2 = 1;
                }
            }
            if (!flag2) flag = 0;
        }
        printf("Insira o valor a ser adicionado na matriz:\n");
        scanf("%f", &Valores[quantidade_de_valores+contador].valor);
        fflush(stdin);
    }


}

void Calcula_somalinha(valormatriz *Valores, int linhas, int quantidade_de_valores){
    float soma = 0;
    printf("\n");
    int alinha;
    while(1){
        printf("De qual linha voce deseja calcular a soma?\n");
        scanf("%d", &alinha);
        fflush(stdin);
        if (alinha >= linhas || alinha < 0){
            printf("Valor invalido, insira um valor positivo e menor ou igual a 'numerodelinhas - 1'!\n");
        } else break;
    }
    int contador;
    for (contador = 0; contador < quantidade_de_valores; contador++){
        if (Valores[contador].coord_i == alinha){
            soma += Valores[contador].valor;
        }
    }
    printf("A soma eh: %.4f\n", soma);
}

void Calcula_somacoluna(valormatriz *Valores, int colunas, int quantidade_de_valores){
    float soma = 0;
    printf("\n");
    int acoluna;
    while(1){
        printf("De qual coluna voce deseja calcular a soma?\n");
        scanf("%d", &acoluna);
        fflush(stdin);
        if (acoluna >= colunas || acoluna < 0){
            printf("Valor invalido, insira um valor positivo e menor ou igual a 'numerodecolunas - 1'!\n");
        } else break;
    }
    int contador;
    for (contador = 0; contador < quantidade_de_valores; contador++){
        if (Valores[contador].coord_j == acoluna){
            soma += Valores[contador].valor;
        }
    }
    printf("A soma eh: %.4f\n", soma);
}

int Criarmatriz(valormatriz *Valores, int linhas, int colunas, int quantmax){
        char opcaoinsert_user;
        printf("\nSelecione uma das duas opcoes para a insercao de valores:\n    1- Inserir todos os valores da matriz.\n    2- Inserir os valores da matriz diferentes de 0.\n");
        scanf("%c", &opcaoinsert_user);
        fflush(stdin);
        while(opcaoinsert_user < '1' || opcaoinsert_user > '2'){
            printf("Invalido, digite 1 ou 2:\n");
            scanf("%c", &opcaoinsert_user);
            fflush(stdin);
        }
        int quantvalor = 0;

        switch (opcaoinsert_user){
            case '1':
                printf("Insira os valores da matriz:\n");
                int contador1;
                float checkvalue;
                for (contador1 = 0; contador1 < linhas * colunas; contador1++){
                    scanf("%f", &checkvalue);
                    fflush(stdin);
                    if (checkvalue){
                        Valores[quantvalor].valor = checkvalue;
                        Valores[quantvalor].coord_j = contador1%colunas;
                        Valores[quantvalor].coord_i = contador1/colunas;
                        quantvalor++;
                    }
                    if (quantvalor == quantmax){
                        printf("O numero limite de valores diferentes de 0 foi atingido! O resto dos valores serao considerados como 0.\n");
                        break;
                    }
                }
                break;

            case '2':;
                float checkvalue2;
                while (1){ //Para os loops à seguir, sei que o uso de breaks e continues é questionável, porém achei que o código ficaria
                           //mais fácil de entender com eles do que utilizando flags, pois as condições são diretamente relacionadas com
                           //a quebra ou continuidade do laço (e são mais de uma).
                    if (quantvalor == quantmax){
                        printf("O numero limite de valores diferentes de 0 foi atingido!\n");
                        break;
                    }
                    int flag = 1;

                    while(flag){
                        while(1){
                            printf("Insira o indice i do valor na matriz (a qual linha pertence, partindo do 0):\n");
                            scanf("%d", &Valores[quantvalor].coord_i);
                            fflush(stdin);
                            if (Valores[quantvalor].coord_i >= linhas){
                                printf("Este numero extrapola o numero de linhas da matriz!\n");
                                continue;
                            }
                            if (Valores[quantvalor].coord_i < 0){
                                printf("Valor invalido!\n");
                                continue;
                            }
                            break;
                        }

                        while(1){
                            printf("Insira o indice j do valor na matriz (a qual coluna pertence, partindo do 0):\n");
                            scanf("%d", &Valores[quantvalor].coord_j);
                            fflush(stdin);
                            if (Valores[quantvalor].coord_j >= colunas){
                                printf("Este numero extrapola o numero de colunas da matriz!\n");
                                continue;
                            }
                            if (Valores[quantvalor].coord_j < 0){
                                printf("Valor invalido!\n");
                                continue;
                            }
                            break;
                        }
                        int flag2=0;
                        int contador2;
                        for (contador2 = 0; contador2 < quantvalor; contador2++){
                            if (Valores[contador2].coord_i == Valores[quantvalor].coord_i && Valores[contador2].coord_j == Valores[quantvalor].coord_j){
                                printf("Este indice ja possui um valor! Insira outro.\n");
                                flag2 = 1;
                            }
                        }
                        if (!flag2) flag = 0;
                    }
                    printf("Insira o valor a ser adicionado na matriz (se ja terminou de adicionar os valores, digite 0):\n");
                    scanf("%f", &checkvalue2);
                    fflush(stdin);
                    if (!checkvalue2) break;

                    Valores[quantvalor].valor = checkvalue2;

                    quantvalor++;

                } break;
        }
        return quantvalor;
}

void Consulta_valor(int linhas, int colunas, valormatriz *Valores, int quantidade_de_valores){
    printf("Insira o valor do indice i do valor que deseja consultar na matriz, considerando a primeira linha como 0:\n");
    int opcaoconsulti_user;
    scanf("%d", &opcaoconsulti_user);
    fflush(stdin);
    while (opcaoconsulti_user >= linhas || opcaoconsulti_user < 0){
        printf("Valor invalido! Nao extrapole a quantidade de linhas e nao de um valor menor que 0!\n");
        scanf("%d", &opcaoconsulti_user);
        fflush(stdin);
    }
    printf("Insira o valor do indice j do valor que deseja consultar na matriz, considerando a primeira coluna como 0:\n");
    int opcaoconsultj_user;
    scanf("%d", &opcaoconsultj_user);
    fflush(stdin);
    while (opcaoconsultj_user >= colunas || opcaoconsultj_user < 0){
        printf("Valor invalido! Nao extrapole a quantidade de colunas e nao de um valor menor que 0!\n");
        scanf("%d", &opcaoconsultj_user);
        fflush(stdin);
    }

    int contador4;
    for (contador4 = 0; contador4 < quantidade_de_valores; contador4++){
        if (Valores[contador4].coord_i == opcaoconsulti_user && Valores[contador4].coord_j == opcaoconsultj_user){
            printf("O valor e: %.4f\n", Valores[contador4].valor);
            break;
        }
    }
    if (contador4 == quantidade_de_valores){
        printf("O valor e: 0.0000\n");
    }
}



int main()
{
    /* Declarações */
    int linhas;
    int colunas;
    valormatriz *Valores;
    int quantidade_de_valores;
    int quantmax;

    /* */

    printf("Matriz-Esparsa \n \n \n");

    char opcaogeral_user = 0;
    char opcaoinsert_user;

    printf("Insira a quantidade de linhas que a matriz possui:\n");
    scanf("%d", &linhas);
    fflush(stdin);

    printf("Insira a quantidade de colunas que a matriz possui:\n");
    scanf("%d", &colunas);
    fflush(stdin);

    printf("Insira um limite maximo para a quantidade de valores diferentes de 0 que existem na matriz:\n");
    scanf("%d", &quantmax);
    fflush(stdin);
    Valores = (valormatriz *) calloc(sizeof(valormatriz), quantmax);
    if (!Valores){
        printf("Erro na alocacao dinamica dos dados!\n");
        exit(0);
    }

    /* */

    quantidade_de_valores = Criarmatriz(Valores, linhas, colunas, quantmax);

    /* */

    while(opcaogeral_user != '7'){
        printf("\nEscolha uma das operacoes a seguir para a matriz:\n    1- Criar outra matriz\n    2- Consultar um valor da matriz.\n    3- Calcular soma dos valores de uma linha da matriz.\n    4- Calcular soma dos valores de uma coluna da matriz.\n    ");
        printf("5- Atribuir novos valores a matriz.\n    6- Resolver o sistema linear da matriz.\n    7- Sair.\n");
        scanf("%c", &opcaogeral_user);
        fflush(stdin);
        while (opcaogeral_user < '1' || opcaogeral_user > '7'){
            printf("Invalido, digite um valor de 1 a 8:\n");
            scanf("%c", &opcaoinsert_user);
            fflush(stdin);
        }
        if (opcaogeral_user == '1'){
            free(Valores);
            printf("\nInsira a quantidade de linhas que a matriz possui:\n");
            scanf("%d", &linhas);
            fflush(stdin);

            printf("Insira a quantidade de colunas que a matriz possui:\n");
            scanf("%d", &colunas);
            fflush(stdin);

            printf("Insira um limite maximo para a quantidade de valores diferentes de 0 que existem na matriz:\n");
            scanf("%d", &quantmax);
            fflush(stdin);
            Valores = (valormatriz *) calloc(sizeof(valormatriz), quantmax);
            if (!Valores){
                printf("Erro na alocacao dinamica dos dados!\n");
                exit(0);
            }

            quantidade_de_valores = Criarmatriz(Valores, linhas, colunas, quantmax);
        }

        switch(opcaogeral_user){
        case '2':
            /* */
            Consulta_valor(linhas, colunas, Valores, quantidade_de_valores);
            /* */
            break;
        case '3':
            /* */
            Calcula_somalinha(Valores, linhas, quantidade_de_valores);
            /* */
            break;
        case '4':
            /* */
            Calcula_somacoluna(Valores, linhas, quantidade_de_valores);
            /* */
            break;
        case '5':;
            /* */
            int add;
            while(1){
                printf("Quantos valores deseja adicionar a matriz?\n");
                scanf("%d", &add);
                fflush(stdin);
                if ((quantidade_de_valores+add) > (linhas * colunas)){
                    printf("Invalido! A quantidade de valores que deseja adicionar e maior que a capacidade da matriz! Insira outro valor.\n");
                } else break;
            }
            if ((add + quantidade_de_valores) > quantmax){
                Valores = (valormatriz *) realloc(Valores, (add + quantidade_de_valores) * sizeof(valormatriz));
                if (!Valores){
                    printf("Erro na alocacao dinamica dos dados!\n");
                    exit(0);
                }
                quantmax = quantidade_de_valores+add;
            }
            Atribui_valor(Valores, linhas, colunas, quantidade_de_valores, quantmax, add);
            /* */
            break;
        case '6':
            /* */
            Gauss_Seidel(Valores, linhas, colunas, quantidade_de_valores);
            /* */
            break;
        default:
            ;
        }
    }
    free(Valores);
}
