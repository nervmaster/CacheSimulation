#ifndef ESTADO_H_
#define ESTADO_H_

#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

class Estado //Salva informacoes referentes aos hits e misses da cache
{
private:
    int acesso;
    int hit;
    int missCompulsorio;
    int missCapacidade;
    int missConflito;

public:
    Estado();
    void incAcesso();
    void incHit();
    void incMiss(int tipo);
    void show();
};

#endif /*ESTADO_H_*/
