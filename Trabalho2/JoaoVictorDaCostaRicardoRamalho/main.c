/*  
Ricardo Ramalho de Lima Junior 
João Victor da Costa Farias 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum RegExpTag {
        TAG_EMPTY,
        TAG_CHAR,
        TAG_STAR,
        TAG_CONCAT,
        TAG_UNION,
    };

struct RegExp {
    char tag;
    union {
        struct {
            char c;
        } ch;
        struct {
            struct RegExp *filho;
        } un;
        struct {
            struct RegExp *filho1;
            struct RegExp *filho2;
        } bin;
    } u;
};

typedef struct RegExp RegExp;

RegExp *new_empty(){
    RegExp *exp = malloc(sizeof(RegExp));
    exp->tag = TAG_EMPTY;

    return exp;
}

RegExp *new_char(char c){
    RegExp *exp = malloc(sizeof(RegExp));
    exp->tag = TAG_CHAR;
    exp->u.ch.c = c;

    return exp;
}

RegExp *new_star(RegExp *filho){
    RegExp *exp = malloc(sizeof(RegExp));
    exp->tag=TAG_STAR;
    exp->u.un.filho = filho;

    return exp;
}

RegExp *new_concat(RegExp *filho1, RegExp *filho2){
    RegExp *exp = malloc(sizeof(RegExp));
    exp->tag=TAG_CONCAT;
    exp->u.bin.filho1 = filho1;
    exp->u.bin.filho2 = filho2;

    return exp;
}

RegExp *new_union(RegExp *filho1, RegExp *filho2){
    RegExp *exp = malloc(sizeof(RegExp));
    exp->tag=TAG_UNION;
    exp->u.bin.filho1 = filho1;
    exp->u.bin.filho2 = filho2;

    return exp;
}

void imprime_arvore(RegExp *arvore, int identacao){
    for (int i = 0; i<identacao; i++){
        printf(" ");
    }
    switch(arvore->tag){
        case TAG_EMPTY:
        printf("EMPTY\n");
        break;
        case TAG_CHAR:
        printf("CHAR %c\n", arvore->u.ch.c);
        break;
        case TAG_STAR:
        printf("STAR\n");
        imprime_arvore(arvore->u.un.filho, identacao+1);
        break;
        case TAG_CONCAT:
        printf("CONCAT\n");
        imprime_arvore(arvore->u.bin.filho1, identacao+1);
        imprime_arvore(arvore->u.bin.filho2, identacao+1);
        break;
        case TAG_UNION:
        printf("UNION\n");
        imprime_arvore(arvore->u.bin.filho1, identacao+1);
        imprime_arvore(arvore->u.bin.filho2, identacao+1);
        break;
    }
}

static RegExp *parse_regexp();
static RegExp *parse_uniao();
static RegExp *parse_concat();
static RegExp *parse_estrela();
static RegExp *parse_basico();

int caracter, ind;
int flag = 1;
char expressao[1024];

void prox_caractere(){
    ind++;
    caracter = expressao[ind];
}

/*
    Nossa gramática:
    Regexp -> Uniao
    Uniao -> lista de uma ou mais concatenações, separadas por '|'
    Concat -> lista potencialmente vazia de itens estrelados
    Estrela -> item básico, seguido de zero ou mais estrelas
    Basico -> um caractere não-especial, ou uma regexp entre parênteses.
*/

static RegExp *parse_regexp(){
    return parse_uniao();
}

static RegExp *parse_uniao(){
    RegExp *lado_esquerdo = parse_concat();
    if(caracter == '|'){
        prox_caractere();
        lado_esquerdo = new_union(lado_esquerdo, parse_uniao());
    }
    return lado_esquerdo;
}

static RegExp *parse_concat(){
    RegExp *lado_esquerdo = parse_estrela();
    if(isalpha(caracter) || caracter == '('){
        lado_esquerdo = new_concat(lado_esquerdo, parse_concat());
    }
    return lado_esquerdo;
}

static RegExp *parse_estrela(){
    RegExp *expressao_base = parse_basico();
    while(caracter == '*'){
        prox_caractere();
        expressao_base = new_star(expressao_base);
    }
    return expressao_base;
}

static RegExp *parse_basico(){
    RegExp *expressao_base = new_empty();

    if((expressao[ind+1] == '\0') && (flag >= 1)){
        printf("Erro de sintaxe na posicao %d: esperava ')', encontrei '%c'\n", ind, caracter);
        exit(1);
    }
    if(isalpha(caracter)){
        expressao_base = new_char(caracter);
        prox_caractere();
    }
    if(caracter == '('){
        flag++;
        prox_caractere();
        expressao_base = parse_regexp();
    }
    if(caracter == ')'){
        flag--;
        prox_caractere();
        if(!(flag)){
            printf("Erro de sintaxe na posicao %d: esperava '\\n', encontrei ')'\n", ind);
            exit(1);
        }
    }
    return expressao_base;
}


int main(void) {

    while (fgets(expressao, sizeof(expressao), stdin)) {
        ind = 0;
        caracter = expressao[ind];

        RegExp *raiz = parse_regexp();

        imprime_arvore(raiz, 0);
    }

    return 0;
    
}