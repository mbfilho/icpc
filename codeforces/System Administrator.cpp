#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)


int tot[] = {0,0}, acc[] = {0,0};

int main(){
	int n;
	scanf("%d", &n);
	
	rep(i, n){
		int s, x, y;
		scanf("%d%d%d", &s, &x, &y);
		--s;
		tot[s] += 10;
		acc[s] += x;
	}
	
	rep(i, 2){
		if(acc[i] * 2 >= tot[i]) printf("LIVE\n");
		else printf("DEAD\n");
	}
}


