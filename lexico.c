# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdbool.h>
# include "valor.h"
# include <sys/stat.h>

FILE *arquivo, *escrita;
int partida = 0;
int estado = 0;
int i = 0;
char string[25];
char *keywords[] = {"char", "double", "else", "float", "if", "int", "main", "return", "static", "void", "while"};
int posicao = 0;

void remove_file() {
  remove("tabela_token.txt");
}


bool is_keywords(char *lexema)
{
  int len = sizeof(keywords) / sizeof(keywords[0]);
  int i;
  for (i = 0; i < len; i++)
  {
    if (strcmp(lexema, keywords[i]) == 0)
    {
      return true;
    }
  }
  return false;
}

char* valor_token(char *lexema) 
{
  if (strcmp(lexema, "if") == 0) return IF;
  else if (strcmp(lexema, "==") == 0) return IGUAL;
  else if (strcmp(lexema, "{" ) == 0) return ABRE_CHAVE;
  else if (strcmp(lexema, "[") == 0)return ABRE_COLCHETE;
  else if (strcmp(lexema, "]") == 0)return FIM_COLCHETE;
  else if (strcmp(lexema, "}") == 0) return FIM_CHAVE;
  else if (strcmp(lexema, "-") == 0) return MENOS;
  else if (strcmp(lexema, "=") == 0) return OP_ATR;
  else if (strcmp(lexema, "+") == 0) return MAIS;
  else if (strcmp(lexema, "*") == 0) return VEZES;
  else if (strcmp(lexema, "<") == 0) return MENOR;
  else if (strcmp(lexema, ">") == 0) return MAIOR;
  else if (strcmp(lexema, ">=") == 0) return MAIOR_IGUAL;
  else if (strcmp(lexema, "<=") == 0) return MENOR_IGUAL;
  else if (strcmp(lexema, "<>") == 0) return DIFERENTE;
  else if (strcmp(lexema, "char") == 0) return CHAR;
  else if (strcmp(lexema, "else") == 0) return ELSE;
  else if (strcmp(lexema, "float") == 0) return FLOAT;
  else if (strcmp(lexema, "int") == 0) return INT;
  else if (strcmp(lexema, "main") == 0) return MAIN;
  else if (strcmp(lexema,"return") == 0)return RETURN;
  else if (strcmp(lexema, "static") == 0) return STATIC;
  else if (strcmp(lexema, "void") == 0) return VOID;
  else if (strcmp(lexema, "while") == 0) return WHILE;
  else if (strcmp(lexema, ";") == 0) return PONTO_VIRGULA;
  else if (strcmp(lexema, ")") == 0) return PARENTESE_DIREITO;
  else if (strcmp(lexema, "(") == 0) return PARENTESE_ESQUERDO;
  else if (strcmp(lexema, "num" ) == 0) return NUM;
  else {
    return "271";
  }
}

void tabela_token(char *lexema, char *class)
{
  FILE *token;
  token = fopen("tabela_token.txt", "a");

  if (strcmp(class, "OP_REL") == 0){
    fprintf(token, "%s\t%s\n", OP_REL, valor_token(lexema));
  }else if (strcmp(class, "COLCHETE") == 0) {
    fprintf(token, "%s\t%s\n", COLCHETE, valor_token(lexema));
  }else if (strcmp(class, "OPERADOR_ADITIVO") == 0) {
    fprintf(token, "%s\t%s\n", OPERADOR_ADITIVO_ARITMETICO, valor_token(lexema));
  }else if(strcmp(class, "OP_REL") == 0){
    fprintf(token, "%s\t%s\n", OP_REL, valor_token(lexema));
  }else if (strcmp(class, "num") == 0){
    fprintf(token, "%s\t%s\n", valor_token(class), lexema);
  } else if (strcmp(lexema, "{") == 0 || strcmp(lexema, "}") == 0){
    fprintf(token, "%s\t%s\n", CHAVE, valor_token(lexema));
  }else if (strcmp(lexema, ")") == 0 || strcmp(lexema, "(") == 0){
      fprintf(token, "%s\t%s\n", PARENTESE, valor_token(lexema));
  }else if (!isalpha(lexema[0]) && !isdigit(lexema[0])){
    fprintf(token, "%s\t\n", valor_token(lexema));
  } else if(!is_keywords(lexema)) {
    fprintf(token, "%s\t%d\n", valor_token(lexema), posicao);
  }else{
    fprintf(token, "%s\t\n", valor_token(lexema));
  }

  fclose(token);

  

}


void tabela_simbolos(char *lexema) 
{
  FILE *tabela_simbolos;
  bool achou = false;
  int result;
  char palavra_tabela[20];
  int id;
  int linhas = 0;
  posicao = 0;

  tabela_simbolos = fopen("tabela_simbolos.txt", "a+");

  if (!is_keywords(lexema)) 
  {
    while (!feof(tabela_simbolos))
    {

      result = fscanf(tabela_simbolos, "%s%d", palavra_tabela, &id);
      if (strcmp(lexema, palavra_tabela) == 0)
      {
        achou = true;
        posicao = (linhas++) + 1;
        /**fprintf(tabela_simbolos, "%s\t%d\n", lexema, posicao);
        achou = ++linhas;
        fclose(tabela_simbolos);**/
      }
      linhas++;
    }

    if (!achou) {
      fprintf(tabela_simbolos, "\n%s\t%d", lexema, linhas+1);
      posicao = linhas+1;
    }

  }
  fclose(tabela_simbolos);
}


 
 
int falhar() {
  switch (partida)
  {
    case 0:
      partida = 9;
      break;
    case 9:
      partida = 12;
    break;
    case 12:
      partida = 22;
    break;
    case 22:
      partida = 25;
    break;
    case 25:
      partida = 30;
    break;
    case 30:
      partida = 35;
    break;
    case 35:
      partida = 40;
    break;
    case 40:
      partida = 45;
    break;
    case 45:
      partida = 0;
    break;
  }
  return partida;
}
 
char next_char() 
{
  return getc(arquivo);
}
 
int main(){
  arquivo = fopen("progama.txt", "r");
  int procurar;
  char ch;
  char *token;
  char *classname;

  remove_file();

  while (ch != EOF)
  {
    switch(estado)
    {
      case 0: ch = next_char();
        if (ch == ' ' || ch == '\t' || ch == '\n'){
          estado = 0;
        }
        else if (ch == '>') {
          string[i++] = ch;
          estado = 1;
        }
        else if (ch == '<') {
          string[i++] = ch;
          estado = 3;
        }
        else if (ch == '='){
          string[i++] = ch;
          estado = 6;
        }else{
          estado = falhar();
        }
      break;
      case 1: ch = next_char();
        if (ch == '='){
          estado = 2;
          string[i++] = ch;
        }else {
          string[i] = '\0';
          tabela_token(string, "OP_REL");
          i = 0;
          strcpy(string, "");
          estado = falhar();
        }
      break;
      case 2:
        string[i] = '\0';
        tabela_token(string, "OP_REL");
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 3: ch = next_char();
        if (ch == '=')
        {
          estado = 5;
          string[i++] = ch;
        }
        else if (ch == '>')
        {
          estado = 7;
          string[i++] = ch;
        }else{
          string[i] = '\0';
          tabela_token(string, "OP_REL");
          i = 0;
          strcpy(string, "");
          estado = falhar();
        }
      break;
      case 4:
        string[i] = '\0';
        tabela_token(string, "OP_REL");
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 5:
        string[i] = '\0';
        tabela_token(string, "OP_REL");
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 6: ch = next_char();
        if (ch == '=') {
          string[i++] = ch;
          estado = 7;
          string[i] = '\0';
          tabela_token(string, "OP_REL");
        }else{
          string[i] = '\0';
          tabela_token(string, "OP_ATR");
        }
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 7:
        string[i] = '\0';
        tabela_token(string, "OP_REL");
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 9: 
        if (isalpha(ch)){
          string[i++] = ch;
          estado = 10;
        }else{
          /**i = 0;
          strcpy(string, "");**/
          estado = falhar();

          /*  string[i] = '\0';
          fprintf(escrita, "%s\n", string);
          printf("%s", string);
          i = 0;
          strcpy(string, "");*/
        }
      break;
      case 10: ch = next_char();
        if (isalpha(ch) || isdigit(ch)) {
            estado = 10;
            string[i++] = ch;
        }else{
            estado = 11;
        }
      break;
      case 11:
        string[i] = '\0';
        tabela_simbolos(string);
        tabela_token(string, "string");
        //fprintf(escrita, "%s\n", string);
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 12:
        if (isdigit(ch) ){
          string[i++] = ch;
          estado = 13;
        }else{
          estado = falhar();
        }
      break;
      case 13: ch = next_char();
        if ( isdigit(ch)){
          string[i++] = ch;
          estado = 13;
        }else if (ch == '.'){
          string[i++] = ch;
          estado = 15;
        }else{
          estado = 14;
        }
      break;
      case 14:
        string[i] = '\0';
      //fprintf(escrita, "%s\n", string);
        tabela_token(string, "num");
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 15: ch = next_char();
        if (isdigit(ch)) {
          string[i++] = ch;
        }else{
          estado = 16;
        }
      break;
      case 16:
        string[i] = '\0';
        tabela_token(string, "num");
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 22:
        if (ch == ';') {
          string[i++] = ch;
          estado = 23;
        }else {
          estado = falhar();
        }
      break;
      case 23:
        string[i] = '\0';
        tabela_token(string, "delimitador");
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 25:
        if (ch == ')' || ch == '(') {
          string[i++] = ch;
          estado = 26;
        }else {
          estado = falhar();
        }
      break;
      case 26:
        string[i] = '\0';
        tabela_token(string, "parentese");
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 30:
        if (ch == '+' || ch == '-') {
          estado = 31;
          string[i++] = ch;
        }else{
          estado = falhar();
        }
      break;
      case 31:
        string[i] = '\0';
        tabela_token(string, "OPERADOR_ADITIVO");
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 35:
        if (ch == '}' || ch == '{') {
          estado = 36;
          string[i++] = ch;
        }else{
          estado = falhar();
        }
      break;
      case 36:
        string[i] = '\0';
        tabela_token(string, "CHAVE");
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 40:
        if (ch == '[' || ch == ']') {
          estado = 41;
          string[i++] = ch;
        }else {
          estado = falhar();
        }
      break;
      case 41:
        string[i] = '\0';
        tabela_token(string, "COLCHETE");
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
      case 45:
        if (ch == '*') {
          string[i++] = ch;
          estado = 46;
        }else{
          estado = falhar();
        }
      break;
      case 46:
        string[i] = '\0';
        tabela_token(string, "MULTIPLICATIVO");
        i = 0;
        strcpy(string, "");
        estado = falhar();
      break;
    }

  }
  fclose(arquivo);
 
}
