/*
Student Name: Begun Unal
Student Number: 2013400021
Project Numbner: 4
Operating System: Virtual Machine
Compile Status: {Compiling/Not Compiling}
Program Status: {Working/Not Working}
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include <iostream>
#include <fstream>
#include <stack>
#include <list>
#include <queue>
using namespace std;

struct Node{
	int id;
	bool isInfected = false;
	bool visited = false;
	vector<Node*> adj;
};
int state = 0;
queue<Node*>infected;
vector<Node> cities;
unsigned int T;
void importData (char* infilename){
	unsigned int N,M,K;
	ifstream reader(infilename);
	reader>>N;
	unsigned int i;
	for(i=0; i<N; i++){
	Node n;
	n.id = i+1;
	cities.push_back(n);
	}
	reader>>M;
	reader>>K;
	reader>>T;
	for(i=0; i<M; i++){
		int firstVer,secondVer;
		reader>>firstVer;
		reader>>secondVer;
		cities[firstVer-1].adj.push_back(&cities[secondVer-1]);
		cities[secondVer-1].adj.push_back(&cities[firstVer-1]);
	}
	for(i=0; i<K; i++){
		int k;
		reader>>k;
		cities[k-1].isInfected =true;
		infected.push(&cities[k-1]);
	}
}
void infecting(Node *n){
	 vector<Node*>::iterator it;
	for(it=n->adj.begin(); it!=n->adj.end(); it++){
		if(!(*it)->isInfected){
			(*it)->isInfected = true;
			infected.push(*it);
		}
	}
}
void dfs(Node &n){
	n.visited = true;
	for(unsigned int i=0; i<n.adj.size(); i++){
		if(!n.adj[i]->isInfected && !n.adj[i]->visited)
			dfs(*n.adj[i]);
	}
}
int main(int argc, char *argv[]){
	if(argc!=3){
		printf("Usage: ./project1 infile outfile\n");
		return 0;
	}
	importData(argv[1]);
	for(unsigned int i=0; i<T; i++){
		unsigned int inf_daily = infected.size();
		for(unsigned int j=0; j<inf_daily;j++){
			Node* n = infected.front();
			infected.pop();
			infecting(n);
		}
	}
	for(unsigned int j=0; j<cities.size();j++){
		if(!cities[j].isInfected && !cities[j].visited)
		{
			state++;
			dfs(cities[j]);
		}
	}

	ofstream writer(argv[2]);
	writer<<state<<endl;
}
