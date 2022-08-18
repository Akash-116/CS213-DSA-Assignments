// Algos should be O(m+n). All four.

#include <bits/stdc++.h>
// #include <iostream>
// #include <unordered_set>
// #include <set>
// #include <vector>
// #include <list>
// #include <stack>
// #include <hash>
using namespace std;


struct hash_pair{
	size_t operator()(const pair<int, int> &p) const{
		hash<int> hasher;
		auto hash1 = hasher(p.first);
		auto hash2 = hasher(p.second);
		return hash1^hash2;
	}
};


vector<unordered_set<int>> inedge;
vector<unordered_set<int>> outedge;
// vector<unordered_set> revinedge;
// vector<unordered_set> revoutedge;

int n,m,op;


void func0(){
	// Assuming that the graph is strongly connected...
	// we construct dfs on the tree and in the reverse tree... 
	int r = 0;
	unordered_set<pair<int, int>, hash_pair> answer_egde;

	bool visited[n];
	for(int i=0; i<n; i++) visited[i]=false;

	// starting dfs on normal graph.
	stack<int> pending;
	pending.push(r);

	while(!pending.empty()){

		r = pending.top(); pending.pop();

		if(!visited[r]){
			visited[r] = true;

			for(auto i = outedge[r].begin(); i!= outedge[r].end(); i++){
				static int child;
				child = *i;
				if(!visited[child]) {
					answer_egde.insert(pair<int, int> (r,child));
					pending.push(child);
				}
			}
		}

	}

	// cout << answer_egde.size()<<endl;

	//DFS in reverse graph.
	r = 0; 

	for(int i=0; i<n; i++) visited[i]=false;
	pending.push(r);

	while(!pending.empty()){

		r = pending.top(); pending.pop();

		if(!visited[r]){
			visited[r] = true;
			for(auto i = inedge[r].begin(); i!= inedge[r].end(); i++){
				static int child;
				child = *i;
				if(!visited[child]) {
					answer_egde.insert(pair<int, int> (child, r));
					pending.push(child);
				}
			}
		}

	}

	cout << answer_egde.size()<<endl;

	for(auto p = answer_egde.begin(); p!= answer_egde.end(); p++){
		cout << p->first <<" " << p->second << endl; 
	}


}

void func1(){
	cout<<"Func1 is incomplete";
}

void func2(){
	cout<<"Func2 is incomplete";
	
}

void func3(){
	cout<<"Func3 is incomplete";
	
}





int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// int n, m, op;
	cin >> n >> m >> op;

	inedge.resize(n);
	outedge.resize(n);

	for(int i=0; i<m; i++){
		static int first, second;
		cin >> first >> second;
		outedge[first].insert(second);
		inedge[second].insert(first);
	// cout << "check" <<endl;

	}

	switch(op){
		case 0:
			func0();
			break;
		case 1:
			func1();
			break;
		case 2:
			func2();
			break;
		case 3:
			func3();
			break;
	}




}