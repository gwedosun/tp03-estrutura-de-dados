#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "expressao.h"

int main(){
    char expressaoUsuario[512];
    while(1){
        printf("Digite sua expressao: ");
        fgets(expressaoUsuario, 512, stdin);

        expressaoUsuario[strcspn(expressaoUsuario, "\n")] = '\0';

        if(strcmp(expressaoUsuario, "sair") == 0){
            break;
        }

        char copia[512];
        strcpy(copia, expressaoUsuario);
        printf("Copia da expressao: %s\n", getFormaInFixa(copia));
        printf("Valor pos-fixa: %.1f\n", getValorPosFixa(expressaoUsuario));
    }

    return 0;

}