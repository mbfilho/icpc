#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define N 510
#define oo ((~0ULL) >> 1)

ll soma[N][N], ma[N][N];
int c, r;

ll give(int i1, int j1, int i2, int j2){
	return soma[i2][j2] - soma[i2][j1-1] - soma[i1-1][j2] + soma[i1-1][j1-1];
}

int main(){
	int t;
	scanf("%d", &t);
	
	Fr(caso, 1, t + 1){
		int q;
		scanf("%d%d%d", &r, &c, &q);
		
		Fr(i, 1, r + 1)
			Fr(j, 1, c + 1)
				scanf("%lld", &ma[i][j]);
		memset(soma, 0, sizeof soma);
		
		Fr(i, 1, r + 1)
			Fr(j, 1, c + 1)
				soma[i][j] = ma[i][j] + soma[i-1][j] + soma[i][j-1] - soma[i-1][j-1];
		
		printf( "Test Case %d:\n", caso);
		Fr(k, 1, q+1){
			int cc[2], rr[2];
			Fr(i, 0, 2)
				scanf("%d%d", rr + i, cc + i);
					
			ll best[] = {oo, oo};
			
			ll dir, esq;
			//col
			
			dir = esq = 0;
			Fr(j, cc[0], cc[1])
				esq += give(rr[0], cc[0], rr[1], j);
			
			for(int j = cc[1]; j >= cc[0]; --j){
				best[0] = min(best[0], esq + dir);
				esq -= give(rr[0], cc[0], rr[1], j - 1);
				dir += give(rr[0], j, rr[1], cc[1]);
			}
			
			//linha
			dir = esq = 0;
			Fr(i, rr[0], rr[1]){
				esq += give(rr[0], cc[0], i, cc[1]);
			}
			for(int i = rr[1]; i >= rr[0]; --i){
				best[1] = min(best[1], esq + dir);
				esq -= give(rr[0], cc[0], i - 1, cc[1]);
				dir += give(i, cc[0], rr[1], cc[1]);
			}
			
			printf( "%d %lld\n", k, best[0] + best[1]);
		}
		printf( "\n");
		
	}
}




