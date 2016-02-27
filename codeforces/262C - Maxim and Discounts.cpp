#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define conj sdkjfhsdkhjf
int m, n, menor;
int precos[100100];

int main(){
	ios::sync_with_stdio(false);
	cin >> m;
	
	rep(i, m){
		int tmp;
		cin >> tmp;
		if(!i) menor = tmp;
		else menor = min(menor, tmp);
	}
	
	cin >> n;
	rep(i, n) cin>>precos[i];
	sort(precos, precos + n);
	
	ll soma = 0;
	int prt = n - 1;
	while(prt + 1 >= menor){
		rep(i, menor){
			soma += precos[prt];
			--prt;
		}
		
		rep(i, 2){
			if(prt >= 0) --prt;
		}
	}
	
	while(prt >= 0) soma += precos[prt--];
	
	cout << soma << endl;
}


