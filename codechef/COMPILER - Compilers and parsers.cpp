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

string text;

int main(){
	ios::sync_with_stdio(false);

	int t;
	cin >> t;

	while(t--){
		cin >> text;
		int best = 0, open = 0;

		_(SIZE(text)){
			if(text[i] == '<') ++open;
			else if(open) --open;
			else break;

			if(!open) best = i + 1;
		}

		cout << best << "\n";
	}
}