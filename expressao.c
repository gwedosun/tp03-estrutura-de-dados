#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "expressao.h"

typedef struct {
    float dados[512];
    int topo;
} Pilha;

typedef struct {
    char dados[512][512];
    int topo;
} PilhaString;

void empilhar(Pilha * p, float Valor){
    p->topo++;
    p->dados[p->topo] = Valor;
}

float desempilhar(Pilha * p){
    float Aux;
    Aux = p->dados[p->topo];
    p->topo--;
    return Aux;
}

float getValorPosFixa(char * StrPosFixa){
    Pilha p;
    p.topo = -1;

    char * token = strtok(StrPosFixa, " ");

    while(token != NULL){
        if(strcmp(token, "+") == 0){
            float B = desempilhar(&p);
            float A = desempilhar(&p);
            float Soma = A + B;
            empilhar(&p, Soma);
        }

        else if(strcmp(token, "-") == 0){
            float B = desempilhar(&p);
            float A = desempilhar(&p);
            float Subtracao = A - B;
            empilhar(&p, Subtracao);
        }

        else if(strcmp(token, "*") == 0){
            float B = desempilhar(&p);
            float A = desempilhar(&p);
            float Produto = A * B;
            empilhar(&p, Produto);
        }

        else if(strcmp(token, "/") == 0){
            float B = desempilhar(&p);
            float A = desempilhar(&p);
            float Quociente = A / B;
            empilhar(&p, Quociente);
        }

        
        else if(strcmp(token, "^") == 0){
            float B = desempilhar(&p);
            float A = desempilhar(&p);
            float Potencia = pow(A, B);
            empilhar(&p, Potencia);
        }

        else if(strcmp(token, "sen") == 0){
            float A = desempilhar(&p);
            float Angulo = A * (3.14159 / 180);
            float Seno = sin(Angulo);
            empilhar(&p, Seno);
        }

        else if(strcmp(token, "cos") == 0){
            float A = desempilhar(&p);
            float Angulo = A * (3.14159 / 180);
            float Cosseno = cos(Angulo);
            empilhar(&p, Cosseno);
        }

        else if(strcmp(token, "tg") == 0){
            float A = desempilhar(&p);
            float Angulo = A * (3.14159 / 180);
            float Tangente = tan(Angulo);
            empilhar(&p, Tangente);
        }

        else if(strcmp(token, "log") == 0){
            float A = desempilhar(&p);
            float Logaritmo = log10(A);
            empilhar(&p, Logaritmo);
        }

        else if(strcmp(token, "raiz") == 0){
            float A = desempilhar(&p);
            float raizQuadrada = sqrt(A);
            empilhar(&p, raizQuadrada);
        } else {
        float Numero = atof(token);
        empilhar(&p, Numero);
    }


        token = strtok(NULL, " ");
    }

    return desempilhar(&p);
}

void empilharString(PilhaString * p, char * String){
    p->topo++;
    strcpy(p->dados[p->topo], String);
}

char * desempilharString(PilhaString * p){
    char * aux = p->dados[p->topo];
    p->topo--;
    return aux;
}

char * getFormaInFixa(char * String){
    static char Resultado[512];
    PilhaString p;
    p.topo = -1;

    char * token = strtok(String, " ");

    while(token != NULL){

        if(strcmp(token, "+") == 0){
            char * B = desempilharString(&p);
            char * A = desempilharString(&p);
            char novaExpressao[512];

            sprintf(novaExpressao, "(%s+%s)", A, B);

            empilharString(&p, novaExpressao);

        } else if (strcmp(token, "-") == 0){
            char * B = desempilharString(&p);
            char * A = desempilharString(&p);
            char novaExpressao[512];

            sprintf(novaExpressao, "(%s-%s)", A, B);

            empilharString(&p, novaExpressao);

        } else if(strcmp(token, "*") == 0){
            char * B = desempilharString(&p);
            char * A = desempilharString(&p);
            char novaExpressao[512];

            sprintf(novaExpressao, "(%s*%s)", A, B);

            empilharString(&p, novaExpressao);

        } else if(strcmp(token, "/") == 0){
            char * B = desempilharString(&p);
            char * A = desempilharString(&p);
            char novaExpressao[512];

            sprintf(novaExpressao, "(%s/%s)", A, B);

            empilharString(&p, novaExpressao);

        } else if(strcmp(token, "^") == 0){
            char * B = desempilharString(&p);
            char * A = desempilharString(&p);
            char novaExpressao[512];

            sprintf(novaExpressao, "(%s^%s)", A, B);

            empilharString(&p, novaExpressao);

        } else if(strcmp(token, "%") == 0){
            char * B = desempilharString(&p);
            char * A = desempilharString(&p);
            char novaExpressao[512];

            sprintf(novaExpressao, "(%s %% %s)", A, B);

            empilharString(&p, novaExpressao);

        } else if(strcmp(token, "sen") == 0){
            char * A = desempilharString(&p);
            char novaExpressao[512];

            sprintf(novaExpressao, "sen(%s)", A);

            empilharString(&p, novaExpressao);

        } else if(strcmp(token, "cos") == 0){
            char * A = desempilharString(&p);
            char novaExpressao[512];

            sprintf(novaExpressao, "cos(%s)", A);

            empilharString(&p, novaExpressao);

        } else if(strcmp(token, "tg") == 0){
            char * A = desempilharString(&p);
            char novaExpressao[512];

            sprintf(novaExpressao, "tg(%s)", A);

            empilharString(&p, novaExpressao);

        } else if(strcmp(token, "log") == 0){
            char * A = desempilharString(&p);
            char novaExpressao[512];

            sprintf(novaExpressao, "log(%s)", A);

            empilharString(&p, novaExpressao);
        
        } else if(strcmp(token, "raiz") == 0){
            char * A = desempilharString(&p);
            char novaExpressao[512];

            sprintf(novaExpressao, "raiz(%s)", A);

            empilharString(&p, novaExpressao);
        
        } else {
            empilharString(&p, token);
        }

        token = strtok(NULL, " ");
    }

    char * Res = desempilharString(&p);
    strcpy(Resultado, Res);
    return Resultado;

};