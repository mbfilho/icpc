#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef pair<ll,ll> F;
#define mp make_pair
#define N 25
#define oo 90000000


int p[N];
int n;
int ord[N];
int tempo[N][N];
int a, b, c;

ll gcd(ll x, ll y){
	if(!y) return x;
	return gcd(y, x % y);
}

bool operator<(const F& x, const F& y){
	return x.first * y.second < x.second * y.first;
}
ll timef(int i, int j){
	ll t = abs(i-j) * abs(i-j) * a + abs(i-j) * b + c;
	
	return t;
}

void reduz(F& f){
	ll tmp = gcd(f.first, f.second);
	f.first /= tmp;
	f.second /= tmp;
}

ll faz(){
	ll soma = 0;
	
	for(int i = 0; i < n; ++i){
		for(int j = i; j < n; ++j){
			
			if(i != j) soma += (tempo[i][j] * ord[i] * ord[j])*2;
			else soma += (tempo[i][j] * ord[i] * ord[j]);
		}
	}

	return soma;
}


int main(){
	int t;
	scanf("%d", &t);
	int caso = 1;
	
	while(t--){
		scanf("%d %d %d %d", &n, &a, &b, &c);
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j) tempo[i][j] = timef(i,j);
		}
		for(int i = 0; i < n; ++i) scanf("%d", p + i);
		sort(p, p + n);
		
		ll best = oo;
		
		if(!a && !b){
			for(int i = 0; i < n; ++i) ord[i] = p[i];
			best = faz();
		}else{
			int a = 0, b = n - 1;
			for(int i = 0; i < n; ++i){
				if(i&1) ord[a++] = p[i];
				else ord[b--] = p[i];
			}			
			best = faz();
		}
		
		F resp = mp(best, 10000);
		reduz(resp);
		printf("%d/%d\n", resp.first, resp.second);
	}
}



