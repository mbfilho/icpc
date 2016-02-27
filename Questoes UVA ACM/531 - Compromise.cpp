#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
using namespace std;
#define N 110

const int lado = 0, cima = 1, diag = 2;

int pd[ N ][ N ], rec[ N ][ N ];
int seq1[ N ], seq2[ N ];
int n1, n2;
map<string,int> mapa;
string rev[ N ];

void faz(){
	memset( rec, -1, sizeof( rec ) );
	
	for( int i = 0; i <= n1; ++i )
		pd[ i ][ 0 ] = 0;
	for( int j = 0; j <= n2; ++j )
		pd[ 0 ][ j ] = 0;
	
	for( int i = 1; i <= n1; ++i ){
		for( int j = 1; j <= n2; ++j ){
			int acao = cima;
			pd[ i ][ j ] = pd[ i - 1 ][ j ];
			
			if( pd[ i - 1 ][ j ] < pd[ i ][ j - 1 ] ){
				pd[ i ][ j ] = pd[ i ][ j - 1 ];
				acao = lado;
			} 
			
			if( seq1[ i - 1 ] == seq2[ j - 1 ] ){
				if( pd[ i - 1 ][ j - 1 ] + 1 > pd[ i ][ j ] ){
					acao = diag;
					pd[ i ][ j ] = pd[ i - 1 ][ j - 1 ] + 1;
				} 
			} 
			
			rec[ i ][ j ] = acao;
		}
	} 
}

int lista[ N ], prt;

void reconstroi( int i, int j ){
	if( rec[ i ][ j ] == -1 )
		return;
	
	if( rec[ i ][ j ] == cima )
		reconstroi( i - 1, j );
	else if( rec[ i ][ j ] == lado )
		reconstroi( i, j - 1 );
	else{
		reconstroi( i - 1, j - 1 );
		lista[ prt++ ] = seq1[ i - 1 ];
	}
		
}

int main(){
	char buff[ 1000 ];
	int cont;
	
	while( scanf( "%s", buff ) != EOF ){
		mapa.clear();
		n1 = n2 = cont = 0;
		
		mapa[ buff ] = cont;
		rev[ cont ] = buff;
		seq1[ n1++ ] = cont++;
		
		while( scanf( "%s", buff ) && buff[ 0 ] != '#' ){
			int p;
			if( mapa.find( buff ) == mapa.end() ){
				mapa[ buff ] = cont;
				rev[ cont ] = buff;
				p = cont++;
			}else
				p = mapa[ buff ];
			
			seq1[ n1++ ] = p;
		}
		
		
		while( scanf( "%s", buff ) && buff[ 0 ] != '#' ){
			int p;
			
			if( mapa.find( buff ) == mapa.end() ){
				mapa[ buff ] = cont;
				rev[ cont ] = buff;
				p = cont++;
			}else
				p = mapa[ buff ];
			
			seq2[ n2++ ] = p;
		}
		
		faz();
		prt = 0;
		reconstroi( n1, n2 );
		
		for( int i = 0; i < prt; ++i ){
			printf( "%s%c", rev[ lista[i] ].c_str(), ( i == prt -1 )? '\n': ' ' );
		}
	}
}


