#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

struct No{
	vector<int> adj;
	int comp, tempo, low;
	bool exc;
}nos[ 2100 ];


int n, m;
int pilha[ 2100 ], sp, tempo, comp;

int verd( int x ){
	return 2 * x + 1;
}

int fals( int x ){
	return 2 * x;
}

int ssc( int no ){
	No& aux = nos[ no ];
	pilha[ sp++ ] = no;
	aux.tempo = aux.low = tempo++;
	
	for( int i = aux.adj.size() - 1; i >= 0; --i ){
		if( nos[ aux.adj[i] ].exc ) continue;
		
		if( nos[ aux.adj[ i ] ].tempo == -1 ){
			ssc( aux.adj[i] );
			aux.low = min( aux.low, nos[ aux.adj[i] ].low );
		}else
			aux.low = min( aux.low, nos[ aux.adj[i] ].tempo );
	}
	
	if( aux.tempo == aux.low ){
		int temp;
		
		do{
			temp = pilha[ --sp ];
			nos[ temp ].comp = comp;
			nos[ temp ].exc = true;
		}while( temp != no );
		++comp;		
	}	 
}

void addEdge( int u, int v ){
	nos[ u ].adj.push_back( v );
}

int main(){
	int a, b;
	
	while( scanf( "%d %d", &n, &m ) != EOF ){
		for( int i = 1; i <= 2 * n + 1; ++i ){
			nos[ i ].adj.clear();
			nos[ i ].comp = -1;
			nos[ i ].exc = false;
			nos[ i ].tempo = nos[ i ].low = -1;
		}
		
		for( int i = 0; i < m; ++i ){
			scanf( "%d %d", &a, &b );
			
			int verda, verb, nega, negb;
			if( a > 0 ){
				verda = verd( a );
				nega = fals( a );
			}else{
				verda = fals( -a );
				nega = verd( -a );
			}
			
			if( b > 0 ){
				verb = verd( b );
				negb = fals( b );
			}else{
				verb = fals( -b );
				negb = verd( -b );
			}
			
			addEdge( nega, verb );
			addEdge( negb, verda );				
		}
		
		tempo = comp = 0;
		for( int i = 1; i <= 2 * n + 1; ++i ){
			if( nos[ i ].comp == -1 ){
				sp = 0;
				ssc( i );
			}
		} 
		
		int resp = 1;
		for( int i = 1; i <= n; ++i ){
			if( nos[ verd( i ) ].comp == nos[ fals( i ) ].comp ){
				resp = 0;
				break;
			}				 
		}
		
		printf( "%d\n", resp );
	}
}


