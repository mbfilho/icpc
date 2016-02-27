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

int n, k;
priority_queue<int> conj;

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> k;
	rep(i, n){
		int tmp;
		cin >> tmp;
		conj.push(-tmp);
	}
	
	while(k && conj.top() > 0){
		int tmp = conj.top();
		conj.pop();
		conj.push(-tmp);
		--k;
	}
	ll soma = 0, menor = -conj.top();
	while(conj.empty() == false){
		soma += -conj.top();
		conj.pop();	
	}
	
	if((k%2) != 0) soma -= 2*menor;
	
	cout << soma << endl;
}


