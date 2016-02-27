#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 200
int pd[N][N][2];

int memo(int pos, int k, int bit){
	if(!pos) return k == 0;
	int& resp = pd[pos][k][bit];
	if(~resp) return resp;
	resp = 0;
	
	//1
	if(!bit || k) resp += memo(pos-1, k - (bit == 1), 1);
//	0
	resp += memo(pos-1, k, 0);
	
	return resp;
}

int main(){
	int t;
	scanf("%d", &t);
	memset(pd, -1, sizeof pd);
	
	rep(cas, t){
		int n, k;
		char buf[100];
		scanf("%s%d%d", buf, &n, &k);
		printf("%s %d\n", buf, memo(n, k, 0));
	}
}

