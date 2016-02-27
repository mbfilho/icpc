#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)

char buf[1000];
int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		int n;
		scanf("%d", &n);
		
		int ha = 0;
		rep(i, n){
			scanf("%s", buf);
			
			for(int j = 0; buf[j]; ++j)
				ha += buf[j] - 'A' + i + j;
		}
		
		printf("%d\n", ha);
	}
}

