#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 40
typedef long long ll;

ll fibo[N], cont[N];

int main(){
	fibo[0] = 0, fibo[1] = 1;
	cont[0] = cont[1] = 1;
	
	fr(i, 2, N){
		cont[i] = cont[i-1] + cont[i-2] + 1;
		fibo[i] = fibo[i-1] + fibo[i-2];
	}
	
	int t;
	scanf("%d", &t);
	
	while(t--){
		int x;
		scanf("%d", &x);
		printf("fib(%d) = %lld calls = %lld\n", x, cont[x]-1, fibo[x]);
	}
}






