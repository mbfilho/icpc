#include <cstdio>
#include <cstring>
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)

int height(int v){
	int h = 0;
	while(v) ++h, v >>= 1;
	return h;
}

int dist(int u, int v){
	int hu = height(u), hv = height(v), tot = 0;

	while(hv > hu) --hv, ++tot, v >>= 1;
	while(hu > hv) --hu, ++tot, u >>= 1;
	
	while(u != v) tot += 2, u >>= 1, v >>= 1;

	return tot;
}

int main(){
	int n;
	scanf("%d", &n);
	
	rep(i, n){
		int u, v;
		scanf("%d%d", &u, &v);
		
		printf("%d\n",  dist(u,v));
	}
}