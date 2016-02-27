#include <cstdio>
#include <algorithm>
using namespace std;

class Turtle{
public:
	int peso, forca;
	
	bool operator<( const Turtle& a ) const{
		if( forca < a.forca )
			return true;
		if( forca > a.forca )
			return false;
		
		return peso < a.peso;
	}
}tarts[ 5700 ];

int pilha[ 5700 ];
int len, qtd;

/*
Suponha de vc tenha uma pilha CBA, onde A � o topo. Vc est� processando a tartaruga D.
Se D tiver fo�a suficiente para sustentar CBA, ent�o crie a pilha DCBA, que tem peso
peso[ CBA ] + peso[ D ].A maior sequencia passa de 3 para 4. Mas suponha que D n�o
suporte CBA. Ent�o verifique se D suporta BA, como na resolu��o da lis convencional.
Se D suportar BA, vc s� criar� a pilha DBA se o peso[ DBA ] < peso[ CBA ]. O tamanho 
da maior sequencia, no entanto, permanece o mesmo.
� essa a recorrencia.
*/

int lis(){
	len = 0;
	pilha[ 0 ] = 0;
	for( int i = 1; i <= qtd; ++i )
		pilha[ i ] = 0x7FFFFFFF;
		
	for( int i = 0; i < qtd; ++i ){
		for( int j = len + 1; j > 0; --j ){
			if( tarts[i].forca - tarts[i].peso >= pilha[j - 1] && pilha[j - 1] + tarts[i].peso < pilha[j] ){
				pilha[ j ] = pilha[ j - 1 ] + tarts[ i ].peso;
			
				if( j > len )
					len = j;
			}
		}
	}
	
	return len;
}

int main(){
	qtd = 0;
	
	while( scanf( "%d %d", &tarts[ qtd ].peso, &tarts[ qtd ].forca ) != EOF )
		++qtd;
	
	sort( tarts, tarts + qtd );
	printf( "%d\n", lis() );
}
