#include <bits/stdc++.h>

using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef pair<int,int> pii;
typedef vector<int> vi;
//typedef int ull;
typedef long long ll;
#define pb push_back
#define B 13
#define mp make_pair

ll get(ll arg, int p){
	return (arg >> (4*p)) & 0xfLL;
}


void print(ll arg){
	rep(i, 12)
		printf("%lld*", get(arg, i)+1);
	printf("\n");
}


ll seta(ll& arg, ll value, int p){
	value <<= 4*p;
	arg = (arg & (~(0xfLL << 4LL*p))) | value;
}

void rotLeftHor(ll& arg){
	int a[] = {get(arg,0), get(arg,11)};
	rep(i, 5)
		seta(arg, get(arg, i+1), i);
	seta(arg, a[0], 11);
	seta(arg, a[1], 5);
}

void rotLeftAnt(ll& arg){
	int a[] = {get(arg,11), get(arg,5)};
	
	for(int i = 5; i > 0; --i)
		seta(arg, get(arg, i-1), i);
	seta(arg, a[0], 0);
	seta(arg, a[1], 11);
}

void rotRightHor(ll& arg){
	int a = get(arg,5);
	fr(i, 5, 11)
		seta(arg, get(arg, i+1), i);
	seta(arg, a, 11);
}

void rotRightAnt(ll& arg){
	int a = get(arg,11);
	
	for(int i = 11; i > 5; --i)	
		seta(arg, get(arg, i-1), i);
	seta(arg, a, 5);
}

void rotAllAnt(ll& arg){
	int a = get(arg,11);
	for(int i = 11; i > 0; --i)
		seta(arg, get(arg, i-1), i);
	seta(arg, a, 0);
}

void rotAllHor(ll& arg){
	int a = get(arg,0);
	arg >>= 4;
	seta(arg, a, 11);
}

struct no{
	ll v;
	int d;
	
	void set(ll a, int c){
		v = a;
		d = c;
	}
	no(){}
	
	
}fila[10000000];

//map<ll,int> mk[2];

#define X 1000000
struct Mapa{
	vector<pair<ll,int> > val[X];
	bitset<X> bits;
	
	int get(ll value){
		int ind = value % X;
		if(!bits[ind]) return -1;
		rep(i, val[ind].size()){
			if(val[ind][i].first == value) return val[ind][i].second;
		}
		
		return -1;
	}
	
//	bool esta(ll value){
//		return get(value) != -1;
//	}
//	
	void insert(ll value, int d){
		int ind = value % X;
		if(!bits[ind]){
			bits[ind] = true;
			val[ind].clear();
		}
		val[ind].pb(mp(value, d));
	}
	
	void clear(){
		bits.reset();
//		rep(i, X) val[i].clear();
	}
}mk[2];

void (* sides[])(ll&) = { rotAllAnt, rotAllHor, rotLeftHor, rotLeftAnt, rotRightHor, rotRightAnt};

//void func(ll& arg, int k){
//	if(!k) rotAllAnt(arg);
//	else if(k==1) rotAllHor(arg);
//	else if(k==2) rotLeftHor(arg);
//	else if(k==3) rotLeftAnt(arg);
//	else if(k==4) rotRightHor(arg);
//	else if(k==5) rotRightAnt(arg);
//}

int generate(int k, ll arg){
	mk[k].clear();
	
	mk[k].insert(arg, 0);
	int ini = 0, fim = 1;
	fila[0].set(arg,  0);
//	print(arg);
	while(ini < fim){
		no at = fila[ini++];

		
		if(k){
			int h = mk[0].get(at.v);
			if(~h)
				return at.d + h;
		}
		if(at.d + 1 >= 10) break;
		
		rep(i, 6){
			ll v = at.v;
			sides[i](v);
//			func(v,i);
			
			int h = mk[k].get(v);
			if(h == -1){
				mk[k].insert(v, at.d+1);
				fila[fim++].set(v, at.d+1);
			}
		}
	}
	
	return 1000;
}

int bs(int k, ll hash){
	return mk[k].get(hash);
}

int main(){
	int t;
	scanf("%d", &t);
	ll at = 0;
	rep(i,12){
		seta(at, i, i);
	}
	generate(0, at);

	while(t--){
		ll input = 0;
		rep(i, 12){
			int tmp;
			scanf("%d", &tmp);
			seta(input, tmp-1, i);
		}
		
		int tmp = bs(0, input);
		if(~tmp) printf("%d\n", tmp);
		else{
			int dist = generate(1, input);
			
			if(dist == 1000) printf("19\n");
			else printf("%d\n", dist);
			
		}
	}
}



