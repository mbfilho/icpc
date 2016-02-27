#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define pb push_back
#define ft first
#define sd second
#define mp make_pair
#define SIZE(x) int(x.size())
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define MOD 1000000007

#define N 4010

int _S[N][N];
//Importante: uma relação de equivalência define uma partição

//maneiras de se particionar tot elementos em part partições
int S(int tot, ll part) {
	if(part == tot && tot == 0)  return 1;
	if(part == 0) return 0;
	if(part > tot) return 0;
	if(~_S[tot][part]) return _S[tot][part];

	int& s = _S[tot][part];

	s = S(tot-1, part-1) + (part*S(tot-1, part))%MOD;

	return s = s % MOD;
}
int comb[N][N];

int main(){
	memset(comb, 0, sizeof comb);
	rep(i, N){
		comb[i][0] = comb[i][i] = 1;
		fr(j, 1, i+1){
			comb[i][j] = (comb[i-1][j] + comb[i-1][j-1])%MOD;
		}
	}


	ios::sync_with_stdio(false);
	int n;
	cin >> n;

	int s = 0;
	memset(_S, -1, sizeof _S);

//deixei left elementos fora de qualquer partição.
	fr(left, 1, n+1){
		int x = n - left;
		ll acc = 0;
		//toda partição é um contraexemplo porque não usa os n elementos
		fr(p, 0, x+1) acc = (acc + S(x, p))%MOD;

		//quantas maneiras eu tenho de deixar left elementos de fora
		s = (s+(acc*comb[n][left])%MOD)%MOD;
	}
	cout << s << endl;
}

