#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;
/*
A id�ia � verificar as subsequencias poss�veis, na for�a bruta mesmo. Ent�o, se
voc� tem a string 1 2 3 1 2 3 1 4, salve os indices em que 1 aparece ( a mesma coisa com 2 e
3 obviamente ) e verifique se os n�meros s�o iguais entre esses indices. Pegando o 
exemplo do 1, verifique a substring [ 0, 3 ] [ 0, 6 ] [ 3, 6 ]. Analogamente com os demais.
( verificar a substring [ 0, 3 ], por exemplo, significa ver se os numeros de 0 � 2
s�o iguais aos numeros de 3 � 5 ). Mas se voc� n�o for cuidadoso no c�digo, 2 coisas
aumentar�o seu tempo ( at� o TLE ):
1) voc� verificar� um intervalo, mas o descartar�. Solu��o: coloque os intervalos
em um heap, ordenando-os com as prioridades do problema. Assim cada intervalo s� ser�
visitado uma vez.
2) voc� verificar� intervalos que n�o cabem na sequencia. Isso quer dizer que, no pior
caso, voc� ir� comparar os numeros dos intervalos at� descobrir que precisaria ter mais 
n�meros para comparar. Solu��o: antes de sair comparando os n�meros, verifique se o 
intervalo � poss�vel dentro da sequencia.

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
		
		/*(2 * temp.j - temp.i <= qtd) verifica se o intervalo em quest�o 
			cabe na sequencia dada. Isto �, voc� pegou os limites do intervalo x,
			mas ele s� faz sentido se existir o intervalo 2x ( e 2x pode n�o
			caber na sequencia). Sem isso d� TLE.
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

