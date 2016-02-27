#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <iostream>
#include <cstdio>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define mp make_pair
#define pb push_back
#define X first
#define Y second


int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	
	
	if(n*(n-1) <= 2*k) printf("no solution\n");
	else{
		int y = int(1e9), dy = 7000;
		
		rep(i, n){
			printf("%d %d\n", i, y);
			y -= dy;
		}
	}
	
}

