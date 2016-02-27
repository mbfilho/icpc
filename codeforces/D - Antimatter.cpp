#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 2000
#define SUM 10100
#define BASE 10000
#define MOD 1000000007
int n, A[N], memo[N][2*SUM];

int rec(int i, int s){
	if(i >= n) return (s == 0);
	
	int& pd = memo[i][s + BASE];
	if(~pd) return pd;
	
	pd = (s == 0) ? 1 : 0;
	pd += rec(i+1, s - A[i]) + rec(i+1, s + A[i]);
	pd %= MOD;
	
	return pd;
}


int main(){
	scanf("%d", &n);
	rep(i, n) scanf("%d", A + i);
	memset(memo, -1, sizeof memo);
	
	int ans = 0;
	rep(i, n) ans += rec(i+1, A[i]), ans %= MOD, ans += rec(i+1, -A[i]), ans %= MOD;
	
	printf("%d\n", ans);
}