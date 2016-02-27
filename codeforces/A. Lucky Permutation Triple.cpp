#include <cstdio>
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 100000
int res[N];

int main(){
	int n;
	scanf("%d", &n);
	if(n&1){
		rep(j, 2){
			rep(i, n){
				if(i) printf(" ");
				printf("%d", i);
			}
			printf("\n");
		}
		rep(i, n){
			if(i) printf(" ");
			printf("%d", (i+i)%n);
		}
		printf("\n");
	}else printf("-1\n");
}

