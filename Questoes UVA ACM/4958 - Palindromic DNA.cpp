#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 11000

int mapa[ 300 ];

vector<int> nos[ N ];
vector<int> comps[ N ];
int qtd;
int mask[ N ];
int time[ 2 * N ], tempo;

char input[ N ];
int n;

void dfs( int no, vector<int>& comp, int& pat ){
	comp.push_back( no );
	pat |= ( 1 << mapa[ input[no] ] );
	
	time[ no ] = 1;
	
	for( int i = 0; i < nos[ no ].size(); ++i ){
		int nt = nos[ no ][ i ];
		if( !time[ nt ] )
			dfs( nt, comp, pat );
	}
}

//2SAT
vector<int> implic[ 2 * N ];
int componente[ 2 * N ];
int pilha[ 2 * N ], sp;
int cont;

int tarjan( int no ){
	int menor;
	menor = time[ no ] = tempo++;
	pilha[ sp++ ] = no;
	
	for( int i = implic[ no ].size() - 1; i >= 0; --i ){
		int nt = implic[ no ][ i ];
		if( componente[ nt ] != -1 ) continue;
		
		if( time[ nt ] != -1 ) menor = min( menor, time[ nt ] );
		else menor = min( menor, tarjan( nt ) );
	}
	
	if( menor == time[ no ] ){
		int tmp;
		do{
			tmp = pilha[ --sp ];
			componente[ tmp ] = cont;
		}while( tmp != no );
		++cont;
	}
	
	return menor;
}

int aux[ N ];
int main(){
	mapa[ 'A' ] = 0;
	mapa[ 'G' ] = 1;
	mapa[ 'T' ] = 2;
	mapa[ 'C' ] = 3;
	int t;
	
	while( scanf( "%d %d", &n, &t ) == 2 && ( n | t ) ){
		scanf( "%s", input );
		
		sp = cont = tempo = 0;
		for( int i = 0; i <= n; ++i ){
			mask[ i ] = 0;
			nos[ i ].clear();
			comps[ i ].clear();
			
			implic[ 2 * i ].clear();
			implic[ 2 * i + 1 ].clear();
			componente[ 2 * i ] = componente[ 2 * i + 1 ] = -1;
			
			
			time[ i ] = 0;
		}
		
		while( t-- ){
			int k;
			scanf( "%d%*s", &k );
			for( int i = 0; i < k; ++i ){
				scanf( "%d", aux + i );
			}
			
			for( int i = 0; i < k / 2; ++i ){
				nos[ aux[i] ].push_back( aux[ k - i - 1 ] );
				nos[ aux[k - i - 1] ].push_back( aux[i] );
//				printf( "(%d--%d)\n", aux[i], aux[k-i-1] );
			}
		}
		
		qtd = 0;
		for( int i = 0; i < n; ++i ){
			if( !time[ i ] && nos[i].size() ){
				dfs( i, comps[ qtd ], mask[ qtd ] );
				++qtd;
			}
		}
		
		memset( time, -1, sizeof time );
		//2sat
		
		//Nao deixe mudar posicoes adjacentes!
		for( int i = 0; i < n - 1; ++i ){
			int nt = i + 1;
			
			//si -> !si+1
			implic[ 2 * i ].push_back( 2 * nt + 1 );
			
			//si+1 -> !si
			implic[ 2 * nt ].push_back( 2 * i + 1 );
		}
		
		bool dm = false;
		
		for( int i = 0; i < qtd; ++i ){
			if( mask[ i ] == 15 ){
				dm = true;
				break;
			}
			
			//AG AC GT TC
			if( mask[ i ] == 3 || mask[ i ] == 9 || mask[ i ] == 6 || mask[ i ] == 12 ){
				int setar = mask[ i ] & ( -mask[ i ] );
				
				for( int j = 0; j < comps[i].size(); ++j ){
					int at = comps[i][j];
					int nt = comps[i][ ( j + 1 ) % comps[i].size() ];
					
					int pre, pos;
					if( ( 1 << mapa[ input[at] ] ) == setar ) pre = 2 * at;
					else pre = 2 * at + 1;
					
					if( ( 1 << mapa[ input[nt] ] ) == setar ) pos = 2 * nt;
					else pos = 2 * nt + 1;
					
					implic[ pre ].push_back( pos );
					
					implic[ pre ^ 1 ].push_back( pos ^ 1 );
				}
			
			// A  G  T  C
			}else if( mask[ i ] == 1 || mask[ i ] == 2 || mask[ i ] == 4 || mask[ i ] == 8 ){
				for( int j = 0; j < comps[i].size(); ++j ){
					int at = comps[i][j];
					int nt = comps[i][ ( j + 1 ) % comps[i].size() ];
					
					implic[ 2 * at ].push_back( 2 * nt );
				}
			
			//AGT
			}else if( mask[ i ] == 7 || mask[ i ] == 14 || mask[ i ] == 11 || mask[ i ] == 13 ){
				char meio = 'G';
				if( mask[ i ] == 14 ) meio = 'T';
				else if( mask[ i ] == 11 ) meio = 'A';
				else if( mask[ i ] == 13 ) meio = 'C';
				
				for( int j = 0; j < comps[i].size(); ++j ){
					int at = comps[i][j];
					if( input[ at ] == meio ) //!at
						implic[ 2 * at ].push_back( 2 * at + 1 );
					else
						implic[ 2 * at + 1 ].push_back( 2 * at );
				}
//				printf( "(%d/%d)>>> %d\n", i, qtd, mask[ i ] );
			//GC AT
			}else if( mask[ i ] == 10 || mask[ i ] == 5 ){
				for( int j = 0; j < comps[i].size(); ++j ){
					int at = comps[i][j];
					implic[ 2 * at + 1 ].push_back( 2 * at );
				}
				
			}else printf( "Faltou " );
		}
		
		for( int i = 0;!dm && i < n; ++i ){
			if( componente[ 2 * i ] == -1 ){
				sp = 0;
				tarjan( 2 * i );
			}
			
			if( componente[ 2 * i + 1 ] == -1 ){
				sp = 0;
				tarjan( 2 * i + 1 );
			}
			dm |= ( componente[ 2 * i ] == componente[ 2 * i + 1 ] );
		}
		
		if( dm ) printf( "NO\n" );
		else printf( "YES\n" );
	}
}





