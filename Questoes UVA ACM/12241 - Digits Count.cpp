#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> operator+( const vector<int>& a, const vector<int>& b ){
	vector<int> resp;
	for( int i = 0; i < 10; ++i )
		resp.push_back( a[ i ] + b [ i ] );
	return resp;
}

vector<int> operator*( int c, const vector<int>& a ){
	vector<int> resp;
	for( int i = 0; i < 10; ++i )
		resp.push_back( a[ i ] * c );
	return resp;
}

vector<int> zero;

vector<int> livre[ 10 ], livres0[ 10 ];
int pot[ 10 ];

//Precalcula: as quantidades para uma quantidade de dígitos (livre) e essa mesma quantidade sem leadings zeros (livres0)
void pre(){
	for( int i = 0; i < 10; ++i ){
		livre[ i ].clear();
		livres0[ i ].clear();
	}
		
	for( int i = 0; i < 10; ++i ){
		livre[ 1 ].push_back( 1 );
		livres0[ 1 ].push_back( 1 );
	}
	
	vector<int> qtd, qtd2;
	for( int i = 0; i < 10; ++i ){
		qtd.push_back( 10 );
		if( i )
			qtd2.push_back( 10 );
		else
			qtd2.push_back( 0 );
	}
		
	for( int i = 2; i < 10; ++i ){
		livre[ i ] = 10 * livre[ i - 1 ] + qtd;
		livres0[ i ] = 9 * livre[ i - 1 ] + qtd2;
		qtd = 10 * qtd;
		qtd2 = 10 * qtd2;
	}
	for( int i = 0; i < 10; ++i )
		zero.push_back( 0 );
	pot[ 0 ] = 1;
	for( int i = 1; i < 10; ++i )
		pot[ i ] = 10 * pot[ i - 1 ];
}

//Calcula a resposta do intervalo fechado 0..arg
vector<int> faz( char arg[20], int size, int at ){
	if( at == size - 1 ){
		vector<int> resp;
		for( int i = '0'; i <= arg[ at ]; ++i )
			resp.push_back( 1 );
		for( int i = arg[ at ] + 1; i <= '9'; ++i )
			resp.push_back( 0 );
		return resp;
	}
	
	//qtd é o digito atual
	int qtd = arg[ at ] - '0', resto = 0;
	int ind = at + 1;
	while( arg[ ind ] == '0' ) ++ind;
	while( arg[ ind ] ){
		resto = resto * 10 + arg[ ind ] - '0';
		++ind;
	}
	
	vector<int> resp, rec = faz( arg, size, at + 1 );
	int tam = size - at;

	if( at == 0 ){//primeiro cara toma cuidados com leadings zeros
		resp = ( qtd - 1 ) * livre[ tam - 1 ] + rec; //coloca um numero diferente de zero na frente e o resto ta livre
		
		for( int i = 1; i < tam; ++i )//Coloca o zero na frente e o resto não deve ter leading zeros
			resp = resp + livres0[ i ];
	}else//Se não for o primeiro cara, todas as posições estão livres
		resp = qtd * livre[ tam - 1 ] + rec;

	//Incrementa a quantidade de vezes que os digitos que eu coloquei aparecem. Toma cuidado para nao colocar leading zero
	for( int i = ( at == 0 ? 1 : 0 ); i < qtd; ++i )
		resp[ i ] += pot[ tam - 1 ];

	//Atualiza a quantidade de vezes que o digito atual aparece ( inclusive o zero ) 
	resp[ qtd ] += resto + 1;

	return resp;
}

char temp[ 20 ];

int main(){
	int aa, bb;
	pre();
	
	while( scanf( "%d%d", &aa, &bb ) != EOF && ( aa | bb ) ){
		sprintf( temp, "%d", bb );
		vector<int> resp = faz( temp, strlen( temp ), 0 );
		
		sprintf( temp, "%d", aa - 1 );
		vector<int> x = faz( temp, strlen( temp ), 0 );
		for( int i = 0; i < 10; ++i )
			resp[ i ] -= x[ i ];
		
		for( int i = 0; i < 10; ++i ){
			printf( "%d", resp[ i ] );
			if( i != 9 ) printf( " " );
			else printf( "\n" ); 
		}
	}
}


