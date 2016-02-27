#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)

#define N 100

int A[N];
int n;

int main(){
	scanf("%d", &n);
	rep(i, n) scanf("%d", A + i + 1);
	
	int cnt = 0;
	int i = n;
	while(i/2){
		int p = i/2;
		if(2*p+1 <= n){
			cnt += A[i];
			A[p] -= min(A[p], A[i]);
			A[2*p] -= min(A[2*p], A[i]);
			A[2*p+1] -= min(A[2*p+1], A[i]);
		}
		--i;
	}
	
	if(A[1] && n < 3) cnt = -1;
	else if(A[1]) cnt += A[1];
	fr(i, 2, n+1) if(A[i]) cnt = -1;
	
	printf("%d\n", cnt);
}


