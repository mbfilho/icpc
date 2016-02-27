#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 200
#define MOD 1000007
int pd[N][N];
char ma[N][N];
int n;

bool valid(int a, int b){
	return a >=  0 && a < n && b >= 0 && b < n;
}

int main(){
	int t;
	scanf("%d", &t);
	fr(cas, 1, t+1){
		scanf("%d", &n);
		rep(i, n) scanf("%s", ma[i]);
		int x, y;
		rep(i, n) rep(j, n) if(ma[i][j] == 'W') x = i, y = j;
		memset(pd, 0, sizeof pd);
		pd[x][y] = 1;
		
		for(int i = x; i > 0; --i){
			rep(j, n){
				if(valid(i-1, j-1)){
					if(ma[i-1][j-1] == 'B' && valid(i-2, j-2) && ma[i-2][j-2] != 'B') pd[i-2][j-2] += pd[i][j], pd[i-2][j-2] %= MOD;
					else if(ma[i-1][j-1] != 'B') pd[i-1][j-1] += pd[i][j], pd[i-1][j-1] %= MOD;
				}
				if(valid(i-1, j+1)){
					if(ma[i-1][j+1] == 'B' && valid(i-2, j+2) && ma[i-2][j+2] != 'B') pd[i-2][j+2] += pd[i][j], pd[i-2][j+2] %= MOD;
					else if(ma[i-1][j+1] != 'B') pd[i-1][j+1] += pd[i][j], pd[i-1][j+1] %= MOD;
				}
			}
		}
		int soma = 0;
		rep(i, n) soma += pd[0][i], soma %= MOD;
		printf("Case %d: %d\n", cas, soma);
	}
}
