#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define mp make_pair
#define pb push_back
#define ft first
#define sd second
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;

int main(){
	ios::sync_with_stdio(false);
	int n, k;

	scanf("%d%d", &n, &k);
	if(n == 1) printf("%d\n", k == 0 ? 1 : -1);
	else{
		int h = n/2;
		if(h > k) printf("-1\n");
		else{
			int a1 = k-h+1, a2 = 3*(k-h+1);
			printf("%d %d", a1, a2);
			int hi = 1000000000 - 1;

			int qtd = h-1;
			while(qtd){
				if(hi == a2 || hi == a1 || hi - 1 == a2 || hi - 1 == a1) --hi;
				else{
					printf(" %d %d", hi, hi-1);
					hi -= 2;
					--qtd;
				}
			}
			if(n&1) printf(" 1000000000\n");
			else printf("\n");
		}	
	}
}