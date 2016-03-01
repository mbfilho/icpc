#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define N 20000
#define oo 0x7fffffff

int FIRST = 0, SECOND = 1, DRAW = 2;

struct Grafo{
	bool marc[N];
	vector<int> adj[N];
	vector<int> rev[N];
	vector<bool> gr[N]; 
	int f[N], c[N];
	int n, m;
	
	void clear(){
		for( int i = 0; i < N; ++i ){
			gr[i] = vector<bool>( 4000, false );
			adj[i].clear();
			rev[i].clear();
			f[i] = oo;
		}
	}
}A, B;

void loose( Grafo& g ){
	memset( g.marc, false, sizeof g.marc );
	for( int i = 1; i <= g.n; ++i ){
		g.c[i] = g.adj[i].size();
	}
	
	queue<int> fila;
	for( int i = 1; i <= g.n; ++i ){
		if( !g.c[i] ){
			fila.push(i);
			g.f[i] = 0;
			g.marc[i] = true;
		}
	}
	
	while( !fila.empty() ){
		int at = fila.front();
		fila.pop();

		if( g.f[at] == 0 ){
			for( int i = 0; i < g.rev[at].size(); ++i ){
				int nt = g.rev[at][i];
				g.gr[nt][0] = true;
				if( g.marc[nt] ) continue;
				g.marc[nt] = true;
				fila.push(nt);
			}
		}else{
			for( int i = 0; i < g.rev[at].size(); ++i ){
				int nt = g.rev[at][i];
				
				if( g.marc[nt] ) continue;
				
				--g.c[nt];
				
				if( !g.c[nt] ){
					g.marc[nt] = true;
					fila.push(nt);
					g.f[nt] = 0;
				}
			}
		}
	}	
}

void grundy( Grafo& g ){
	loose(g);
	bool mudou = true;
	int k = 1;
	
	while( mudou ){
		mudou = false;
		queue<int> fila, lvl;
		memset( g.marc, false, sizeof g.marc );
		for( int i = 1; i <= g.n; ++i ){
			g.c[i] = g.adj[i].size();
		}
		
		for( int i = 1; i <= g.n; ++i ){
			if( g.f[i] < k ){
				fila.push(i);
				lvl.push(0);
				g.marc[i] = true;
			}
		}
		
		while( !fila.empty() ){
			int at = fila.front(); fila.pop();
			int ind = lvl.front(); lvl.pop();
			
			if( ind & 1 ){ //impar, coloca de qlq jeito
				for( int i = 0; i < g.rev[at].size(); ++i ){
					int nt = g.rev[at][i];
					
					if( g.f[at] != oo ){
						g.gr[nt][ g.f[at] ] = true;
					}
						
					if( g.marc[nt] ) continue;
					g.marc[nt] = true;
					fila.push(nt);
					lvl.push(ind + 1);
				}
			}else{ //par, coloca apenas se zerar
				for( int i = 0; i < g.rev[at].size(); ++i ){
					int nt = g.rev[at][i];
					
					if( g.f[at] != oo )
						g.gr[nt][ g.f[at] ] = true;
						
					if( g.marc[nt] ) continue;
					
					--g.c[nt];
					if( !g.c[nt] ){
						g.marc[nt] = true;
						
						int cont = 0;
						for( int x = 0; x < k; ++x ){
							if( g.gr[nt][x] ) ++cont;
						}
					
						if( cont == k ){
							fila.push(nt);
							lvl.push(1+ind);
							g.f[nt] = k;
							mudou = true;
						}else{ /*num liga*/ }
					}
				}
			}
		}
		++k;
	}
}

			

int query( int a, int b ){
	if( A.f[a] == B.f[b] ){
		if( A.f[a] == oo ){
			//caso 2
			return DRAW;
		}else{
			//caso 1, 4
			return SECOND; // xor = 0
		}
	}else if( A.f[a] == oo ){
		int k = B.f[b];
		
		for( int i = 0; i < A.adj[a].size(); ++i ){
			int nt = A.adj[a][i];
			if( A.f[nt] == k ){
				//caso2
				return FIRST;
			}
		}
		
		//caso3
		
		return DRAW;
	}else if( B.f[b] == oo ){
		int k = A.f[a];
		
		for( int i = 0; i < B.adj[b].size(); ++i ){
			int nt = B.adj[b][i];
			
			if( B.f[nt] == k ){
				//caso2
				return FIRST;
			}
		}
		
				//caso8
		return DRAW;
	}else{//diferentes
	//caso3
		return FIRST;
	}
}

void load( Grafo& g ){
	scanf( "%d %d", &g.n, &g.m );
	for( int i = 0; i < g.m; ++i ){
		int u, v;
		scanf( "%d %d", &u, &v );
		g.adj[u].push_back(v);
		g.rev[v].push_back(u);
		//loops: caso 2!
	}
}

int main(){
	#ifndef X
	freopen( "smith.in", "r", stdin );
	freopen( "smith.out", "w", stdout );
	#endif
	
	A.clear(); B.clear();
	
	load(A);
	load(B);
	grundy(A);
//	for( int i = 1; i <= A.n; ++i )
//		printf( "%d %d\n",i,  A.f[i] );

	grundy(B);
	int ca = 0, cb = 0;
	for( int i = 1; i <= B.n; ++i ){
		if( B.f[i] == oo ) ++cb;
	}
	for( int i = 1; i <= A.n; ++i ){
		if( A.f[i] == oo ) ++ca;
	}
	
	int t;
	scanf( "%d", &t );
	while( t-- ){
		int u, v;
		scanf( "%d %d", &u, &v );
		int resp = query( u, v );
		if( resp == DRAW ) printf( "draw\n" );
		else if( resp == FIRST ) printf( "first\n" );
		else if( resp == SECOND ) printf( "second\n" );
	}
}


