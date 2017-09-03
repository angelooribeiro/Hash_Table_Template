#include "hash_table.h"

template<class T1, class T2>
hash_table<T1, T2>::hash_table()
{}

//recebe o codigo
//retorna o valor de hashing
template<class T1, class T2>
T1 hash_table<T1, T2>::funcao_hash(T1 codigo)
{
    return ( ( (codigo/1000) * (codigo%10) ) + (codigo%10) );
}

template<class T1, class T2>
T1 hash_table<T1, T2>::funcao_hash2(T1 codigo)
{
    return ( ( (codigo/1000) * (codigo%10) ) + (codigo%10) + 3);
}

//recebe uma estrutura Dados
//coloca na respectiva posição da tabela
template<class T1, class T2>
void hash_table<T1, T2>::inserir_elemento(T1 codigo, T2 concelho)
{
    int indice = funcao_hash(codigo);      //determina o indice do array

    if( !tabela[indice].empty() )
        indice = funcao_hash2(codigo);

    typename list <Dados> :: iterator it = tabela[indice].begin(); //iterador para procurar o elemento
    while(it->codigo != codigo && it != tabela[indice].end() )  //enquanto nao econtrar ou nao chegar ao ultimo elemento
        it++;                                       //incrementa o iterator
    //insere
    Dados date;
    date.codigo = codigo;
    date.concelho = concelho;

    tabela[indice].emplace_back(date);         //coloca na primeira posição da lista da posição do array
    gere_indices(indice, 1);                   //atualiza os dados da tabela

    if(it != tabela[indice].end() )  //se o elemento for repetido
    {
        tabela->erase(it);     //elimina o elemento repetido
        gere_indices(indice, 2);        //atualiza os indices apos a remoção
    }
}

//recebe o codigo a procurar
//retorna um apontador para a estrutura encontrada
//retorna uma estrutura vazia se nao encontrado
template<class T1, class T2>
T2 hash_table<T1, T2>::procurar_elemento(T1 codigo)
{
    string concelho;
    int indice = funcao_hash(codigo);       //determina em que indice da tabela se econtra o elemento a procurar
    typename list <Dados> :: iterator it = tabela[indice].begin(); //iterador para procurar o elemento
    while(it->codigo != codigo && it != tabela[indice].end() )  //enquanto nao econtrar ou nao chegar ao ultimo elemento
        it++;                                       //incrementa o iterator

    if ( it == tabela[indice].end() )                //se nao encontrou
        return concelho;                                    //retorna uma estrutura default

    else
        return it->concelho;//se encontrou retorna a estrutura
}

//recebe o codigo do elemento a remover
//retorna true se removeu
//false se nao removeu
template<class T1, class T2>
bool hash_table<T1, T2>::remover_elemento(T1 codigo)
{
    int indice = funcao_hash(codigo);       //determina em que indice da tabela se econtra o elemento a procurar
    typename list <Dados> :: iterator it = tabela[indice].begin(); //iterador para procurar o elemento
    while(it->codigo != codigo && it != tabela[indice].end() )  //enquanto nao chegar ao fim da lista
        it++;               //incrementa o iterator para o prox elemento
    if (it == tabela[indice].end() )          //se nao encontrou
        return false;
    else
    {
        tabela->erase(it);     //elimina o elemento na posição
        gere_indices(indice, 2);        //atualiza os indices apos a remoção
        return true;
    }
}
template<class T1, class T2>
//recebe o indice da tabela de hash, e a indicação se se trata de uma operação de remoção ou inserção
//altera os valores globais das estatisticas da tabela
// max_colisoes, media_colisoes, elementos
void hash_table<T1, T2>::gere_indices(T1 indice, char a)
{
    if(a == 1)      //se é operação de inserção
    {
        int colisoes = tabela[indice].size();       //numero de elementos neste indice
        if(colisoes > 1)                            // se existir colisoes neste indice
            num_colisoes++;                         //incrementa o numero de colisoes de toda a tabela
        if( colisoes > max_colisoes )                 //se o numero de colisoes atual, maior que o ultimo maximo
            max_colisoes = (colisoes-1);                //maximo atualizado
        num_elementos++;                            //incrementa o numero de elementos inseridos
        media_colisoes = ( ((float)num_colisoes / (float)num_elementos) *100);  // atualiza a media de colisoes
    }

    else if(a == 2)     //se é operação de remoção
        {
            int colisoes = 0;
            for(int i = 0; i < SIZE; i++)       //apos a remoção determina o numero maximo de colisoes num dos indices da tabela
            {
                int aux_colisoes = tabela[i].size();
                if(aux_colisoes > colisoes)
                    colisoes = aux_colisoes;
            }
            if( (colisoes-1) < max_colisoes)                 //se o numero de colisoes atual, for menor que o ultimo maximo
                max_colisoes = (colisoes-1);                //maximo atualizado

            colisoes = tabela[indice].size();           //numero de elementos neste indice
            if(colisoes > 1)                            // se existir colisoes neste indice
                num_colisoes--;                         //decrementa o numero de colisoes de toda a tabela
            num_elementos--;                            //decrementa o numero de elementos
            media_colisoes = ( ((float)num_colisoes / (float)num_elementos) * 100 );  // atualiza a media de colisoes
        }
}

template<class T1, class T2>
Estatistica hash_table<T1, T2>::estatisticas()
{
    struct Estatistica est;
    est.max_colisoes=max_colisoes;
    est.media_colisoes=media_colisoes;
    est.num_colisoes=num_colisoes;
    est.num_elementos=num_elementos;

    return est;
}

//nao recebe nada
//percorre toda a tabela imprimindo os valores constantes
template<class T1, class T2>
void hash_table<T1, T2>::imprimir_tabela()
{
    for( int i = 0; i < SIZE; i++)
    {
        if( !tabela[i].empty() )        //se esta linha estiver vazia
        {
             for (typename list<Dados>::iterator it=tabela[i].begin() ; it != tabela[i].end(); ++it)     //percorre a lista
                cout << it->codigo << " " << it->concelho << endl;     //imprme o elemento
        }
    }
}

template<class T1, class T2>
hash_table<T1, T2>::~hash_table() {}
