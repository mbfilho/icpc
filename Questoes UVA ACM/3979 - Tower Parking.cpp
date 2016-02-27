#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int,int> Ponto;
#define N 200
#define X first
#define Y second
#define mp make_pair
#define pb push_back

int n, m;

Ponto mapa[N*N];
int ind[N];

int main(){
	int casos;
	scanf("%d", &casos);
	
	while(casos--){
		scanf("%d%d", &n, &m);
		int maior = 0;
		
		for(int i = 0; i < n; ++i){
			ind[i] = 0;
			
			for(int j = 0; j < m; ++j){
				int tmp;
				scanf("%d", &tmp);
				maior = max(maior, tmp);
				
				if(~tmp)
					mapa[tmp] = mp(i,j);
			}
		}
		
		
		int tempo = 0;
		for(int k = 1; k <= maior; ++k){
			int i = mapa[k].X, j = mapa[k].Y;
			tempo += 2 * i * 10;
			
			int d1 = abs(j-ind[i]);
			int d2 = m - d1;
			tempo += min(d1, d2) * 5;
			ind[i] = j;
		}
		
		printf( "%d\n", tempo);
		
		
	}
}


