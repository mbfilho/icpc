#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define mp make_pair
#define ft first
#define sd second
#define pb push_back
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;

ll gcd(ll a, ll b){
	return b ? gcd(b, a % b) : a;
}

int main(){
	ios::sync_with_stdio(false);
	int t;
	cin >> t;

	while(t--){
		ll n, m;
		cin >> n >> m;
		ll tot = ll(n) * m, odd = (n / 2) * (m - m / 2) + (n - n/2) * (m / 2), mdc = gcd(odd, tot);

		cout << (odd / mdc) << "/" << (tot / mdc) << endl;
	}
}
