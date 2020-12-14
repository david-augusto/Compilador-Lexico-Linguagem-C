# Compilador-Lexico-Linguagem-C

    1. OBJETIVO
    O objetivo desse projeto foi desenvolver e projetar a fase de Análise Léxica 
    de um Compilador para a linguagem de programação C.

    2. RESULTADOS EXPERIMENTAIS
    A partir de um arquivo .txt, que contém um programa em C, foram gerados dois 
    arquivos: a tabela de símbolos e a de tokens. Foram especificados e criados 
    tokens, para determinados autômatos reconhecidos.
    O ambiente de programação utilizado foi o Dev C (no Windows) e o GCC – 
    GNU Compiler Collection (no Linux).
    
    3. ANÁLISE E CONCLUSÃO
    Foi criado um arquivo com as palavras-chaves e também foi criada uma função
    para verificar se a palavra gerada no autômato era uma palavra-chave ou não.
    Se for uma palavra-chave, a tabela de símbolos irá retornar a posição 
    da palavra. Se não for, a função irá verificar se já existe uma palavra igual
    na tabela de símbolos. Se existir, ela vai         guardar a posição da palavra.
    Do contrário, a palavra será armazenada na última linha do arquivo.
    Foram criados autômatos para cada especificação de token dada pelo professor. 
    A função desses autômatos é reconhecer os tokens.

        
        
