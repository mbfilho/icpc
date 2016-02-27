#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace std;
typedef long long ll;
typedef pair<int,int> Ponto;
#define mp make_pair
#define X first
#define Y second
#define N 2000000

Ponto dir[] = {mp(1, 0), mp(1,1), mp(0,1), mp(-1,1), mp(-1,0), mp(-1,-1), mp(0, -1), mp(1,-1)};

ll operator*(const Ponto& a, const Ponto& b){
	return a.X * ll(b.Y) - b.X * ll(a.Y);
}

Ponto operator-(const Ponto& a, const Ponto& b){
	return mp(a.X - b.X, a.Y - b.Y);
}

Ponto operator+(const Ponto& a, const Ponto& b){
	return mp(a.X + b.X, a.Y + b.Y);
}

int n;
char seq[N];

int main(){
	while(scanf("%s", seq) != EOF){
		n = strlen(seq);
		ll area = 0;
		Ponto pivot = mp(0,0), p1 = pivot + dir[seq[0]-'0'];
		Ponto p2 = p1 + dir[seq[1]-'0'];
		area = p2 * p1;
		
		for(int i = 2; i < n; ++i){
			p1 = p2;
			p2 = p2 + dir[seq[i]-'0'];
			area += p2 * p1;
		}
		
		if(area < 0) area = -area;
		ll internos = (area - n) / 2 + 1;
		printf( "%lld\n", internos + n);
	}
}







