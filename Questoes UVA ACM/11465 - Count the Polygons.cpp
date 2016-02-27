#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
typedef pair<int,int> pii;
#define mp make_pair
#define X first
#define Y second
#define N 31
#define H (1<<17)
#define oo 10000000
#define conj somethingelse
#define pb push_back
typedef long long ll;

struct no{
	ll sum;
	int max;
	int c;
	
	no(){
		max = c = 0;
		sum = 0;
	}
	no(int count, int b, ll h){
		c = count;
		max = b;
		sum = h;
	}
	
	bool operator<(const no& ot) const{
		if(c != ot.c) return c < ot.c;
		if(max != ot.max) return max < ot.max;
		return sum < ot.sum; 
	}
};
vector<no> conj[2];

int num[N], n, k;

void gerar(){
	int h = n / 2;
	rep(i,2) conj[i].clear();
	
	rep(mask, (1 << h)){
		no tmp;
		rep(i, h){
			if((1 << i) & mask) tmp.sum += num[i], tmp.max = max(tmp.max, num[i]), ++tmp.c;
		}
		conj[0].pb(tmp);
	}
	
	rep(mask, (1<<(n-h))){
		no tmp;
		rep(i, n-h){
			if((1<<i) & mask) tmp.sum += num[i+h], tmp.max = max(tmp.max, num[i+h]), ++tmp.c;
		}
		conj[1].pb(tmp);
	}
	
	rep(i, 2) sort(conj[i].begin(), conj[i].end());
}

bool coun(no a, no b){return a.c < b.c;}
bool mai(no a, no b){return a.max < b.max;}

vector<ll> aux;
int bit[H];
void clearBit(){
	memset(bit, 0, sizeof bit);
}

void update(int ind){
	while(ind < H){
		bit[ind] += 1;
		ind += ind & -ind;
	}
}

int query(int ind){
	int resp = 0;
	while(ind > 0){
		resp += bit[ind];
		ind -= ind & -ind;
	}
	return resp;
}

ll contar(){
	gerar();
	
	ll res = 0;
	
	rep(p, 2){
		aux.clear();
		rep(i, conj[1-p].size())
			aux.pb(conj[1-p][i].sum);		
		sort(aux.begin(), aux.end());
		
		int i = 0;
		while(i < conj[p].size()){
			no at = conj[p][i];
			int tam = at.c;
			if(tam > k) break;
			
			int ini = lower_bound(conj[1-p].begin(), conj[1-p].end(), no(k-at.c,0,0), coun) - conj[1-p].begin();
			int fim = upper_bound(conj[1-p].begin(), conj[1-p].end(), no(k-at.c,0,0), coun) - conj[1-p].begin() - 1;
			if(ini >= conj[1-p].size() || fim >= conj[1-p].size() || conj[1-p][ini].c != k - at.c){
				++i;
				continue;
			}
			int mid;
			if(!p) //a partir de onde sou >
				mid = upper_bound(conj[1].begin() + ini, conj[1].begin() + fim + 1, at, mai) - conj[1].begin();
			else //a partir de onde sou >=
				mid = lower_bound(conj[0].begin() + ini, conj[0].begin() + fim + 1, at, mai) - conj[0].begin();
				
			clearBit();
			fr(x, ini, mid) update(lower_bound(aux.begin(), aux.end(), conj[1-p][x].sum) - aux.begin() + 1);
			
			while(i < conj[p].size() && conj[p][i].c == tam){
				at = conj[p][i];
				while(mid <= fim && (conj[1-p][mid].max < at.max || (!p && conj[1-p][mid].max <= at.max)) ){
					int ind = lower_bound(aux.begin(), aux.end(), conj[1-p][mid].sum) - aux.begin() + 1;
					update(ind);
					++mid;
				}
				ll low = 2 * conj[p][i].max - conj[p][i].sum;
				int ind = upper_bound(aux.begin(), aux.end(), low) - aux.begin();
				res += query(H - 1) - query(ind);
				++i;
			}
		}
	}
	
	return res;
}

int main(){
	int t;
	scanf("%d", &t);
	rep(cas, t){
		scanf("%d%d", &n, &k);
		rep(i, n) scanf("%d", num + i);
		printf("Case %d: %lld\n", cas + 1, contar());
	}
}



