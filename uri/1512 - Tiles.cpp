#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;
ll gcd(ll a, ll b){
	return b ? gcd(b, a %b) : a;
}

int main(){
	ll n, a, b;
	while(cin >> n >> a >> b && (n|a|b)){
		cout << (n/a + n/b - n / (a*b/gcd(a,b))) << endl;
	}
}