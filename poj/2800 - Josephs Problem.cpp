#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef long long ll;
int n, k;

int bt(){
	int r = 0;
	fr(i, 1, n+1) 
		r += k % i;
	return r;
}

int main(){
	scanf("%d%d", &n, &k);
	
	int root = min(n, int(10 + sqrt(double(k))));
	ll soma;
	
	if(k != 1){
		soma = n * ll(k);
		fr(i, 1, root)
			soma -= i * (k / i);
			
		int at = root;
		while(at <= n){
			int val = k / at;
			if(!val) break;
			int nt = min(k / val, n);
			int size = nt - at + 1;
			soma -= val*(ll(at + nt) * size)/2;
			at = nt + 1;
		}
	}else soma = n - 1;
	cout << soma << endl;
}




