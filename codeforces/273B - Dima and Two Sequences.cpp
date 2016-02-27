#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
typedef long double ld;
#define mp make_pair
#define ft first
#define sd second
#define pb push_back
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define conj sdkjfhsdkhjf
#define N 200100

int A[N], primos[N], cont;

void pre(){
	memset(A, -1, sizeof A);
	cont = 0;
	
	fr(i, 2, N){
		if(A[i] == -1){
			A[i] = cont;
			primos[cont++] = i;
		}
		
		rep(j, A[i]+1){
			ll tmp = ll(i) * primos[j];
			if(tmp >= N) break;
			A[tmp] = j;
		}
	}
}


pii seq[N];
int n, m;
ll fat[N];

ll expo(ll num, int xp){
	ll res = 1;
	
	while(xp){
		if(xp & 1) res = (res * num) % m;
		num = (num * num) % m;
		xp >>= 1;
	}
	
	return res;
}

int main(){
	pre();
	ios::sync_with_stdio(false);
	cin >> n;
	
	rep(k, 2){	
		rep(i, n){
			if(cin >> seq[i+k*n].ft)
				seq[i+k*n].sd = i;
			else throw 1;
		}
	}
	cin >> m;
	n *= 2;
	sort(seq, seq + n);
	int ini = 0, fim;
	while(ini < n){
		fim = ini;
		while(fim < n && seq[fim].ft == seq[ini].ft) ++fim;
		++fat[fim-ini];
		
		fr(i, ini, fim-1){
			if(seq[i].sd == seq[i+1].sd) --fat[2]; 
		}
		ini = fim;
	}
	ll res = 1;
	
	for(int i = n; i > 1; --i) fat[i-1] += fat[i];
	for(int i = n; i > 1; --i){
		if(primos[A[i]] == i){
			res = (res * expo(i, fat[i])) % m;
		}else{	
			int tmp = i;
			while(tmp != 1){
				fat[primos[A[tmp]]] += fat[i];
				tmp /= primos[A[tmp]];
			}
		}
	}
	cout << res << endl;
	
}

