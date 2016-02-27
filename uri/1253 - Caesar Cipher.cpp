#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)


char buf[1000];
int n;

int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		scanf("%s%d", buf, &n);
		n = 26 - n;
		
		for(int i = 0; buf[i]; ++i){
			int ch = buf[i] -'A';
			ch = (ch + n) % 26;
			buf[i] = ch + 'A';
		}
		
		printf("%s\n", buf);
	}
}


