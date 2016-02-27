#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <string>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define LIM (2500*2500+5)
int n;
int A[LIM], primos[LIM], qtd[LIM], pd[LIM], contp;

//quantidade de divisores

void pre(){
	memset(A, -1, sizeof A);

	fr(i, 2, LIM){
		if(A[i] == -1){
			A[i] = contp;
			primos[contp++] = i;
			qtd[i] = 1;
		}else{
			int ant = i / primos[A[i]];
			if(A[ant] == A[i]) qtd[i] = 1 + qtd[ant];
			else qtd[i] = 1;
		}

		rep(j, A[i]+1){
			if(ll(primos[j]) * i >= LIM) break;
			A[primos[j]*i] = j;
		}
	}

	pd[0] = 0;
	pd[1] = 1;
	fr(i, 2, LIM){
		int ant = i / primos[A[i]];
		if(ant % primos[A[i]] == 0) pd[i] = (qtd[i]+1) * (pd[ant] / (qtd[ant] + 1));
		else pd[i] = pd[ant] * 2;
	}

	fr(i, 2, LIM) pd[i] += pd[i-1];
}


int main(){
	int t;
	scanf("%d", &t);
	pre();

	while(t--){
		scanf("%d", &n);
		ll ans = 0;

		fr(a, 1, n){
			ans += pd[a*(n-a)-1];
		}
		printf("%lld\n", ans);
	}
}
