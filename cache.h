#ifndef CACHE_H_

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "estado.h"

using namespace std;
class Bloco
{
private:
    int validade;
    int tag;
public:
    Bloco();
    ~Bloco();
    int consulta(int tag);
    void buscaMem(int tag);
};

class Cache
{
private:
    int assoc;
    int nsets;
    int bsize;
    int associativa;
    Bloco ** sets;
    Estado estado;
public:
    Cache();
    ~Cache();
    Cache(int nsets, int bsize, int assoc);
    void instrucao(int endereco);
    void show();
};

#endif /*CACHE_H_*/