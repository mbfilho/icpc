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
#define N 10000

int A[N], primos[N], contp;

void pre(){
	memset(A, -1, sizeof A);
	contp = 0;

	fr(i, 2, N){
		if(A[i] == -1) {
			A[i] = contp;
			primos[contp++] = i;
		}

		rep(j, A[i]+1){
			if(primos[j]*i >= N) break;
			A[primos[j]*i] = j;
		}
	}
}

int ans[N], cont, n;

int main(){
	pre();
	scanf("%d", &n);


	for(int i = 0; primos[i] <= n; ++i){
		int aux = primos[i];
		while(aux <= n) {
			ans[cont++] = aux;
			aux *= primos[i];
		}
	}

	printf("%d\n", cont);
	rep(i, cont) {
		printf("%d%c", ans[i], i == cont-1 ? '\n' : ' ');
	}

	

}





