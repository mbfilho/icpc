#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <iostream>
using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
#define ft first
#define sd second
#define N 10100

#define NUD 0

int L[N], R[N], Y[N], X[N], S[N], Flip[N], Pai[N], cont = 1;

void update(int no){
	if(!no) return;
	S[no] = S[L[no]] + S[R[no]] + 1;
	if(R[no]) Pai[R[no]] = no;
	if(L[no]) Pai[L[no]] = no;
}

void fix(int no){
	if(!no) return;
	if(Flip[no]) swap(R[no], L[no]), Flip[L[no]] ^= 1, Flip[R[no]] ^= 1;
	
	Flip[no] = 0;
}

void split(int no, int val, int& lef, int& ri){
	fix(no);

	if(!no) Pai[lef] = Pai[ri] = NUD, lef = ri = NUD;
	else{
		int c = S[L[no]] + 1;
		if(val < c) ri = no, split(L[no], val, lef, L[no]);
		else{
			val -= c;
			lef = no;
			split(R[no], val, R[no], ri);
		}
	}
	update(no);
}

int merge(int lef, int ri){
	fix(lef), fix(ri);

	if(!lef) return ri;
	if(!ri) return lef;

	if(Y[lef] < Y[ri]){
		R[lef] = merge(R[lef], ri), update(lef);
		return lef;
	}else{
		L[ri] = merge(lef, L[ri]), update(ri);
		return ri;
	}

}

int add(int no, int nw){
	int left = NUD, right = NUD;
	split(no, X[nw], left, right);
	left = merge(no, nw);
	no = merge(left, right);
	update(no);
	return no;
}

void fixToRoot(int no){
	if(Pai[no]) fixToRoot(Pai[no]);
	fix(no);
}

int calcCurPos(int no){
	fixToRoot(no);
	int pos = 0, soma = 1;

	while(no){
		if(soma) pos += S[L[no]] + 1;

		if(R[Pai[no]] == no) soma = true;
		else soma = false;
		no = Pai[no];
	}

	return pos;
}

#define M 5001
pii input[N];
vector<pii> ans;

int main(){
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int root = NUD;

	rep(i, n){
		cin >> input[i].ft, input[i].sd = i + 1;

		X[cont] = i+1;
		Y[cont] = rand();
		root = add(root, cont);
		++cont;
	}

	sort(input, input + n);

	fr(i, 1, 1+n){
		int pos = calcCurPos(input[i-1].sd);

		if(pos != i){
			ans.pb(mp(i, pos));
			int low = NUD, hi = NUD, toInv = NUD;
			split(root, pos, low, hi);
			split(low, i-1, low, toInv);
			Flip[toInv] = 1;

			low = merge(low, toInv);
			root = merge(low, hi);
		}
	}

	cout << ans.size() << endl;
	rep(i, ans.size()) cout << ans[i].ft << " " << ans[i].sd << endl;
}




