#include <cstdio>
#include <list>
using namespace std;

int pilha[ 10001 ];
int sp;
class No{
	public:
	bool marcado;
	list<int> adjs;
	No(){
		marcado = false;
	}
};

int busca( No* array ){

    list<int>::iterator i;
	int retorno = 0;

	while( sp ){
		--sp;
		No& temp = array[ pilha[ sp ] ];
		if( temp.marcado == false ){
			++retorno;
			temp.marcado = true;

			for( i = temp.adjs.begin(); i != temp.adjs.end(); ++i ){
				pilha[ sp ] = *i;
				++sp;
			}

		}

	}

	return retorno;
}

int main(){
	int l, m, n, vezes;
	int temp, temp1;

	scanf( "%d", &vezes );

	while( vezes-- ){
		scanf( "%d %d %d", &n, &m, &l );
		No array[ 10001 ];
		
		for( int i = 0; i < m; ++i ){
			scanf( "%d %d", &temp, &temp1 );
			array[ temp ].adjs.push_back( temp1 );
		}

		int soma = 0;
		for( int i = 0; i < l; ++i ){
			scanf( "%d", &temp );
			pilha[ 0 ] = temp;
			sp = 1;
			soma += busca( array );
		}

		printf( "%d\n", soma );
	}

}
