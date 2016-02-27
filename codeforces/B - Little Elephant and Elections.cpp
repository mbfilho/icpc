#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 100100
#define MOD 1000000007
typedef long long ll;

char num[20];
int tam;
int pd[20][20][2];

int memo(int k, int ind, bool zero, bool tight){
	if(num[ind] == 0){
		if(zero) return 0;
		if(k) return 0;
		return 1;
	}
	
	if(!tight && pd[k][ind][zero] != -1) return pd[k][ind][zero];
	
	int lim = tight ? (num[ind] - '0' + 1) : 10;
	int ret = 0;
	rep(i, lim){
		int nk = k;
		if(!k && (i == 4 || i == 7)) continue;
		if(i == 4 || i == 7) --nk;
		ret += memo(nk, ind + 1, zero && i == 0, tight && i == lim-1);
	}
	
	if(!tight) pd[k][ind][zero] = ret;
	return ret;
}

ll geta(int num, int qtd){
	ll tmp = 1;
	
	rep(i, qtd){
		tmp = (tmp * num) % MOD;
		--num;
	}
	
	return tmp;
}

int res[11];
int coef[20];

ll back(int part, int conco, int somaMax, int somaAt){
	if(conco == 0){
		ll resp = 1;
		fr(i, 0, part){
			resp = (resp * geta(res[i], coef[i])) % MOD;
		}
		
		//com repeticao
		ll fat = geta(6, 6);
		fr(i, 0, part){
			if(coef[i])
				fat /= geta(coef[i], coef[i]);
		}
		
		resp = (resp * fat) % MOD;
		return resp;
	}
	if(part > 10) return 0;
	
	ll resp = 0;
	rep(i, 1+min(conco, res[part])){
		if(i * part + somaAt > somaMax) break;
		coef[part] = i;
		resp = (resp + back(part+1, conco-i, somaMax, somaAt + i * part)) % MOD;
	}
	coef[part] = 0;
	return resp;
}


int main(){
	memset(pd, -1, sizeof pd);
	ios::sync_with_stdio(false);
	cin >> num;
	
	ll resp = 0;
	ll acc = 0;
	rep(i, 11) res[i] = memo(i, 0, true, true);
	fr(i, 1, 11){
		ll particoes = back(0, 6, i-1, 0);//atribuir aos concorrentes os numeros com 0, 1... lucky numbers
		resp = (resp + res[i] * particoes) % MOD;
	}
	
	cout << resp << endl;
}




