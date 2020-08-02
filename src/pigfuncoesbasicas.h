
#ifndef PIGFUNCOESBASICAS_H
#define PIGFUNCOESBASICAS_H

#include "tipos_pig.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <string.h>
#include <time.h>
#include <vector>
#include <map>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <iomanip>

//separa uma string em palavras, usando os delimitadores indicados
std::vector<std::string> PIGSeparaPalavras(std::string texto,std::string delim);

//verifica se uma string possui apenas digitos de 0 a 9
bool PIGSomenteNumeros(std::string frase);

//verifica se duas cores s�o iguais
bool PIGCoresIguais(PIG_Cor cor1, PIG_Cor cor2);

//cria uma cor a partir de uma string com um valor hexadecimal de 8 algarismos RRGGBBAA. Ex: 0xFF0000FF (vermelho)
PIG_Cor PIGCriaCor(char *stringHexa);

//multiplica as componentes RGB da cor pelo fator
PIG_Cor PIGMultiplicaCor(PIG_Cor cor, float valor);

//troca a posi��o dos bytes de uma word(16bits)
uint16_t PIGTroca2Bytes(uint16_t valor);

//retorna o diretorio onde est� o execut�vel
std::string PIGGetDiretorioAtual();

//retorna "valor" limitado entre [vMin, vMax]
int PIGLimitaValor(int valor, int minimo,int maximo);

//cria uma lista de strings contendo o nome do arquivos de um diret�rio
std::vector<std::string> PIGListaArquivosDiretorio(std::string path);

#endif // _PigFuncoesBasicas_
