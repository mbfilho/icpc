#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define TRIE 7000000
struct No{
	map<char, int> adj;
	int fail;
	bitset<270> words;
	
	void init(){
		adj.clear();
		words.reset();
		fail = 0;
	}
}nos[TRIE];
int cont;

void insert(char* s, int ind){
	int at = 0;
	map<char,int>::iterator it;
	
	for(int i = 0; s[i]; ++i){
		int nt;
		if(nos[at].adj.find(s[i]) == nos[at].adj.end()){
			nt = cont++;
			nos[nt].init();
			nos[at].adj[s[i]] = nt;			
		}else
			nt = nos[at].adj[s[i]];
		at = nt;
	}
	nos[at].words[ind] = 1;
}

void failure(){
	queue<int> fila;
	for(map<char,int>::iterator it = nos[0].adj.begin(); it != nos[0].adj.end(); ++it)
		fila.push(it -> second);
		
	while(!fila.empty()){
		int at = fila.front();
		fila.pop();
		
		for(map<char,int>::iterator it = nos[at].adj.begin(); it != nos[at].adj.end(); ++it){
			fila.push(it -> second);
			int fail = nos[at].fail;
			
			while(fail && nos[fail].adj.find(it -> first) == nos[fail].adj.end())
				fail = nos[fail].fail;
	
			if(nos[fail].adj.find(it -> first) != nos[fail].adj.end())
				fail = nos[fail].adj[it -> first];
			nos[it -> second].fail = fail;
			nos[it->second].words |= nos[fail].words;
		}
	}
}

bitset<270> match(char* s){
	bitset<270> resp;
	resp.reset();
	
	int at = 0;
	for(int i = 0; s[i]; ++i){
//		printf("(%d,%d)\n", i, at);
		while(at && nos[at].adj.find(s[i]) == nos[at].adj.end()){
//			printf(">>> %d %d\n", at, nos[at].fail);
			at = nos[at].fail;
		}
		if(nos[at].adj.find(s[i]) != nos[at].adj.end())
			at = nos[at].adj[s[i]];
		resp |= nos[at].words;
	}
	
	return resp;
}

void print(int no){
	printf( "No %d\n", no);
	for(map<char,int>::iterator it = nos[no].adj.begin(); it != nos[no].adj.end(); ++it){
		printf( "adj > %c %d\n", it -> first, it -> second);
		print(it -> second);
	}
}

char vir[5100000], prog[5100000];

int main(){
	int t, n;
	scanf("%d", &t);
	
	while(t--){
		scanf("%d", &n);
		cont = 1;
		nos[0].init();
		
		rep(i, n){
			scanf("%s", vir);
			insert(vir, i);
			int tam = strlen(vir);
			reverse(vir, vir + tam);
			insert(vir, i);
		}
		failure();
//		print(0);
		scanf("%s", prog);
		int prt = 0;
		int i = 0;
		while(prog[i]){
			if(prog[i] == '['){
				int qtd = 0, j = i+1;
				
				while(prog[j] >= '0' && prog[j] <= '9'){
					qtd = 10 * qtd + prog[j] - '0';
					++j;
				}
				while(qtd--)
					vir[prt++] = prog[j];
				i = j + 2;
			}else{
				vir[prt++] = prog[i++];
			}
		}
		vir[prt] = 0;
		bitset<270> resp = match(vir);
		int c = 0;
		rep(i, 270){
			if(resp[i]) ++c;
		}
		cout << c << endl;
	}
}




