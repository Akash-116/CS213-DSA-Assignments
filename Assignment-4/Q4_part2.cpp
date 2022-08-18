
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
	map<int, int> *ttinv;
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

	void set_n(int n){
		this->n = n; 
		// this->m = m;
	}

	void add_edge(int first, int second){
		outedge[first].insert(second);
		inedge[second].insert(first);
	}
	 // void pass_ttinv (map<int, int> &ttinv){
	 // 	this->ttinv = &ttinv;
	 // }

	int main_func(){
		// int n,m; cin >> n >> m;
		if(n == 1) {cout << 0 << endl; return 0;}

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
			cout << (*ttinv)[w_arr[ind-1]] << " " << (*ttinv)[v_arr[ind]]<<endl;
		}

		if(s==0 && t==0)
		{
				for(int idx = 0; idx < q-1; idx++)
				{
					cout << (*ttinv)[x_arr[idx]] << " " << (*ttinv)[x_arr[idx+1]] << endl; ;
				}
				cout << (*ttinv)[x_arr[q-1]] << " " << (*ttinv)[x_arr[0]] << endl; ; 
		}

	//////////////////////////////main theme////////////////////////
		else if(s <= t){
			for(int idx = p; idx < s; idx++)
			{
				cout << (*ttinv)[w_arr[idx]] << " " << (*ttinv)[v_arr[idx]] << endl;
			}

			if(q==0 && s==t)
			{
				cout << (*ttinv)[w_arr[p-1]] << " " << (*ttinv)[v_arr[0]] << endl;
			}

			else if(q==0 && s<t)
			{
				cout << (*ttinv)[w_arr[p-1]] << " " << (*ttinv)[w_arr[s]] << endl; ;
				for(int idx = s; idx < t-1 ; idx++)
				{
					cout << (*ttinv)[w_arr[idx]] << " " << (*ttinv)[w_arr[idx+1]] << endl; ;
				}
				cout << (*ttinv)[w_arr[t-1]] << " " << (*ttinv)[v_arr[0]] << endl; ;
			}

			else if(q!=0)
			{
				if(s==t)
				{
					cout << (*ttinv)[w_arr[p-1]] << " " << (*ttinv)[x_arr[0]] <<  endl; ;

					for(int idx = 0; idx < q-1; idx++)
					{
						cout << (*ttinv)[x_arr[idx]] << " " << (*ttinv)[x_arr[idx+1]] << endl; ;
					}

					cout << (*ttinv)[x_arr[q-1]] << " " << (*ttinv)[v_arr[0]] << endl; ;
				}	
				else
				{
					cout << (*ttinv)[w_arr[p-1]] << " " << (*ttinv)[w_arr[s]] << endl; ;
					for(int idx = s; idx < t-1; idx++ )
					{
						cout << (*ttinv)[w_arr[idx]] << " " << (*ttinv)[w_arr[idx+1]] << endl; ;
					}
					cout << (*ttinv)[w_arr[t-1]] << " " << (*ttinv)[x_arr[0]] << endl; ;
					for(int idx = 0; idx < q-1; idx++)
					{
						cout << (*ttinv)[x_arr[idx]] << " " << (*ttinv)[x_arr[idx+1]] << endl; ;
					}
					cout << (*ttinv)[x_arr[q-1]] << " " << (*ttinv)[v_arr[0]] << endl; ;
				}
			}
		}
		else // i.e. s > t .hence, s !=0
		{
			for(int idx = p; idx < t; idx++)
			{
				cout << (*ttinv)[w_arr[idx]] << " " << (*ttinv)[v_arr[idx]] << endl;
			}
			if(q==0)
			{
				cout << (*ttinv)[w_arr[p-1]] << " " << (*ttinv)[v_arr[t]] << endl; ;
				for(int idx = t; idx < s-1 ; idx++)
				{
					cout << (*ttinv)[v_arr[idx]] << " " << (*ttinv)[v_arr[idx+1]] << endl; ;
				}
				cout << (*ttinv)[v_arr[s-1]] << " " << (*ttinv)[v_arr[0]] << endl; ;
			}
			else
			{
				cout << (*ttinv)[w_arr[p-1]] << " " << (*ttinv)[v_arr[t]] << endl; ;
				for(int idx = t; idx < s-1; idx++ )
				{
					cout << (*ttinv)[v_arr[idx]] << " " << (*ttinv)[v_arr[idx+1]] << endl; ;
				}
				cout << (*ttinv)[v_arr[s-1]] << " " << (*ttinv)[x_arr[0]] << endl; ;
				for(int idx = 0; idx < q-1; idx++)
				{
					cout << (*ttinv)[x_arr[idx]] << " " << (*ttinv)[x_arr[idx+1]] << endl; ;
				}
				cout << (*ttinv)[x_arr[q-1]] << " " << (*ttinv)[v_arr[0]] << endl; ;
			}
		}

	return 0;

	}


};