#include <iostream>
using namespace std;

int lin = 0, m, numero;
int restricoes[ 20 ][ 3 ];
int a, b, c;
int cont;
class No{
	public:
		bool usada;
		int pos;
};

No nos[ 8 ];
	
void seq( No *nos, const int i ){
	if( i == numero ){
		int q = 0;
		
		for( int o = 0; o < m; ++o ){
			a = restricoes[ o ][ 0 ];
			b = restricoes[ o ][ 1 ];
			c = restricoes[ o ][ 2 ];
			
			if( c < 0 ){
				int dif = nos[ a ].pos - nos[ b ].pos;
				if( dif < 0 )
					dif = -dif;
				if( dif >= -c )
					++q;						
			}else{
				int dif = nos[ a ].pos - nos[ b ].pos;
				if( dif < 0 )
					dif = -dif;
				if( dif <= c )
					++q;
			}
		}
		
		if( q == m )
			++cont;
			
		++lin;
		return;
	}
	
	int j = 0;
	while( nos[ j ].usada )
		++j;
	
	int k = j;
	
	do{
		nos[ k ].usada = true;
		nos[ k ].pos = i;
		
		seq( nos, i + 1 );
		
		nos[ k ].usada = false;
		
		k = ( k + 1 ) % numero;
		while( nos[ k ].usada && k != j )
			k = ( k + 1 ) % numero;
			
	}while( k != j );
			
}

int fatorial( int l ){
	int retorno = 1;
	int y = l;
	while( y ){
		retorno = retorno * y;
		--y;
	}
	
	return retorno;
}

int main(){

	cin >> numero >> m;
	
	while( m | numero ){
		for( int i = 0; i < 8; ++i )
			nos[ i ].usada = false;
		
		if( m == 0 )
			cout << fatorial( numero ) << endl;
		else{
			for( int i = 0; i < m; ++i )
				cin >> restricoes[ i ][ 0 ] >> restricoes[ i ][ 1 ] >> restricoes[ i ][ 2 ];
			lin = 0;
			cont = 0;
			seq( nos, 0 );
			cout << cont << endl;
		}
		
		cin >> numero >> m;
	}

}
