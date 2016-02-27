//a*u - (n-a)*d > 0
//a*u - n*d + a*d > 0
//a*(u+d) - n*d > 0
//a*(u+d) > n*d
//a > n*d/(u+d)

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i <b; ++i)
#define rep(i,n) fr(i,0,n)

int bs(int n, int u, int d){
	int ini = 0, fim = n;
	while(ini <= fim){
		int a = (ini+fim)>>1;
		if(a*u -(n-a) * d > 0) fim = a - 1;
		else ini = a + 1;
	}
	int a = fim + 1;
	return a * u - (n-a)*d;
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);{
		int resp = -1;
		rep(i, m){
			int u, d;
			scanf("%d%d", &u, &d);
			resp = (~resp) ? min(resp, bs(n,u,d)) : bs(n,u,d);
		}
		if(resp == -1) throw 1;
		printf("%d\n", resp);
	}
}

