#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
#define N 110
#define M 10100

double pd[N][M];
int r, n;
int dist[N][N];

void faz(){
	memset(pd, 0, sizeof pd);
	pd[0][0] = 1;
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j < M; ++j){
			for(int k = 1; k <= r && k <= j; ++k){
				pd[i][j] += pd[i-1][j-k] / r;
			}
		}
	}
}

char buf[N];

int main(){
	int casos;
	scanf( "%d", &casos );
	for(int ca = 1; ca <= casos; ++ca){
		scanf( "%d%d", &n, &r );
		for(int i = 0; i < n; ++i ){
			scanf("%s", buf);
			for(int j = 0; buf[j]; ++j){
				dist[i][j] = (buf[j] == 'Y');
				if(!dist[i][j]) dist[i][j] = 1000000;
			}
		}
		
		for(int k = 0; k < n; ++k){
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < n; ++j) 
					dist[i][j] = dist[j][i] = min(dist[i][k] + dist[k][j], dist[i][j]);
			}
		}
		faz();
		int q;
		scanf( "%d", &q );
		printf( "Case %d\n", ca );
		while(q--){
			int u, v, m;
			scanf( "%d%d%d", &u, &v, &m);
			--u; --v;
			double soma = 0;
			for(int i = 0; i <= m; ++i ) soma += pd[dist[u][v]][i];
			printf( "%.4lf\n", soma);
		}
		printf( "\n");
	}
}


