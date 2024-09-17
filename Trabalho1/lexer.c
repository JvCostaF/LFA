/*
Joao Victor da Costa Farias
Ricardo Ramalho De Lima Junior
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define QTD_PALAVRAS_RESERVADAS 3
#define QTD_SIMBOLOS 9

const char *palavrasReservadas[QTD_PALAVRAS_RESERVADAS] = {"if", "else", "while"};

const char *simbolos[QTD_SIMBOLOS] = {"+", "-", "*", "/", "=", ";", "%", "(", ")"};

int caracter;

int leuNumero(int caracter){
    return (caracter >= '0' && caracter <= '9');
}

int leuLetraMaiuscula(int caracter){
    return (caracter >= 'A' && caracter <= 'Z');
}

int leuLetraMinuscula(int caracter){
    return (caracter >= 'a' && caracter <= 'z');
}

int leuNome(int caracter, int flag){
    if(flag){
        return (leuLetraMaiuscula(caracter) || leuLetraMinuscula(caracter) || leuNumero(caracter));
    }else{
        return (leuLetraMaiuscula(caracter) || leuLetraMinuscula(caracter));
    }
}

int leuCaractereInvalido(char caracter){
    char invalido = '$';
    if(caracter == invalido) {
        return 1;
    }
    return 0;
}

int leuPalavraReservada(const char *palavra){
    int i;
    for (i = 0; i < QTD_PALAVRAS_RESERVADAS; i++) {
        if (strcmp(palavra, palavrasReservadas[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int leuSimbolo(char caracter){ 
    for (int i = 0; i < QTD_SIMBOLOS; i++) {
        if (caracter == *simbolos[i]){
            return 1;
        }
    }
    return 0;
}

void proxToken(){
    if (caracter == '/'){
        caracter = getchar();
        if (caracter == '*'){
            int fim[2] = {0,0}; 
            char comentario[500]; 
            comentario[0] = "/"; 
            comentario[1] = caracter; 
                
            int i = 2; 
                
            while (!fim[1]){ 
                    
                caracter = getchar(); 
                comentario[i] = caracter; 
                        
                if (((caracter == '/')) && (fim[0])){ 
                    fim[1] = 1; 
                } 

                if (caracter == EOF){
                    printf("ERRO: Faltou fechar um comentário \n");
                    exit(1);
                }
                        
                if (caracter == '*'){ 
                    fim[0] = 1;
                } else{ 
                    fim[0] = 0; 
                } 
            } 
            return; 
        } else{ 
            printf("/\n");
            ungetc(caracter, stdin);
            return; 
        } 
    } else if(leuNome(caracter,0)){
        char palavra[20];
        int i = 0;
        while(leuNome(caracter,1)){
            palavra[i] = caracter;
            i++;
            caracter = getchar();
        }
        palavra[i] = '\0';
        if (!leuPalavraReservada(palavra)){
            printf("Nome %s\n", palavra);
            ungetc(caracter,stdin);
            return;
        } else{            
            printf("%s\n", palavra);
            ungetc(caracter,stdin);
            return;
        }   
    } else if(leuNumero(caracter)){
        char num[64];
        int i = 0;
        while(leuNumero(caracter)){
            num[i] = caracter;
            i += 1;
            caracter = getchar();
        }
        num[i] = '\0';
        printf("Num %s\n", num);
        ungetc(caracter,stdin);
        return;
    } else if(leuSimbolo(caracter)){ 
        printf("%c\n", caracter); 
        return; 
    } else if(isspace(caracter)){
        return;
    }else{
        printf("ERRO: Caractere inválido '%c'\n", caracter);
    }
}

int main(){
    while((caracter = getchar()) != EOF){
        proxToken();
    }

    return 0;
}
