#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 110
typedef long long ll;
int n, m, k;

void makeId(ll ma[N][N]){
	rep(i, N) rep(j, N) ma[i][j] = 0;
	rep(i, N) ma[i][i] = 1;
}

void makeG(int cat, ll ma[N][N]){
	makeId(ma);
	ma[n][cat] = 1;
}

void makeE(int cat, ll ma[N][N]){
	makeId(ma);
	ma[cat][cat] = 0;
}

void makeS(int c1, int c2, ll ma[N][N]){
	makeId(ma);
	ma[c1][c1] = ma[c2][c2] = 0;
	ma[c2][c1] = ma[c1][c2] = 1;
}

void mult(ll a[N][N], ll b[N][N], ll c[N][N]){
	ll tmp[N][N];
	rep(i, N) rep(j, N) tmp[i][j] = 0;
	
	ll B[N];
	rep(i, N) B[i] = 0;
	rep(j, n){
		rep(i, n){
			if(b[i][j]){
				B[j] = i;
				break;
			}
		}
	}
	B[n] = n;
	
	rep(i, n+1){
		rep(j, n+1){
			tmp[i][j] = a[i][B[j]] * b[B[j]][j] + (n == B[j] ? 0 : a[i][n] * b[n][j]);
		}
	}
	rep(i, n+1) rep(j, n+1) c[i][j] = tmp[i][j];
}

void expo(ll ma[N][N], int xp){
	ll tmp[N][N];
	makeId(tmp);
	
	while(xp){
		if(xp&1) mult(tmp, ma, tmp);
		mult(ma, ma, ma);
		xp >>= 1;
	}
	rep(i, n+1) rep(j, n+1) ma[i][j] = tmp[i][j];
}


char buf[10];
ll ma[N][N], tmp[N][N];
int main(){
	while(scanf("%d%d%d", &n, &m, &k) == 3 && (n|m|k)){
		makeId(ma);
		
		rep(i, k){
			int a;
			scanf("%s %d", buf, &a);
			--a;
			if(buf[0] == 'g'){
				makeG(a, tmp);
				
				mult(ma, tmp, ma);
			}else if(buf[0] == 'e'){
				makeE(a, tmp);
				mult(ma, tmp, ma);
			}else{
				int b;
				scanf("%d", &b);
				--b;
				makeS(a, b, tmp);
				mult(ma, tmp, ma);
			}
		
		}
		expo(ma, m);
		rep(i, n){
			if(i) printf(" ");
			cout << ma[n][i];
		}
		cout << endl;
	}
}
