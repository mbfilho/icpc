#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define reps(i, str) for(int i = 0; str[i]; ++i)
#define mp make_pair
#define ft first
#define sd second
#define pb push_back
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define N 200100
#define MOD 1000000007

//Contar progressoes aritméticas

int input[N], n;
int pd[101][101];
int qtd[101];

int main(){
	ios::sync_with_stdio(false);
	int t;
	cin >> t;

	while(t--){
		memset(pd, 0, sizeof pd);
		memset(qtd, 0, sizeof qtd);

		cin >> n;
		_(n){
			int x;
			cin >> x;
			fr(a, 1, 101){
				int q = x - a;
				if(a - q > 0 && a - q <= 100){
					pd[a][x] = (pd[a][x] + pd[a-q][a]) % MOD;
				}
			}
			fr(a, 1, 101) if(a != x) pd[a][x] = (pd[a][x] + qtd[a]) % MOD;
			++qtd[x];
			pd[x][x]++, pd[x][x] %= MOD;
		}

		int tot = 0, xp = 1;
		_(101) rep(j, 101) tot = (tot + pd[i][j])%MOD;

		// fr(i, 1, 3) fr(j, 1, 3) cout << "(" << i << "," << j << "): " << pd[i][j] << endl;

		_(n) xp = (xp * 2) % MOD;

		cout << ((xp - tot - 1) % MOD + MOD) % MOD << endl;
	}
}
