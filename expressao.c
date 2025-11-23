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
    if (p->topo < 511) { 
        p->topo++;
        p->dados[p->topo] = Valor;
    }
}

float desempilhar(Pilha * p){
    if (p->topo >= 0) {
        float Aux = p->dados[p->topo];
        p->topo--;
        return Aux;
    }
    return 0.0; 
}


void empilharString(PilhaString * p, char * String){
    if (p->topo < 511) {
        p->topo++;
        strcpy(p->dados[p->topo], String);
    }
}

// retorna null caso erro
char * desempilharString(PilhaString * p){
    if (p->topo >= 0) {
        char * aux = p->dados[p->topo];
        p->topo--;
        return aux;
    }
    return NULL; 
}


float getValorPosFixa(char * StrPosFixa){
    char StrCopia[512]; 
    strcpy(StrCopia, StrPosFixa);

    Pilha p;
    p.topo = -1;

    char * token = strtok(StrCopia, " ");

    while(token != NULL){
        if(strcmp(token, "+") == 0){
            float B = desempilhar(&p);
            float A = desempilhar(&p);
            empilhar(&p, A + B);
        }
        else if(strcmp(token, "-") == 0){
            float B = desempilhar(&p);
            float A = desempilhar(&p);
            empilhar(&p, A - B);
        }
        else if(strcmp(token, "*") == 0){
            float B = desempilhar(&p);
            float A = desempilhar(&p);
            empilhar(&p, A * B);
        }
        else if(strcmp(token, "/") == 0){
            float B = desempilhar(&p);
            float A = desempilhar(&p);
            if(B != 0) empilhar(&p, A / B);
            else empilhar(&p, 0); 
        }
        else if(strcmp(token, "^") == 0){
            float B = desempilhar(&p);
            float A = desempilhar(&p);
            empilhar(&p, pow(A, B));
        }
        else if(strcmp(token, "sen") == 0){
            float A = desempilhar(&p);
            empilhar(&p, sin(A * (3.14159 / 180)));
        }
        else if(strcmp(token, "cos") == 0){
            float A = desempilhar(&p);
            empilhar(&p, cos(A * (3.14159 / 180)));
        }
        else if(strcmp(token, "tg") == 0){
            float A = desempilhar(&p);
            empilhar(&p, tan(A * (3.14159 / 180)));
        }
        else if(strcmp(token, "log") == 0){
            float A = desempilhar(&p);
            empilhar(&p, log10(A));
        }
        else if(strcmp(token, "raiz") == 0){
            float A = desempilhar(&p);
            if (A >= 0) empilhar(&p, sqrt(A));
            else empilhar(&p, 0);
        } 
        else {
            float Numero = atof(token);
            empilhar(&p, Numero);
        }
        token = strtok(NULL, " ");
    }

    if (p.topo == -1) return 0.0; 
    return desempilhar(&p);
}

char * getFormaInFixa(char * Str){
    static char Resultado[512];
    PilhaString p;
    p.topo = -1;

    char StrCopia[512];
    strcpy(StrCopia, Str);

    char * token = strtok(StrCopia, " ");

    while(token != NULL){
        char novaExpressao[512];
        char * A;
        char * B;

        // operadores binários
        if(strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || 
           strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || 
           strcmp(token, "^") == 0 || strcmp(token, "%") == 0) {
            
            // verificação de erro
            B = desempilharString(&p);
            A = desempilharString(&p);
            if (A == NULL || B == NULL) return NULL; 

            if(strcmp(token, "+") == 0) {
                sprintf(novaExpressao, "%s+%s", A, B);

            } 
            else if(strcmp(token, "-") == 0) {
                sprintf(novaExpressao, "%s-%s", A, B);

            } else {

                char A_formatado[512], B_formatado[512];
                

                if(strchr(A, '+') != NULL || strchr(A, '-') != NULL) sprintf(A_formatado, "(%s)", A);
                else strcpy(A_formatado, A);


                if(strchr(B, '+') != NULL || strchr(B, '-') != NULL) sprintf(B_formatado, "(%s)", B);
                else strcpy(B_formatado, B);

                if(strcmp(token, "*") == 0) sprintf(novaExpressao, "%s*%s", A_formatado, B_formatado);
                else if(strcmp(token, "/") == 0) sprintf(novaExpressao, "%s/%s", A_formatado, B_formatado);
                else if(strcmp(token, "^") == 0) sprintf(novaExpressao, "%s^%s", A_formatado, B_formatado);

                else if(strcmp(token, "%") == 0) sprintf(novaExpressao, "%s%%%s", A_formatado, B_formatado);
            }

            empilharString(&p, novaExpressao);

        }

        // operadores unarios
        else if(strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 || 
                strcmp(token, "tg") == 0  || strcmp(token, "log") == 0 || 
                strcmp(token, "raiz") == 0) {
            
            A = desempilharString(&p);
            if (A == NULL) return NULL; // requisito 3

            if(strcmp(token, "sen") == 0) sprintf(novaExpressao, "sen(%s)", A);
            else if(strcmp(token, "cos") == 0) sprintf(novaExpressao, "cos(%s)", A);
            else if(strcmp(token, "tg") == 0) sprintf(novaExpressao, "tg(%s)", A);
            else if(strcmp(token, "log") == 0) sprintf(novaExpressao, "log(%s)", A);
            else if(strcmp(token, "raiz") == 0) sprintf(novaExpressao, "raiz(%s)", A);
            
            empilharString(&p, novaExpressao);
        }
        // --- NÚMEROS ---
        else {
            empilharString(&p, token);
        }

        token = strtok(NULL, " ");
    }


    // verificação de erro final
    if (p.topo != 0) {
        return NULL;
    }

    char * Res = desempilharString(&p);
    strcpy(Resultado, Res);
    return Resultado;
}