#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define LIM 3000

int A[LIM], primos[LIM], contp;


void pre(){
	memset(A, -1, sizeof A);
	contp = 0;
	
	fr(i, 2, LIM){
		if(A[i] == -1){
			A[i] = contp;
			primos[contp++] = i;
		}
		
		rep(j, A[i]+1){
			if(primos[j]*i >= LIM) break;
			A[primos[j]*i] = j;
		}
	}
}

int main(){
	pre();
	int t;
	scanf("%d", &t);
	
	while(t--){
		int x, y, *ans;
		scanf("%d %d", &x, &y);
		ans = upper_bound(primos, primos + contp, x+y);
		printf("%d\n", *ans-x-y);
	}
}