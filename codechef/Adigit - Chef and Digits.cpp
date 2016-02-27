#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 100100

int qtd[10];
long long ans[N];
char str[N];

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	scanf("%s", str);
	memset(qtd, 0, sizeof qtd);
	
	rep(i, n){
		ans[i] = 0;
		int d = str[i] - '0';
		rep(j, 10) ans[i] += qtd[j] * abs(d - j);
		++qtd[d];
	}
	
	while(m--){
		int x;
		scanf("%d", &x);
		printf("%lld\n", ans[x-1]);
	}

}