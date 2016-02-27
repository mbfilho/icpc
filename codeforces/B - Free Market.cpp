#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 505000

bool pd[N];
int n, d;
int c[100], aux[N];


int main(){
	memset(pd, 0, sizeof pd);
	scanf("%d%d", &n, &d);	
	pd[0] = true;
	rep(i, n) scanf("%d", c + i);
	
	rep(i, n) for(int j = N - 1; j >= c[i]; --j){
		pd[j] |= pd[j-c[i]];
	}
	int a = 0, last = 0, dias = 0;
	
	rep(i, N) if(pd[i]) aux[a++] = i;
	int i = 0;
	
	while(i < a){
		int x = i;
		while(i < a && aux[i] - last <= d) ++i;
		if(x == i) break;
		if(i) last = aux[i-1], ++dias;
	}
	if(!last) dias = 0;
	printf("%d %d\n", last, dias);
	
}

