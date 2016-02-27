#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <iostream>
using namespace std;
typedef long long ll;

#define MAX 510

class No{
public:
	vector<int> adj;
	int ind, size;
	bool marcado;
}nos[ MAX ];

ll cap[ MAX ][ MAX ], flux[ MAX ][ MAX ];
int pilha[ MAX ], cont;
map<string,int> mapa;
map<string,int>::iterator ite;

//supersource, supersink
const int ss = 0, st = 1;

int res( int a, int b ){
	return cap[ a ][ b ] - flux[ a ][ b ];
}

bool dfs(){
	for( int i = 0; i <= cont + 1; ++i ){
		nos[ i ].marcado = false;
		nos[ i ].ind = 0;
	}
	int sp = 1, atual = ss, adj, residual;
	pilha[ 0 ] = ss;
	
	while( sp != 0 ){
		atual = pilha[ sp - 1 ];
		if( atual == st )
			break;
		nos[ atual ].marcado = true;

		if( nos[ atual ].ind == nos[ atual ].size ){
			--sp;
			continue;
		}

		for( int* i = &nos[ atual ].ind; *i < nos[ atual ].size; ++(*i) ){
			adj = nos[ atual ].adj[ *i ];
			if( nos[ adj ].marcado == false ){
				residual = res( atual, adj );
				if( residual ){
					pilha[ sp++ ] = adj;
					break;
				}
			}
		}

	}
	
	if( sp == 0 )
		return false;
	
	int menor = 0x7fffffff;
	for( int i = 0; i < sp - 1; ++i ){
		residual = res( pilha[ i ], pilha[ i + 1 ] );
		if( residual < menor )
			menor = residual;
	}
	
	for( int i = 0; i < sp - 1; ++i ){		
		flux[ pilha[ i ] ][ pilha[ i + 1 ] ] += menor;
		flux[ pilha[ i + 1 ] ][ pilha[ i ] ] -= menor;
	}

	return true;
}

int main(){
	int tomadas, devices, adaptadores, casos;
	string buffer, buffer2;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		mapa.clear();
		for( int i = 0; i < MAX; ++i ){
			nos[ i ].adj.clear();
			nos[ i ].size = 0;
			for( int j = 0; j < MAX; ++j ){
				flux[ i ][ j ] = flux[ j ][ i ] = 0;
				cap[ i ][ j ] = cap[ j ][ i ] = 0;
			}
		}
		
		scanf( "%d", &tomadas );
		cont = 2; 
		for( int i = 0; i < tomadas; ++i ){
			cin >> buffer;
			if( (ite = mapa.find( buffer ) ) == mapa.end() ){
				nos[ cont ].adj.push_back( st );
				nos[ st ].adj.push_back( cont );
				++nos[ cont ].size;
				++nos[ st ].size;
				++cap[ cont ][ st ];
				mapa[ buffer ] = cont++;				
			}else
				++cap[ ite -> second ][ st ];		
			
		}
		
		cin >> devices;
		for( int i = 0; i < devices; ++i ){
			cin >> buffer >> buffer2;
			
			//Supersource
			nos[ ss ].adj.push_back( cont );
			nos[ cont ].adj.push_back( ss );
			++nos[ cont ].size;
			++nos[ ss ].size;
			cap[ ss ][ cont ] = 999999;
			
			if( ( ite = mapa.find( buffer2 ) ) == mapa.end() ){
				mapa[ buffer2 ] = cont + 1;
				nos[ cont ].adj.push_back( cont + 1 );
				nos[ cont + 1 ].adj.push_back( cont );
				++cap[ cont ][ cont + 1 ];
				++nos[ cont + 1 ].size;
				++nos[ cont ].size;
				cont += 2;
			}else{				
				nos[ cont ].adj.push_back( ite -> second );
				nos[ ite -> second ].adj.push_back( cont );
				++cap[ cont ][ ite -> second ];
				++nos[ ite -> second ].size;
				++nos[ cont ].size;
				++cont;
			}			

		}
		
		cin >> adaptadores;
		map<string,int>::iterator it;
		int a, b;
		for( int i = 0; i < adaptadores; ++i ){
			cin >> buffer >> buffer2;
			
			it = mapa.find( buffer );
			if( it == mapa.end() )
				a = mapa[ buffer ] = cont++;
			else
				a = it -> second;
			
				
			it = mapa.find( buffer2 );
			if( it == mapa.end() )
				b = mapa[ buffer2 ] = cont++;
			else
				b = it -> second;
				
			cap[ a ][ b ] = 999999;
				
			nos[ a ].adj.push_back( b );
			nos[ b ].adj.push_back( a );
			++nos[ b ].size;
			++nos[ a ].size;
		}
		

		while( dfs() );
		
		int resp = 0;
		for( int i = 0; i < nos[ ss ].size; ++i ){
			if( flux[ ss ][ nos[ ss ].adj[ i ] ] > 0 )
				resp += flux[ ss ][ nos[ ss ].adj[ i ] ];
		}
			
		printf( "%d\n", devices - resp );
		if( casos )
			printf( "\n" );
	}
}

