#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> Ponto;
#define X first
#define Y second
#define N 55
#define mp make_pair
#define pb push_back

bool pd[N][N][N];
Ponto pred[N][N][N];

char ma[N][N];
int n;

vector<int> adj[N][30], rev[N][30];

void faz(){
	memset( pd, false, sizeof pd );
	queue< pair<Ponto,int> > fila;
	vector< pair<Ponto,int> > tmp;
	
	for( int i = 0; i < n; ++i ){
		for( int j = i + 1; j < n; ++j ){
			fila.push( mp( mp(i,j), 1 ) );
			pd[i][j][1] = true;
		}
	}
	
	//i..e, size = 2
	for( int c = 0; c <= 'Z' - 'A'; ++c ){
		for( int i = 0; i < n; ++i ){
			for( int x = 0; x < adj[i][c].size(); ++x ){
				int mean = adj[i][c][x];
				for( int z = 0; z < adj[mean][c].size(); ++z ){
					int e = adj[mean][c][z];
					if(!pd[i][e][2]){
						pd[i][e][2] = true;
						pred[i][e][2] = mp(mean,mean);
						fila.push(mp(mp(i,e),2));
					}
				}
			}
		}
	}
	
	while( !fila.empty() ){
		tmp.clear();
		tmp.pb(fila.front());
		fila.pop();
		
		while(!fila.empty() && fila.front().Y == tmp[0].Y){
			tmp.pb(fila.front());
			fila.pop();
		}
		
		//a..i..j..e
		for( int c = 0; c <= 'Z' - 'A'; ++c ){
			for( int h = 0; h < tmp.size(); ++h ){
				int i = tmp[h].X.X, j = tmp[h].X.Y, k = tmp[h].Y;
				
				for( int x = 0; x < rev[i][c].size(); ++x ){
					int a = rev[i][c][x];
					for( int z = 0; z < adj[j][c].size(); ++z ){
						int e = adj[j][c][z];
						
						if(!pd[a][e][k+2]){
							pd[a][e][k+2] = true;
							pred[a][e][k+2] = mp(i,j);
							fila.push(mp(mp(a,e),k+2));
						}
					}
				}
			}
		}
	}
}

void print( int i, int j, int  k ){
	if( k == 1 ) printf( "%c", ma[i][j] );
	else if( k == 2 ) printf( "%c%c", ma[i][ pred[i][j][2].X ], ma[ pred[i][j][2].X ][j] );
	else{
		printf( "%c", ma[i][ pred[i][j][k].X ] );
		print( pred[i][j][k].X, pred[i][j][k].Y, k - 2 );
		printf( "%c", ma[ pred[i][j][k].Y ][j] );
	}
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	
	while(casos--){
		scanf( "%d", &n );
		for( int i = 0; i < n; ++i ){
			scanf( "%s", ma[i] );
		}
		
		for( int i = 0; i < n; ++i ){
			for( int x = 0; x <= 'Z' - 'A'; ++x ){
				adj[i][x].clear();
				rev[i][x].clear();
			}
		}
		
		for( int i = 0; i < n; ++i ){
			for( int j = i + 1; j < n; ++j ){
				if(!(ma[i][j] >= 'A' && ma[i][j] <= 'Z')) throw 1;
				adj[i][ ma[i][j] - 'A' ].pb(j);
				rev[j][ ma[i][j] - 'A' ].pb(i);
			}
		}
		
		faz();

		bool achou = false;
		for( int i = n - 1; i > 0; --i ){
			if( pd[0][n-1][i] ){
				print(0, n-1, i);
				printf( "\n" );
				achou = true;
				break;
			}
		}
		
		if(!achou){
			throw 1;
			printf( "NO PALINDROMIC PATH\n" );
		}
	}
}





