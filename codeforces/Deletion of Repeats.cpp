#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;
/*
A idéia é verificar as subsequencias possíveis, na força bruta mesmo. Então, se
você tem a string 1 2 3 1 2 3 1 4, salve os indices em que 1 aparece ( a mesma coisa com 2 e
3 obviamente ) e verifique se os números são iguais entre esses indices. Pegando o 
exemplo do 1, verifique a substring [ 0, 3 ] [ 0, 6 ] [ 3, 6 ]. Analogamente com os demais.
( verificar a substring [ 0, 3 ], por exemplo, significa ver se os numeros de 0 à 2
são iguais aos numeros de 3 à 5 ). Mas se você não for cuidadoso no código, 2 coisas
aumentarão seu tempo ( até o TLE ):
1) você verificará um intervalo, mas o descartará. Solução: coloque os intervalos
em um heap, ordenando-os com as prioridades do problema. Assim cada intervalo só será
visitado uma vez.
2) você verificará intervalos que não cabem na sequencia. Isso quer dizer que, no pior
caso, você irá comparar os numeros dos intervalos até descobrir que precisaria ter mais 
números para comparar. Solução: antes de sair comparando os números, verifique se o 
intervalo é possível dentro da sequencia.

*/

class Dupla{
public:
	int i, j;
	
	Dupla( int a, int b ){
		i = a;
		j = b;
	}
		
	Dupla(){}
	
	bool operator<( const Dupla& d ) const{
		bool menor;
		
		if( i - j < d.i - d.j )
			menor = true;
		else if( i - j > d.i - d.j )
			menor = false;
		else
			menor = ( i < d.i );
			
		return !menor;
	}
};

int qtd, down;
int seq[ 100000 ];
map<int,vector<int> > mapa;
priority_queue<Dupla> heap;

void carregar(){
	scanf( "%d", &qtd );
	
	for( int i = 0; i < qtd; ++i ){
		scanf( "%d", &seq[ i ] );
		mapa[ seq[ i ] ].push_back( i );
	}		
}

typedef vector<int>::iterator Iterator;
void encherHeap(){
	
	map<int,vector<int> >::iterator its;
	
	for( its = mapa.begin(); its != mapa.end(); ++its ){
		for( Iterator it = (its -> second).begin(); it != (its -> second ).end(); ++it ){
			for( Iterator it2 = (its -> second).begin(); it2 != (its -> second).end(); ++it2 ){
				if( *it < *it2 )
					heap.push( Dupla( *it, *it2 ) );
			}
		}
	}
}

void responder(){
	down = 0;
	bool muda;
	Dupla temp;
	
	while( heap.size() ){
		temp = heap.top();
		heap.pop();
		muda = true;
		
		/*(2 * temp.j - temp.i <= qtd) verifica se o intervalo em questão 
			cabe na sequencia dada. Isto é, você pegou os limites do intervalo x,
			mas ele só faz sentido se existir o intervalo 2x ( e 2x pode não
			caber na sequencia). Sem isso dá TLE.
		*/
		if( temp.i >= down && 2 * temp.j - temp.i <= qtd ){
			int tam = temp.j - temp.i;
			for( int i = temp.i; muda && i < temp.j; ++i ){
				if( seq[ i ] != seq[ i + tam ] )
					muda = false;
			}
			
			if( muda )
				down = temp.j;
		}
	}
}

int main(){
	carregar();
	encherHeap();
	responder();
	
	printf( "%d\n", ( qtd - down ) );
	for( int i = down; i < qtd; ++i )
		printf( "%d%c", seq[ i ], (i == (qtd - 1)) ? '\n' : ' ' );
	
}

