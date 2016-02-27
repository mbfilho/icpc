#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 20
typedef long long ll;

int d, m;


void mult(ll a[N][N], ll b[N][N], ll c[N][N]){
	ll tmp[N][N];
	
	for(int i = 0; i < d; ++i){
		for(int j = 0; j < d; ++j){
			tmp[i][j] = 0;
			for(int k = 0; k < d; ++k)
				tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % m;
		}
	}

	for(int i = 0; i < d; ++i){
		for(int j = 0; j < d; ++j){	
			c[i][j] = tmp[i][j];
		}
	}
}

void expo(ll a[N][N], ll xp, ll c[N][N]){
	ll tmp[N][N];
	memset(tmp, 0, sizeof tmp);
	for(int i = 0; i < d; ++i) tmp[i][i] = 1;
	
	while(xp){
		if(xp&1) mult(tmp, a, tmp);
		
		mult(a,a,a);
		xp >>= 1;
	}
	
	for(int i = 0; i < d; ++i){
		for(int j = 0; j < d; ++j) c[i][j] = tmp[i][j];
	}
}

ll ma[N][N];
ll vet[N];
int n;

int main(){
	while(scanf("%d%d%d", &d, &n, &m) != EOF && (n|m|d)){
		memset(ma, 0, sizeof ma);
		for(int i = 0; i < d; ++i){
			scanf("%lld", &ma[d-i-1][d-1]);
		}
		for(int i = 0; i < d; ++i){
			scanf("%lld", vet + i);
		}
		
		for(int j = 0; j < d - 1; ++j){
			ma[j+1][j] = 1;
		}
		
		expo(ma, n - 1, ma);
		
		ll resp = 0;
		for(int i = 0; i < d; ++i){
			resp = (resp + vet[i] * ma[i][0]) % m;
		}
		printf( "%lld\n", resp);
		
	}
}







