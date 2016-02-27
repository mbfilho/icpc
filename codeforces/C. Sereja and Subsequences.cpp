#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <set>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define pb push_back
#define mp make_pair
#define N 1000100
ll mod = 1000000007;


ll bit[N];

ll query(int idx){
	ll soma = 0;
	
	for(int i = idx; i > 0; i -= i & -i) soma = (soma + bit[i]) % mod;
	return soma;
}

void update(int idx, ll val){
	for(int i = idx; i < N; i += i & -i)
		bit[i] = (bit[i] + val) % mod;
}



ll s[N], n;
int last[N];

int main(){
	ios::sync_with_stdio(false);
	cin >> n;
		
	rep(i, n) cin >> s[i];
	
	rep(i, n){
		ll val = (s[i] + query(s[i]) * s[i]) % mod;
		ll old = (query(s[i]) - query(s[i]-1)) % mod;
		update(s[i], val - old);
		last[s[i]] = i;
	}
	
	ll soma = 0;
	rep(i, n){
		if(last[s[i]] == i){
			soma = (soma + query(s[i]) - query(s[i]-1)) % mod;
		}
	}
	
	soma = ((soma % mod) + mod) % mod;
	cout << soma << endl;
}


