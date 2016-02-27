#include <cstdio>

/*
	A dificuldade do problema é a restrição de que a quantidade de moedas v[i] >= v[j]
para todo j > i. Dá para arrumar as coisas de modo que o problema seja reduzido a 
uma troca de moedas "normal"? Sim, basta perceber o seguinte: toda vez que eu utilizo
a moeda v[2], eu devo utilizar uma moeda v[1], assim, na verdade eu não tenho uma
moeda v[2], e sim uma moeda de valor v[2] + v[1]. Não tenho moeda v[3], e sim moeda
v[1] + v[2] + v[3] e assim por diante... Feito isso, basta resolver o coin change
normal.
*/

bool valor[ 100001 ];
int moedas[ 5 ], contM, val;

void resolver(){
	valor[ 0 ] = true;
	
	for( int i = 0; i < contM; ++i ){
		for( int j = moedas[ i ]; j <= val; ++j ){
			if( valor[ j - moedas[ i ] ] ){
				valor[ j ] = true;
				if( j == val )
					return;
			}
		}
	}
}

int main(){
	int casos;
	
	scanf( "%d", &casos );
		
	for( int u = 1; u <= casos; ++u ){
		scanf( "%d %d", &val, &contM );
		
		scanf( "%d", moedas );
		
		for( int i = 1; i < contM; ++i ){
			scanf( "%d", moedas + i );
			moedas[ i ] += moedas[ i - 1 ];
		}
		
		for( int i = 1; i <= val; ++i )
			valor[ i ] = false;
			
		resolver();
		
		if( valor[ val ] )
			printf( "YES\n" );
		else
			printf( "NO\n" );
		
		if( u != casos )
			printf( "\n" );
			
	}

}
