#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 4
#define MOD 10007

void mult(int a[N][N], int b[N][N], int c[N][N]){
	int tmp[N][N];
	
	rep(i, N) rep(j, N){
		tmp[i][j] = 0;
		rep(k, N) tmp[i][j] += a[i][k] * b[k][j], tmp[i][j] %= MOD;
	}
	
	rep(i, N) rep(j, N) c[i][j] = tmp[i][j];
}

void expo(int ma[N][N], int xp){
	int tmp[N][N];
	rep(i, N){
		rep(j, N) tmp[i][j] = 0;
		tmp[i][i] = 1;
	}
	
	while(xp){
		if(xp&1) mult(ma, tmp, tmp);
		mult(ma, ma, ma);
		xp >>= 1;
	}
	rep(i, N) rep(j, N) ma[i][j] = tmp[i][j];
}


int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		int k; scanf("%d", &k);
		int ma[N][N];
		rep(i, N) rep(j, N) ma[i][j] = 1;
		rep(i, N) ma[i][i] = 2, ma[i][N-i-1] = 0;

		expo(ma, k);
		
		
		printf("%d\n", ma[0][0]);
	}
}




