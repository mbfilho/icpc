//#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int n, dim;

class Box{
public:
	int d[ 10 ];
	int id;
	
	bool operator<( const Box& a ) const{

		for( int i = 0; i < dim; ++i ){
			if( d[ i ] >= a.d[ i ] )
				return false;
		}
		
		return true;
	}
}caixas[ 100 ];

int pai[ 100 ], tamanho[ 100 ];
int tam, last;

void seq(){
	tam = 1, last = 0;
	
	fill( tamanho, tamanho + n, 1 );
	for( int i = 0; i < n; ++i )
		pai[ i ] = i;
	
	for( int i = 1; i < n; ++i ){
		for( int j = 0; j < n; ++j ){
			if( i == j )
				continue;
			if( caixas[ j ] < caixas[ i ] && tamanho[ j ] + 1 > tamanho[ i ] ){
				pai[ i ] = j;
				tamanho[ i ] = tamanho[ j ] + 1;
				
				if( tamanho[ i ] > tam ){
					tam = tamanho[ i ];
					last = i;
				}
			}
		}
	}
}

/*Ordena lexicograficamente*/
bool lex( const Box& a, const Box& b ){
	for( int i = 0; i < dim; ++i ){
		if( a.d[ i ] < b.d[ i ] )
			return true;
		else if( a.d[ i ] > b.d[ i ] )
			return false;
	}
}

void reconstruir( int i ){
	if( pai[ i ] == i ){
		printf( "%d", caixas[ i ].id );
		//cout << caixas[ i ].id;
	}else{
		reconstruir( pai[ i ] );
		printf( " %d", caixas[ i ].id );
		//cout << " " << caixas[ i ].id;
	}
}

int main(){

	//while( cin >> n >> dim ){
	while( scanf( "%d %d", &n, &dim ) != EOF ){
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < dim; ++j )
				scanf( "%d", caixas[ i ].d + j );
				//cin >> caixas[ i ].d[ j ];
			caixas[ i ].id = i + 1;
			sort( caixas[ i ].d, caixas[ i ].d + dim );
		}
		
		sort( caixas, caixas + n, lex );
		
		/*
		for( int i = 0; i < n; ++i ){
			cout << "Caixa: " << caixas[ i ].id << endl;
			for( int j = 0; j < dim; ++j )
				cout << caixas[ i ].d[ j ] << " ";
			cout << endl;
		}
		*/
		
		seq();
		
		/*
		cout << "Teste: ";
		reconstruir( 6 );
		cout << endl;
		*/
		
		printf( "%d\n", tam );
		//cout << tam << endl;
		reconstruir( last );
		printf( "\n" );
		//cout << endl;
	}
}





