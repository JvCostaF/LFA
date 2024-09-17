Segundo Trabalho - Linguagens Formais

Alunos: João Victor da Costa Farias e Ricardo Ramalho de Lima Junior.

Como rodar o programa:

1) Acesse o diretório onde os arquivos foram extraídos;
2) Utilizando um compilador C (nós utilizamos o gcc) compile o programa main.c;
    *Pelo GCC*
    2.1) $ gcc -o regexp main.c
    2.2) $ ./regexp < nome_do_arquivo.txt

ou 

    2.3) $ echo "expressão" | ./regexp

**OBS:**
    - No item *2.1* estamos criando um executável a partir do arquivo lexer.c com o gcc. 
    - No item *2.2* estamos lendo um arquivo em formato txt como entrada padrão.
    - No item *2.3* estamos lendo uma string passada no terminal como entrada padrão.

A saída vai seguir as regras conforme o enunciado.