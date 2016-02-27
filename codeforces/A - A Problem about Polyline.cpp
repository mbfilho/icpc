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
	int a, b;

	cin >> a >> b;

	double x = -1;
	if(a == b) x = a;
	else{
		int k = (b+a)/(2*b);
		if(k) x = (b+a)/(2.0*k);
		
		k = (b-a)/(2*b);
		if(k) x = min(x, (b-a)/(2.0*k));
	}

	if(x < 0) cout << "-1\n";
	else printf("%.9lf\n", x);

}

