#include "estado.h"

Estado::Estado()
{
    acesso = 0;
    hit = 0;
    missCompulsorio = 0;
    missCapacidade = 0;
    missConflito = 0;
}

void Estado::incMiss(int tipo)
{
    switch(tipo)
    {
            case 0:
            {
                missCompulsorio++;
                break;
            }
            case 1:
            {
                missCapacidade++;
                break;
            }
            case 2:
            {
                missConflito++;
				break;
            }
    }
}

void Estado::incHit()
{
	hit++;
}

void Estado::incAcesso()
{
	acesso++;
}

void Estado::show()
{
    int largura = 20;
    cout << setw(largura) <<"Acessos: "           << acesso << endl;
    cout << setw(largura) <<"Hits: "              << hit << endl;
    cout << setw(largura) <<"Hit rate: "          << setprecision(5)<< ( (float) hit/acesso)*100 << "%" << endl;
    cout << setw(largura) <<"Misses: "            << missCompulsorio + missCapacidade + missConflito << endl;
    cout << setw(largura) <<"Miss rate: "         << setprecision(5) << ((float) (missCompulsorio + missCapacidade + missConflito)/acesso)*100 << "%" << endl;
    cout << setw(largura) <<"Miss Compulsório: "  << missCompulsorio << endl;
    cout << setw(largura) <<"Miss Conflito: "     << missConflito << endl;
    cout << setw(largura) <<"Miss Capacidade: "   << missCapacidade << endl;
}
