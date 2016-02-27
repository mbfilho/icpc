#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <string>
#include <map>
#include <vector>
using namespace std;
#define BASE 43
typedef unsigned long long ull;

set<ull> dicionario;
map<string,int> mapa;
char temp[ 50 ];

ull getHash( char *a ){
	ull h = 0;
	
	while( *a ){
		h = h * BASE + *a;
		++a;
	}
	
	return h;
}

char aux[ 100 ];
void insert( char* word, set<string>& resp ){
	for( int ch = 'a'; ch <= 'z'; ++ch ){
		int tam = strlen( word ) + 2;
		for( int pos = 0; pos < tam - 1; ++pos ){
			int prt = 0;
			for( int i = 0; i <= tam; ++i ){
				if( i == pos )
					aux[ i ] = ch;
				else
					aux[ i ] = word[ prt++ ];
			}
			aux[ tam + 1 ] = 0;
			if( dicionario.find( getHash( aux ) ) != dicionario.end() )
				resp.insert( string( aux ) );
		}
	}
		
}

void deletar( char* word, set<string>& resp ){
	int tam = strlen( word );
	
	for( int i = 0; i < tam; ++i ){
		int prt = 0;
		for( int j = 0; j < tam; ++j ){
			if( i != j )
				aux[ prt++ ] = word[ j ];
		}
		aux[ prt ] = 0;
		// printf( "%s\n", aux );
		if( dicionario.find( getHash( aux ) ) != dicionario.end() )
			resp.insert( aux );
	}
}

void replace( char* word, set<string>& resp ){
	for( char ch = 'a'; ch <= 'z'; ++ch ){
		for( int pos = 0; word[ pos ]; ++pos ){
			for( int i = 0; word[ i ]; ++i ){
				if( i == pos )
					aux[ i ] = ch;
				else
					aux[ i ] = word[ i ];
				aux[ i + 1 ] = 0;
			}
			
			if( dicionario.find( getHash( aux ) ) != dicionario.end() )
				resp.insert( aux );
		}
	}
}

bool cmp( const string& a, const string& b ){
	return mapa[ a ] < mapa[ b ];
}

int main(){
	dicionario.clear();
	int cont = 0;
	while( scanf( "%s", temp ) && strcmp( temp, "#" ) ){
		dicionario.insert( getHash( temp ) );
		mapa[ temp ] = cont++;
	}
//	printf( ">>> %d\n", dicionario.find( getHash( "av" ) ) == dicionario.end() );	
	
	set<string> resp;
	while( scanf( "%s", temp ) && strcmp( temp, "#" ) ){
		ull h = getHash( temp );
		resp.clear();
		
		if( dicionario.find( h ) != dicionario.end() )
			printf( "%s is correct\n", temp );
		else{
			insert( temp, resp );
			deletar( temp, resp );
			replace( temp, resp );
			vector<string> impr( resp.begin(), resp.end() );
			sort( impr.begin(), impr.end(), cmp );
			printf( "%s:", temp );
			
			for( int i = 0; i < impr.size(); ++i )
				printf( " %s", impr[ i ].c_str() );
			printf( "\n" );
		}
	}
	
	
}



