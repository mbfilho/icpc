#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;


struct No{
	int adj[ 2 ];
	int label;
}t1[ 1000 ], t2[ 1000 ];

int l1[ 1000 ], l2[ 1000 ];

int cont, prt;
int montar( No* tree, int* lista ){
	int ind = cont++;
	//printf( "(%d %d)\n", cont, prt );
	
	if( lista[ prt ] == -1 ){
		tree[ ind ].label = -1;
		--prt;
	}else{
		tree[ ind ].label = lista[ prt ];
		--prt;
		tree[ ind ].adj[ 0 ] = montar( tree, lista );
		tree[ ind ].adj[ 1 ] = montar( tree, lista );
	}	
	
	return ind;
}

bool comp( int a, int b ){
	if( t1[ a ].label == -1 || t2[ b ].label == -1 )
		return ( t1[ a ].label == t2[ b ].label );
	
	if( t1[ a ].label != t2[ b ].label )
		return false;
		
	bool aux = ( comp( t1[ a ].adj[ 1 ], t2[ b ].adj[ 1 ] ) && comp( t1[ a ].adj[ 0 ], t2[ b ].adj[ 0 ] ) );
	aux = aux || ( comp( t1[ a ].adj[ 1 ], t2[ b ].adj[ 0 ] ) && comp( t1[ a ].adj[ 0 ], t2[ b ].adj[ 1 ] ) );
	
	return aux;
}

int main(){
	char buf[ 80 ];
	int casos = 0;
	
	//Sem essa conversão 'manual' de string -> int, dá wrong answer!!!!
	string str;
	getline( cin, str );
	int size = str.size();
	
	//Tem uma string na frente do numero!
	int k = 0;
	while( str[ k ] < '0' || str[ k ] > '9' ) ++k;
	
	for( ; k < size; ++k )
		casos = casos * 10 + str[ k ] - '0';
		
	while( casos-- ){
		int prt1 = 0, prt2 = 0;
		while( scanf( "%s", buf ) && strcmp( buf, "end" ) ){
			if( strcmp( buf, "nil" ) == 0 )
				l1[ prt1++ ] = -1;
			else
				l1[ prt1++ ] = buf[ 0 ] - 'A';
		}
		
		while( scanf( "%s", buf ) && strcmp( buf, "end" ) ){
			if( strcmp( buf, "nil" ) == 0 )
				l2[ prt2++ ] = -1;
			else
				l2[ prt2++ ] = buf[ 0 ] - 'A';
		}
		
		cont = 0;
		prt = prt1 - 1;
		montar( t1, l1 );
		
		cont = 0;
		prt = prt2 - 1;
		montar( t2, l2 );
	
		if( comp( 0, 0 ) ){
			printf( "true\n" );
		}else{
			printf( "false\n" );
		}
		
	}
}

