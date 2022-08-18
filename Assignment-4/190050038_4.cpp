#include <bits/stdc++.h>
// #include <iostream>
#define NIL -1 
using namespace std; 

unordered_map<int, int> ttinv;	
unordered_map<int, int> tt;


struct hash_pair{
	size_t operator()(const pair<int, int> &p) const{
		hash<int> hasher;
		auto hash1 = hasher(p.first);
		auto hash2 = hasher(p.second);
		return hash1^hash2;
	}
};

vector<unordered_set<int>> inedge11;
vector<unordered_set<int>> outedge11;

int n11,m11,op11;


struct part2{

	bool sinknotfound;
	vector<unordered_set<int>> inedge;
	vector<unordered_set<int>> outedge;
	vector<bool> marked;

	int n,m;
	int i = -1;
	int v, w;
	int p = -1;

	unordered_set<int> sources;
	unordered_set<int> sinks;
	vector<int> x_arr;
	unordered_set<int> unmarked_sources;
	unordered_set<int> unmarked_sinks;
	vector<int> status;
	//status = 1 means source, //status = 2 means sink,
	//status = 3 means isolate,
	//status = 4 means richDude,

	vector<bool> ordered_node;
	//ordered is 1 if, node is inside the sorting, else 0


	vector<int> v_arr;
	vector<int> w_arr;


	void search(int x){
		if (!marked[x])
		{
			if(status[x] == 2)
			{
				w = x;
				sinknotfound = false;
			}
			marked[x] = true;
			if(status[x] == 2 ) unmarked_sinks.erase(x);
			else if(status[x]==1) unmarked_sources.erase(x);

			for( int y : outedge[x]){
				if(sinknotfound) search(y);
			}
		}
	}

	void set_n(int n){
		this->n = n; 
		inedge.resize(n);
		outedge.resize(n);
		marked.resize(n);
		ordered_node.resize(n);
		status.resize(n);

		for(int qw = 0; qw < n; qw++){
			marked[qw] = false;
			ordered_node[qw] = false;
			status[qw] = 4;
		} 

		// this->m = m;
	}

	void add_edge(int first, int second){
		outedge[first].insert(second);
		// cout << "vasd"<<endl;
		inedge[second].insert(first);
	}
	 // void pass_ttinv (map<int, int> &ttinv){
	 // 	this->ttinv = &ttinv;
	 // }

	int main_func(){
		// int n,m; cin >> n >> m;
		if(n == 1) {cout << 0 << endl; return 0;}

		 // cout << "main_func called " << endl;
		
		// for(int iq=0; iq<m; iq++){
		// 	static int first, second;
		// 	cin >> first >> second;
		// 	outedge[first].insert(second);
		// 	inedge[second].insert(first);
		// }

		int s=0,t=0,q=0;

		for(int iq=0; iq<n; iq++)
		{
			if(outedge[iq].empty() && inedge[iq].empty())
			{
				x_arr.push_back(iq);
				status[iq] = 3;
				q++;
			} 
			else if(!outedge[iq].empty() && inedge[iq].empty())
			{
				unmarked_sources.insert(iq);
				status[iq] = 1;	
				s++;
			}
			else if(outedge[iq].empty() && !inedge[iq].empty())
			{
				unmarked_sinks.insert(iq);
				status[iq] = 2;	
				t++;
			}
		}

		while (!unmarked_sources.empty())
		{
			v = *(unmarked_sources.begin());
			w = -1;
			sinknotfound = true;
			search(v);
			if (w!=-1) 
			{
				i = i+1;
				v_arr.push_back(v);
				ordered_node[v] = true; 
				w_arr.push_back(w); 
				ordered_node[w] = true; 
			}
		}
		p = i+1; //p is the length of common sequence. 

		// cout << "P is  : "<<p << endl;


		cout << max(s,t) + q << endl;
		

		for(int item=0; item<n; item++)
		{
			if(status[item] == 1 && !ordered_node[item]) v_arr.push_back(item);
			if(status[item] == 2 && !ordered_node[item]) w_arr.push_back(item);
		}

		////////////////////cout-ing edges needed//////////////

		for ( int ind =1; ind < p; ind++ )
		{	
			cout << ttinv[w_arr[ind-1]] << " " << ttinv[v_arr[ind]]<<endl;
		}

		if(s==0 && t==0)
		{
				for(int idx = 0; idx < q-1; idx++)
				{
					cout << ttinv[x_arr[idx]] << " " << ttinv[x_arr[idx+1]] << endl; ;
				}
				cout << ttinv[x_arr[q-1]] << " " << ttinv[x_arr[0]] << endl; ; 
		}

	//////////////////////////////main theme////////////////////////
		else if(s <= t){
			for(int idx = p; idx < s; idx++)
			{
				cout << ttinv[w_arr[idx]] << " " << ttinv[v_arr[idx]] << endl;
			}

			if(q==0 && s==t)
			{
				cout << ttinv[w_arr[p-1]] << " " << ttinv[v_arr[0]] << endl;
			}

			else if(q==0 && s<t)
			{
				cout << ttinv[w_arr[p-1]] << " " << ttinv[w_arr[s]] << endl; ;
				for(int idx = s; idx < t-1 ; idx++)
				{
					cout << ttinv[w_arr[idx]] << " " << ttinv[w_arr[idx+1]] << endl; ;
				}
				cout << ttinv[w_arr[t-1]] << " " << ttinv[v_arr[0]] << endl; ;
			}

			else if(q!=0)
			{
				if(s==t)
				{
					cout << ttinv[w_arr[p-1]] << " " << ttinv[x_arr[0]] <<  endl; ;

					for(int idx = 0; idx < q-1; idx++)
					{
						cout << ttinv[x_arr[idx]] << " " << ttinv[x_arr[idx+1]] << endl; ;
					}

					cout << ttinv[x_arr[q-1]] << " " << ttinv[v_arr[0]] << endl; ;
				}	
				else
				{
					cout << ttinv[w_arr[p-1]] << " " << ttinv[w_arr[s]] << endl; ;
					for(int idx = s; idx < t-1; idx++ )
					{
						cout << ttinv[w_arr[idx]] << " " << ttinv[w_arr[idx+1]] << endl; ;
					}
					cout << ttinv[w_arr[t-1]] << " " << ttinv[x_arr[0]] << endl; ;
					for(int idx = 0; idx < q-1; idx++)
					{
						cout << ttinv[x_arr[idx]] << " " << ttinv[x_arr[idx+1]] << endl; ;
					}
					cout << ttinv[x_arr[q-1]] << " " << ttinv[v_arr[0]] << endl; ;
				}
			}
		}
		else // i.e. s > t .hence, s !=0
		{
			for(int idx = p; idx < t; idx++)
			{
				cout << ttinv[w_arr[idx]] << " " << ttinv[v_arr[idx]] << endl;
			}
			if(q==0)
			{
				cout << ttinv[w_arr[p-1]] << " " << ttinv[v_arr[t]] << endl; ;
				for(int idx = t; idx < s-1 ; idx++)
				{
					cout << ttinv[v_arr[idx]] << " " << ttinv[v_arr[idx+1]] << endl; ;
				}
				cout << ttinv[v_arr[s-1]] << " " << ttinv[v_arr[0]] << endl; ;
			}
			else
			{
				cout << ttinv[w_arr[p-1]] << " " << ttinv[v_arr[t]] << endl; ;
				for(int idx = t; idx < s-1; idx++ )
				{
					cout << ttinv[v_arr[idx]] << " " << ttinv[v_arr[idx+1]] << endl; ;
				}
				cout << ttinv[v_arr[s-1]] << " " << ttinv[x_arr[0]] << endl; ;
				for(int idx = 0; idx < q-1; idx++)
				{
					cout << ttinv[x_arr[idx]] << " " << ttinv[x_arr[idx+1]] << endl; ;
				}
				cout << ttinv[x_arr[q-1]] << " " << ttinv[v_arr[0]] << endl; ;
			}
		}

	return 0;

	}


};


struct Graph 
{ 
	int V; // No. of vertices 
	list<int> *adj; // A dynamic array of adjacency lists
	int* scc_head; //an array to save the scc heads of respective node.
	unordered_set<int> scc_heads; //a list of ssc_heads
	unordered_set<int> *in_scchead; //will be of size V but only see the head nodes
	unordered_set<int> *out_scchead;//will be of size V but only see the head nodes

	// A Recursive DFS based function used by SCC() 
	void SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]); 

	Graph(int V); // Constructor 
	void addEdge(int v, int w); // function to add an edge to graph 
	void SCC(); // prints strongly connected components 
	void build_SCC_graph();
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
	scc_head = new int[V]; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); 
	//even though this is a directed graph, all edges are captured by just one adj_list 
} 

void Graph::SCCUtil(int u, int disc[], int low[], stack<int> *st, 
					bool stackMember[]) 
{ 
	static int time = 0; 

	disc[u] = low[u] = ++time; 
	st->push(u); 
	stackMember[u] = true; 

	for (auto v : adj[u]) 
	{ 
		if (disc[v] == -1) 
		{ 
			SCCUtil(v, disc, low, st, stackMember); 
			low[u] = min(low[u], low[v]); 
		} 
		else if (stackMember[v] == true) 
		{
			low[u] = min(low[u], disc[v]); 
		}
	} 
	int w = 0; // To store stack extracted vertices 
	if (low[u] == disc[u]) 
	{ 
		while (st->top() != u) 
		{ 
			w = (int) st->top(); 
			// cout << w << " "; 
			stackMember[w] = false; 
			st->pop();
			scc_head[w] = u; 
		} 
		w = (int) st->top(); 
		// cout << w << "\n"; 
		stackMember[w] = false; 
		st->pop(); 
		scc_head[w] = u; 
		scc_heads.insert(u); 
	} 
} 

void Graph::SCC() 
{ 
	int *disc = new int[V]; 
	int *low = new int[V]; 
	bool *stackMember = new bool[V]; 
	stack<int> *st = new stack<int>(); 
	for (int i = 0; i < V; i++) 
	{ 
		disc[i] = NIL; 
		low[i] = NIL; 
		stackMember[i] = false; 
	} 
	for (int i = 0; i < V; i++) 
		if (disc[i] == NIL) 
			SCCUtil(i, disc, low, st, stackMember); 
} 


void Graph::build_SCC_graph(){
	if(scc_heads.size() == 1) //when the given graph is strongly connected in itself.
	{
		cout << 0 << endl;
		return;
	}

	in_scchead = new unordered_set<int>[V]; //TO STORE edges in the headGraph
	out_scchead = new unordered_set<int>[V]; //to STORE edges in the headGraph

	for(int u=0; u < V; u++)  //reading all graph edges, to bulid scc graph
		for(auto v : adj[u] )
		{
			int a =scc_head[u];
			int b =scc_head[v];
			if(a==b) continue;
			out_scchead[a].insert(b);
			in_scchead[b].insert(a);
		}

	part2 ANS;
	ANS.set_n(scc_heads.size());


	int iqwe =0;

	for(int h: scc_heads)
	{
		tt[h]= iqwe;
		ttinv[iqwe] = h;
		iqwe++;
	}

	for(int h: scc_heads)
	{
		static int a1,b1;
		a1 = tt[h];
		for(int k: out_scchead[h])
		{
			b1 = tt[k];

			// cout << "Hey ahndsome"<<endl;
			ANS.add_edge(a1, b1);
		}
	}

	ANS.main_func();

}



void func0(){
	// Assuming that the graph is strongly connected...
	// we construct dfs on the tree and in the reverse tree... 
	int r = 0;
	// unordered_set< pair<int, int>, hash_pair > answer_egde;

	bool visited[n11];
	for(int i=0; i<n11; i++) visited[i]=false;
		
	unordered_set<int> new_adj[n11];

	// starting dfs on normal graph.
	stack<int> pending;
	pending.push(r);

	while(!pending.empty()){

		r = pending.top(); pending.pop();

		if(!visited[r]){
			visited[r] = true;

			for(auto i = outedge11[r].begin(); i!= outedge11[r].end(); i++){
				static int child;
				child = *i;
				if(!visited[child]) {
					new_adj[r].insert(child);
					// answer_egde.insert(pair<int, int> (r,child));
					pending.push(child);
				}
			}
		}

	}

	// cout << answer_egde.size()<<endl;

	//DFS in reverse graph.
	r = 0; 

	for(int i=0; i<n11; i++) visited[i]=false;
	pending.push(r);

	while(!pending.empty()){

		r = pending.top(); pending.pop();

		if(!visited[r]){
			visited[r] = true;
			for(auto i = inedge11[r].begin(); i!= inedge11[r].end(); i++){
				static int child;
				child = *i;
				if(!visited[child]) {
					new_adj[child].insert(r);
					// answer_egde.insert(pair<int, int> (child, r));
					pending.push(child);
				}
			}
		}

	}

	int count1 =0;
	for(int i=0; i<n11; i++) count1+=new_adj[i].size();

	cout << count1 << endl;
	for(int i=0; i<n11; i++)
		for( auto p = new_adj[i].begin(); p!= new_adj[i].end(); p++){
			cout << *p <<" " << *p << endl; 
		}


}

int main() 
{ 
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n11 >> m11 >> op11;

	switch(op11){
		case 0:

			inedge11.resize(n11);
			outedge11.resize(n11);

			for(int i=0; i<m11; i++){
				static int first, second;
				cin >> first >> second;
				outedge11[first].insert(second);
				inedge11[second].insert(first);
			// cout << "check" <<endl;
			}
			func0();
			break;
		case 1:
			cout << 0 << endl;
			break;
		case 2:
			cout << "impossible" << endl;
			break;
		case 3:
			Graph g2(n11);
			for(int i=0; i<m11; i++)
			{
				static int first, second;
				cin >> first >> second;
				g2.addEdge(first, second);
			}
			g2.SCC();
			g2.build_SCC_graph();
			break;
	}

	return 0; 
} 
