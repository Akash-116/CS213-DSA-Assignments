// for directed acyclic graph.
// can be having many components


#include <bits/stdc++.h>
using namespace std;


bool sinknotfound;

vector<unordered_set<int>> inedge;
vector<unordered_set<int>> outedge;
int n,m;
vector<bool> marked;

int i=-1;
int v, w;
int p = -1;

unordered_set<int> sources;
unordered_set<int> sinks;
vector<int> x_arr;
unordered_set<int> unmarked_sources;
unordered_set<int> unmarked_sinks;
vector<int> status;
//status = 1 means source,
//status = 2 means sink,
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




int main(){

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// int n, m, op;
	cin >> n >> m;

	inedge.resize(n);
	outedge.resize(n);
	marked.resize(n);
	status.resize(n);
	ordered_node.resize(n);
	for(int qw = 0; qw < n; qw++){
		marked[qw] = false;
		ordered_node[qw] = false;
		status[qw] = 4;
	} 

	for(int iq=0; iq<m; iq++){
		static int first, second;
		cin >> first >> second;
		outedge[first].insert(second);
		inedge[second].insert(first);
	// cout << "check" <<endl;

	}

	for(int iq=0; iq<n; iq++)
	{
		if(outedge[iq].empty() && inedge[iq].empty()){
			x_arr.push_back(iq);
			status[iq] = 3;

		} 
		else if(!outedge[iq].empty() && inedge[iq].empty())
		{
			// cout << "sources\n";
			// cout << iq << endl;
			sources.insert(iq);
			unmarked_sources.insert(iq);
			status[iq] = 1;	
		}
		else if(outedge[iq].empty() && !inedge[iq].empty())
		{
			sinks.insert(iq);
			unmarked_sinks.insert(iq);
			status[iq] = 2;	
		}
	}
	int s,t,q;
	s = sources.size();
	t = sinks.size();
	q = x_arr.size();

	// cout << "\nprinting the source array of sources   ";
	// for(int vq : unmarked_sources ) cout << vq << " ";

	// cout << "\nprinting the sinks array of sinks   ";
	// for(int wq : unmarked_sinks ) cout << wq << " ";



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


	// cout << "\nprinting the v_arr array of sources   ";
	// for(int vq : v_arr ) cout << vq << " ";

	// cout << "\nprinting the w_arr array of sinks   ";
	// for(int wq : w_arr ) cout << wq << " ";



	cout << "P is  : "<<p << endl;

	int count = 0 ;
	cout << "count calculated via direct  :  " ;
	cout << max(s,t) + q<<endl;


	for(int x : sources)
	{
		cout << "a" << endl;
		if(!ordered_node[x]) v_arr.push_back(x);
	}
	for(int x : sinks)
	{
		if(!ordered_node[x]) w_arr.push_back(x);
	}



	////////////////////cout-ing edges needed//////////////

	for(int ind =1; ind < p; ind ++)
	{	
		count++;
		cout << w_arr[ind-1] << " " << v_arr[ind]<<endl;

	}



	if(s <= t){
		// cout << "declared that s < t" << endl;
		for(int idx = p; idx < s; idx++)
		{
			count++;
			cout << w_arr[idx] << " " << v_arr[idx] << endl;
		}



		if(q==0 && s==t)
		{
			cout << w_arr[p-1] << " " << v_arr[0] << endl;
			count++;
		}

		else if(q==0 && s<t)
		{
			cout << w_arr[p-1] << " " << w_arr[s] << endl; count++;

			for(int idx = s; idx < t-1 ; idx++)
			{
				cout << w_arr[idx] << " " << w_arr[idx+1] << endl; count++;
			}
			cout << w_arr[t-1] << " " << v_arr[0] << endl; count++;
		}


		else if(q!=0)
		{
			cout << w_arr[p-1] << " " << w_arr[s] << endl; count++;

			for(int idx = s; idx < t-1; idx++ )
			{
				cout << w_arr[idx] << " " << w_arr[idx+1] << endl; count++;
			}

			cout << w_arr[t-1] << " " << x_arr[0] << endl; count++;

			for(int idx = 0; idx < q-1; idx++)
			{
				cout << x_arr[idx] << " " << x_arr[idx+1] << endl; count++;
			}

			cout << x_arr[q-1] << " " << v_arr[0] << endl; count ++;

		}
	}

	else
	{
		cout << "declared that s > t\n";
		for(int idx = p; idx < t; idx++)
		{
			count++;
			cout << w_arr[idx] << " " << v_arr[idx] << endl;
		}

		if(q==0)
		{
			cout << w_arr[p-1] << " " << v_arr[t] << endl; count++;

			for(int idx = t; idx < s-1 ; idx++)
			{
				cout << v_arr[idx] << " " << v_arr[idx+1] << endl; count++;
			}

			cout << v_arr[s-1] << " " << v_arr[0] << endl; count++;
		}


		else
		{
			cout << w_arr[p-1] << " " << v_arr[t] << endl; count++;

			for(int idx = t; idx < s-1; idx++ )
			{
				cout << v_arr[idx] << " " << v_arr[idx+1] << endl; count++;
			}

			cout << v_arr[s-1] << " " << x_arr[0] << endl; count++;

			for(int idx = 0; idx < q-1; idx++)
			{
				cout << x_arr[idx] << " " << x_arr[idx+1] << endl; count++;
			}

			cout << x_arr[q-1] << " " << v_arr[0] << endl; count ++;

		}
	}


	cout << "count calculated via indirect  : " << count << endl;




}


