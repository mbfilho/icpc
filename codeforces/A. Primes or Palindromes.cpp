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
#define N 2000000

int A[N], primos[N];
int pal[N], pri[N];
int contp;

int buf[100];

int ehPal(int a){
	int x = 0;
	while(a) {
		buf[x++] = a % 10;
		a /= 10;
	}

	rep(i, x / 2){
		if(buf[i] != buf[x-1-i]) return 0;
	}

	return 1;
}

void pre(){
	memset(A, -1, sizeof A);
	contp = 0;
	pal[0] = 0, pal[1] = 1;
	pri[0] = pri[1] = 0;

	fr(i, 2, N) {
		if(A[i] == -1) {
			A[i] = contp;
			primos[contp++] = i;
		}

		rep(j, A[i]+1) {
			ll x = primos[j];
			if(x * i < N) A[x*i] = j;
			else break;
		}
		pri[i] = pri[i-1] + (A[i] != -1 && primos[A[i]] == i);
		pal[i] = ehPal(i) + pal[i-1];
	}

	// for(int i = N - 1; i >= 0; --i) {
	// 	if(42 * pal[i] >= pri[i]){
	// 		printf(">>> %d %d %d\n", i, pal[i], pri[i]);
	// 		break;
	// 	}
	// }
}



int main(){
	pre();

	ios::sync_with_stdio(false);

	int p, q;
	cin >> p >> q;

	for(int i = N-1; i >= 0; --i) {
		if(pal[i] * p >= pri[i] * q){
			cout << i << endl;
			return 0;
		}
	}

	cout << "Palindromic tree is better than splay tree" << endl;

	return 0;
}
