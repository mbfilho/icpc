#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;
typedef pair<int,int> Ponto;
#define mp make_pair
#define X first
#define Y second
int prt;

struct Var{
	string type;
	string name;
	
	bool operator<(const Var& v) const{
		if(type != v.type) return type < v.type;
		if(name != v.name) return name < v.name;
		return false;
	}
	
	bool operator==(const Var& v) const{
		return type == v.type && name == v.name;
	}
};

struct Func{
	string name;
	vector<Var> par;
	
	bool operator<(const Func& f) const{
		if(name != f.name) return name < f.name;
		if(par.size() != f.par.size()) return par.size() < f.par.size();
		if(par != f.par) return par < f.par;
		
		return false;
	}
};

map<string, vector<string> > mapa;

void print(const Func& f){
	printf("%s(", f.name.c_str());
	for(int i = 0; i < f.par.size(); ++i){
		printf( "%s %s,", f.par[i].type.c_str(), f.par[i].name.c_str());
	}
	printf(")\n");
}


bool pode(const Func& at, Func& cal){
//	printf("match{\n");
//	print(at);
//	print(cal);
//	printf("}\n");
	
	if(at.name != cal.name) return false;
	if(at.par.size() != cal.par.size()) return false;
	
	for(int i = 0; i < at.par.size(); ++i){
		Var ta = at.par[i], tc = cal.par[i];
		vector<string> tipos = mapa[tc.name];
		
		if(ta.type != "T" && find(tipos.begin(), tipos.end(),ta.type) == tipos.end()) return false;
	}
	return true;
}


set<Func> funcs;
char linha[300], tipo[300], nome[300];
int main(){
	int n;
	scanf("%d", &n);
	gets(linha);
	
	for(int i = 0; i < n; ++i){
		gets(linha);
		int tam = strlen(linha);
		
		string aux = "";
		int prt = 0;
		while(prt < tam && aux != "void"){
			if(linha[prt] != ' ') aux += linha[prt];
			++prt;
		}
		
		aux = "";
		while(prt < tam && linha[prt] != '('){
			if(linha[prt] != ' ') aux += linha[prt];
			++prt;
		}
		
		Func funcao;
		funcao.name = aux;
		
		++prt;//pila o '('
		
		while(prt < tam && linha[prt] != ')'){
			aux = "";
			while(prt < tam && linha[prt] != ',' && linha[prt] != ')'){
				if(linha[prt] != ' ') aux += linha[prt];
				++prt;
			}
			++prt;
			
			if(aux != ""){
				Var var;
				var.type = aux;
				var.name = "";
				funcao.par.push_back(var);
			}
		}
		
		funcs.insert(funcao);
	}
	
//	for(set<Func>::iterator it = funcs.begin(); it != funcs.end(); ++it){
//		print(*it);
//	}
		
	int q;
	scanf("%d", &q);
	
	while(q--){
		scanf("%s %s", tipo, nome);	
		mapa[nome].push_back(tipo);	
	}
	scanf("%d", &q);
	gets(linha);
	
	while(q--){
		gets(linha);
		int prt = 0, tam = strlen(linha);
		string aux = "";
		
		while(prt < tam && linha[prt] != '('){
			if(linha[prt] != ' ') aux += linha[prt];
			++prt;
		}
		
		++prt;//pula '('
		Func funcao;
		funcao.name = aux;
		
		while(prt < tam && linha[prt] != ')'){
			aux = "";
			while(prt < tam && linha[prt] != ')' && linha[prt] != ','){
				if(linha[prt] != ' ') aux += linha[prt];
				++prt;
			}
			++prt;
			
			if(aux != ""){
				Var var;
				var.name = aux;
				var.type = "";
				funcao.par.push_back(var);
			}
		}
		
		int cont = 0;
		for(set<Func>::iterator it = funcs.begin(); it != funcs.end(); ++it){
			if(pode(*it, funcao)) ++cont;
		}
		printf( "%d\n", cont);
	}
}



