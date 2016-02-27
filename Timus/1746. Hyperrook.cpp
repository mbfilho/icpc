#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 60
typedef long long ll;

int n, m, d, q;
ll p;

ll ma[N][N];


void monta(){
	memset(ma, 0, sizeof ma);
	
	rep(j, n+1){
		if(j)
			ma[j-1][j] = j % p;
		if(j != n)
			ma[j+1][j] = ((m-1) * (n-j)) % p;
		ma[j][j] = (j * (m-2)) % p;
	}
}

void mult(ll a[N][N], ll b[N][N], ll c[N][N]){
	ll tmp[N][N];
	
	rep(i, n+1){
		rep(j, n+1){
			tmp[i][j] = 0;
			
			rep(k, n+1)
				tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % p;
		}
	}
	
	rep(i, n+1) rep(j, n+1) c[i][j] = tmp[i][j];
}

void expo(int xp, ll arg[N][N]){
	ll ident[N][N];
	rep(i, n+1){
		rep(j, n+1) ident[i][j] = 0;
		ident[i][i] = 1;
	}
	
	while(xp){
		if(xp&1) mult(ident, arg, ident);
		mult(arg, arg, arg);
		xp >>= 1;
	}
	rep(i, n+1) rep(j, n+1) arg[i][j] = ident[i][j];
}

ll pt[N][N];

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> m >> d >> p >> q;
	monta();
	expo(d, ma);

	rep(i, q){
		rep(j, n) cin >> pt[i][j];
	}
	
	rep(i, q){
		rep(j, q){
			int dif = 0;
			rep(k, n) if(pt[i][k] != pt[j][k]) ++dif;
			if(j) cout << " " ;
			cout << ma[0][dif] % p;
		}
		cout << endl;
	}
}



