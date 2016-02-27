#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define N 100100
#define inv qlqcoisa
typedef long long ll;

char buf[N];
int n, num[N], inv[N];

int main(){
	scanf("%d", &n);
	rep(i, n) scanf("%d", num + i);
	
	if(n > 1){
		buf[n-1] = '+';
		buf[n-2] = '-';
		int	s = num[n-1] - num[n-2];
		
		for(int i = n - 3; i >= 0; --i){
			if(s >= num[i]){
				buf[i] = '-';
				s -= num[i];
			}else{
				buf[i] = '+';
				s = num[i] - s;
				inv[i+1]++;
			}
		}		
		buf[n] = 0;
		int soma = 0;
		rep(i, n){
			soma += inv[i];
			if(soma & 1){
				buf[i] = (buf[i] == '-') ? '+' : '-';
			}
		}
		printf("%s\n", buf);
	}else printf("+\n");
	
}


