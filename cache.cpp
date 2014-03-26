#include "cache.h"

/* METODOS DA CACHE */
Cache::Cache()
{
	//Valores default para cache
	associativa = 0;
	nsets = 1024;
	bsize = 4;
	assoc = 1;
	sets = new Bloco*[nsets];
        
	for(int i=0;i<nsets;i++)
	{
		sets[i] = new Bloco();
	}
}
Cache::~Cache()
{
    delete[] sets;
}
Cache::Cache(int nsets, int bsize, int assoc)
{
	this->associativa = 0;
	this->nsets = nsets;
	this->bsize = bsize;
	this->assoc = assoc;
	
	if( nsets == 1 && assoc > 1)
    {
		associativa = 1;
    }
    
	sets = new Bloco*[nsets*assoc]; //o array com os blocos da cache
        
	for(int i=0;i<nsets*assoc;i++)
	{
		sets[i] = new Bloco(); //inicializa os blocos
	}
}

void Cache::instrucao(int endereco)
{
	int indice,tag;
	int i=0,controle=0, last=0;
	int poslivre;

	estado.incAcesso(); //Um acesso a cache
	endereco = endereco/this->bsize; //ignora o offset
	if(assoc<nsets)
	{
		indice = endereco % (nsets/assoc); //indice recebe os bits de indice
	}
	else
	{
		indice = 0;
	}
	tag = endereco - indice;
	
	for(i=0; i<assoc;i++) //Consulta aos blocos
	{	
		controle += sets[indice + nsets*i]->consulta(tag);
		if(controle > last) //So verdadeiro quando recebeu um
		{
				controle = 1;
				break;
		}
		if(controle == -1)
		{
			poslivre = indice + nsets*i;
		}
		last = controle;
	}
	
	if(controle==1)
	{
		estado.incHit();
	}
	else //MISS
	{
		if(controle==0) //MISS Capacidade e conflito
		{
			i = indice + nsets * (rand()%assoc); //Posicao randomica
			if(associativa)
			{
				estado.incMiss(1);
			}
			else
			{
				estado.incMiss(2);
			}
		}
		else //Miss Compulsorio
		{
			i = poslivre; //Escreve na primeira posicao livre
			estado.incMiss(0);
		}
		sets[i]->buscaMem(tag); //Busca na mem
	}
}

void Cache::show()
{
    estado.show();
}
/* METODOS DO BLOCO */

Bloco::Bloco()
{
	validade = 0;
}

int Bloco::consulta(int tag)
{
	if(!validade) //Miss Compulsorio
	{
		return -1;
	}
	if(this->tag != tag) //Miss Conflito
	{
		return 0;
	}
	return 1;
}

void Bloco::buscaMem(int tag)
{
	this->validade = 1;
	this->tag = tag;
}
