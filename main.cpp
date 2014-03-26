#include <iostream>
#include <fstream>
#include <cstdlib>
#include <netinet/in.h>
#include "time.h"
#include "cache.h"

using namespace std;
void help();
int main(int argc, char **argv)
{
    Cache *cache;
    FILE *arq;
    int i=0;
    srand(time(NULL));
    unsigned int endereco;
    
    if(argc == 1) //nao ha argumentos
    {
        help();
    }
    if(argc != 3) //Cache default
    {
            cache = new Cache();
			arq = fopen(argv[1],"rb");
			if(arq == NULL)
			{
				cout << "Erro ao abrir" << argv[1] << endl;
				exit(-1);
			}
    }
    else
    {
			int nsets,bsize,assoc;
			
			sscanf(argv[1],"%d:%d:%d",&nsets,&bsize,&assoc);
            cache = new Cache(nsets,bsize,assoc);
            arq = fopen(argv[2],"rb");
    }
    if(arq == NULL)
    {
        cout << "Erro ao abrir arquivo: " << argv[2] << endl;
        exit(-1);
    }
   
   fread(&endereco,sizeof(int),1,arq);
    while(!feof(arq))
    {
		endereco = htonl(endereco);
        cache->instrucao(endereco);
        fread(&endereco,sizeof(int),1,arq);
    }
    
    cache->show();

    fclose(arq);
    return 1;
}

void help()
{
		cout << endl;
		cout << "Simulador de Cache" << endl << endl;
        cout << "Linguagem utilizada: C++" << endl;
        cout << "Instrucoes de uso:" << endl << endl;
        cout << "   Configuracao padrao" << endl;
        cout << "       ./cache <arquivo_de_entrada_binario>" << endl;
        cout << "       Neste modo <nsets> = 1024, <bsize> = 4, <assoc> = 1"<< endl << endl;
        cout << "   Configuracao personalizada" << endl;
        cout << "       ./cache <nsets>:<bsize>:<assoc> <arquivo_de_binario>" << endl << endl;

        exit(0);
}
