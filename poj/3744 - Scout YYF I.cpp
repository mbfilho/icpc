#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 20
#define M 2
#define EPS 1e-8
typedef long double ld; 
int bombs[N];

inline void mult(ld a[M][M], ld b[M][M], ld c[M][M]){
	ld tmp[M][M];
	
	rep(i, M) rep(j, M){
		tmp[i][j] = 0;
		rep(k, M) tmp[i][j] += a[i][k] * b[k][j];
	}
	rep(i, M) rep(j, M) c[i][j] = tmp[i][j];
}

inline void expo(ld ma[M][M], int xp){
	ld tmp[M][M];
	memset(tmp, 0, sizeof tmp);
	rep(i, M) tmp[i][i] = 1;
	
	while(xp){
		if(xp&1) mult(tmp, ma, tmp);
		mult(ma, ma, ma);
		xp >>= 1;
	}
	rep(i, M) rep(j, M) ma[i][j] = tmp[i][j];
}

int main(){
	ld p;
	int n;
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);

	while(cin >> n >> p){
		rep(i, n) cin >> bombs[i];
		sort(bombs, bombs + n);
		
		int prt = 1;
		ld resp = 1;
		if(bombs[0] == 1) resp = 0;
		
		rep(i, n){
			int tam = bombs[i] - prt;
			ld ma[M][M] = {{0, (1-p)}, {1, p}};
			if(!tam){
				resp = 0;
				break;
			}
			expo(ma, tam-1);
			ld tmp = ma[0][0] * 1 + ma[1][0] * p;
			resp *= tmp * (1-p);
			prt = bombs[i]+1;
		}
		cout << setiosflags(ios::fixed)  << setprecision(7) << (resp+EPS) <<  endl;
	}	
}

