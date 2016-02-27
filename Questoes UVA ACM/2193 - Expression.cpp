#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int,ll> pii;
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define ROOT 4000000
#define mp make_pair
#define X first
#define Y second
#define N 1000

struct No{
	int tam, sinal, pos;
	ll num;
	
	bool operator<(const No& a)const{
		if(tam != a.tam)
			return tam > a.tam;
		if(sinal != a.sinal)
			return sinal < a.sinal;
		
		if(sinal < 0)
			return pos < a.pos;
		else
			return pos > a.pos;
	}
	
}nos[N];



struct Se{
	int pos, no, sinal;
	
	
	bool operator<(const Se& a) const{
		if(pos != a.pos)
			return pos > a.pos;

		if(sinal == a.sinal){
		
			if(sinal < 0)
				return nos[no].pos < nos[a.no].pos;
			else
				return nos[no].pos >= nos[a.no].pos;
		}
				
		return false;
	}
};


int prt;
char buf[10000];
int tam, ind;
vector<Se> vetor;
void faz(int sinal){
	if(ind == tam) return;
	int st = sinal;
	
	while(ind < tam){
		if(buf[ind] == 0) return;
		if(buf[ind] == ')'){
			++ind;
			return;
		}
		if(buf[ind] == '-'){
			sinal = -st;
			++ind;
		}else if(buf[ind] == '('){
			++ind;
			faz(sinal);
		}else if(buf[ind] == '#'){
			nos[prt].tam = 0;
			nos[prt].sinal = sinal;
			nos[prt].pos = ind;
			nos[prt].num = 0;

		
			while(buf[ind] == '#'){
				++nos[prt].tam;
				++ind;
			}
			Se tmp;
			tmp.pos = nos[prt].tam;
			tmp.no = prt;
			tmp.sinal = sinal;
			vetor.push_back(tmp);
			++prt;
		}else if(buf[ind] == '+'){
			sinal = st;
			++ind;
		}else throw 1;
	}
}


char dig[100];
int main(){
	int t;
	scanf("%d", &t);
	
	Fr(caso, 1, t + 1){
		scanf("%s%s", buf, dig);
		tam = strlen(buf);
		prt = 0;
		ind = 0;
		vetor.clear();
		
		faz(1);
		// Fr(i, 0, prt){
			// printf( "> %d %d\n", nos[i].tam, nos[i].sinal);
		// }
		
		int d[] = {0, strlen(dig) - 1};
		sort(dig, dig + d[1] + 1);
		
		
		while(vetor.size()){
			vector<Se>::iterator it = min_element(vetor.begin(), vetor.end());
			Se at = *it;
//			printf( ">>> %d %d %d\n", at.pos, at.no, nos[at.no].sinal);
			
			if(at.sinal < 0){
				nos[at.no].num *= 10;
				nos[at.no].num += dig[d[0]] - '0';
				buf[nos[at.no].pos + (nos[at.no].tam - at.pos)] = dig[d[0]++];
			}else{
				nos[at.no].num *= 10;
				nos[at.no].num += dig[d[1]] - '0';
				buf[nos[at.no].pos + (nos[at.no].tam - at.pos)] = dig[d[1]--];
			}
			
			if(at.pos != 1){
				(*it).pos--;
			}else{
				vetor.erase(it);
			}
		}
		
		ll soma = 0;
		Fr(i, 0, prt){
			soma += nos[i].sinal * nos[i].num;
		}
		printf("Case %d:\n", caso);
		printf( "%s\n", buf);
		printf("%lld\n", soma);
	}	
}

