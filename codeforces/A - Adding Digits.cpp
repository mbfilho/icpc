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
#define N 100100

int a, b, n;
char num[N];

int main(){
	ios::sync_with_stdio(false);
	cin >> a >> b >> n;
	sprintf(num, "%d", a);
	
	int d = (b - ((a * 10) % b)) % b;
	if(d > 9) cout << "-1" << endl;
	else{
		int tam = strlen(num);
		num[tam++] = d + '0';
		
		rep(i, n-1){
			num[tam++] = '0';
		}
		num[tam] = 0;
		cout << num << endl;
	}	
		
}


