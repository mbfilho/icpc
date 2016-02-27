#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define pb push_back
#define ft first
#define sd second
#define mp make_pair
#define SIZE(x) int(x.size())
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;



int main(){
	ios::sync_with_stdio(false);

	ll a;
	cin >> a;

	a %= 6;
	if(a == 0 || a == 1 || a == 3) cout << "yes\n";
	else cout << "no\n";
}