#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <iostream>
#include <list>

#define SIZE 100

using namespace std;

    struct Estatistica
    {
        int max_colisoes;                          //numero maximo de colisoes
        int num_colisoes;                           //numero de colisoes
        float media_colisoes;                       //media de colisoes, em percentagem
        int num_elementos;                          //elementos inseridos
    };


//t1 chave, t2 dados
template<class T1, class T2>
class hash_table
{
    struct Dados
    {
        T1 codigo;
        T2 concelho;
    };

    list <Dados> tabela[SIZE];
    T1 funcao_hash(T1 codigo);              //determina o indice no array
    T1 funcao_hash2(T1 codigo);               //segunda função de hashing
    int max_colisoes = 0;                          //numero maximo de colisoes
    int num_colisoes = 0;                           //numero de colisoes
    float media_colisoes = 0.00;                       //media de colisoes, em percentagem
    int num_elementos = 0;                          //elementos inseridos

public:
    hash_table();                             //constructor
    void inserir_elemento(T1 codigo, T2 concelho);         //para inserir um novo elemento
    T2 procurar_elemento(T1 codigo);       //procura de um elemento
    bool remover_elemento(T1 codigo);        //remove um elemento
    void gere_indices(T1 indice, char a);    //atualiza as estatisticas da tabela
    Estatistica estatisticas();                //retorna uma estrutura com as estatisticas da tabela
    void imprimir_tabela();                   //função que imprime toda a tabela;
    ~hash_table();                            //destructor
};

#include "hash_table.cpp"

#endif
