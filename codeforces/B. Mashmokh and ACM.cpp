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
#define N 3000
#define MOD 1000000007

int pd[2][N];
int n, k;
//simple pd
int main(){
	ios::sync_with_stdio(false);

	scanf("%d%d", &n, &k);

	fr(i, 1, n+1) pd[1][i] = 1;
	int at = 0;

	fr(s, 2, k+1){
		fr(i, 1, n+1){
			pd[at][i] = 0;
			for(int x = 1; x * i <= n; ++x){
				pd[at][i] = (pd[at][i] + pd[1-at][i*x]) % MOD;
			}
		}
		at = 1 - at;
	}

	int ans = 0;
	fr(i, 1, n+1) ans = (ans + pd[1-at][i]) % MOD;
	printf("%d\n", ans);
	
}