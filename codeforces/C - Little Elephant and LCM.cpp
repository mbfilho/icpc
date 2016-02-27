#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 100100
#define MOD 1000000007
typedef long long ll;
#define LIM 100100

int A[LIM];
int primos[LIM], cont;
void pre(){
	memset(A, -1, sizeof A);
	
	fr(i, 2, LIM){
		if(A[i] == -1){
			A[i] = cont;
			primos[cont++] = i;
		}
		
		rep(j, A[i] + 1){
			ll tmp = primos[j] * i;
			if(tmp >= LIM) break;
			A[tmp] = j;
		}
	}
}

int inp[N], n;
vector<int> divi;

void back(int num, int divisor){
	if(num == 1){
		divi.push_back(divisor);
		return;
	}
	int c = 0, p = primos[A[num]];
	while((num % p) == 0) ++c, num /= p;
	int fat = 1;
	
	rep(i, c+1){
		back(num, divisor * fat);
		fat *= p;
	}
}

ll expo(ll num, int xp){
	ll r = 1;
	
	while(xp){
		if(xp&1) r = (r * num) % MOD;
		num = (num * num) % MOD;
		xp >>= 1;
	}
	
	return r;
}

int main(){
	pre();
	ios::sync_with_stdio(false);
	cin >> n;
	rep(i, n) cin >> inp[i];
	sort(inp, inp + n);
	
	ll resp = 0;
	fr(k, 1, inp[n-1]+1)
	{
		int at = k;
		divi.clear();
		back(at, 1);
		sort(divi.begin(), divi.end());
		
		ll tmp = 1;
		int last = 0;
		//contar, para cada posicao da sequencia quantos divisores podem aparecer ali. So que fazer isso em logN
		rep(i, divi.size()-1){
			int nt = lower_bound(inp, inp+n, divi[i+1]) - inp;
			tmp = (tmp * expo(i+1, nt - last)) % MOD;
			last = nt; 
		}
		
		//o ultimo intervalo eh onde o max=lcm vai aparecer. Tem que tomar cuidado em tirar as sequencias em que
		//ele nao aparece (eh essa subtracao).
		tmp = (tmp * (expo(divi.size(), n-last) - expo(divi.size()-1, n-last)) ) % MOD;
		resp = (resp + tmp) % MOD;
	}
	resp = (resp + MOD) % MOD;
	cout << resp << endl;
	
}




