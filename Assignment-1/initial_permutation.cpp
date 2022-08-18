#include<vector>
#include<iostream>
using namespace std;


int gcd(int a, int b)  
{  
    if (a == 0) 
        return b;  
    return gcd(b % a, a);  
}  
  
// Function to return LCM of two numbers  
int lcm(int a, int b)  
{  
    return (a*b)/gcd(a, b);  
}  


class permutation{

	int *a;  //equal to some new int[n]
	int n;
	vector<int> * loops; //array of vectors.
	vector<vector<int>> size_count;

	long long int idty_index=1;

	void idty_index(){
	for(int i=1; i<size_count.size(); i++){
		if(size_count[i].size()>0)idty_index=lcm(idty_index,size_count[i].size());
	}

	void form_loops(){
		size_count.clear();
		vector<vector<int>> a(n+1);
		size_count=a;		

		loops = new vector<int> [n];
		for(int i=0; i<n; i++){
			loops[i].push_back(i);
			int next = a[i];
			while(next!=i){
				if(next<i){
					loops[i].clear();
					break;
				}
				loops[i].push_back(next);
				next=a[next];
			}
			size_count[loop[i].size()].push_back(i);
		}
		this->idty_index();
	return;
	}

public:
	permutation(int n, int a[]) {  //i<=n<=100
		this->n = n;
		int *b = new int[n];
		for (int i=0; i<n; i++)
			b[i]=a[i];
		this->a = b;
		this->form_loops();
	}

	permutation (permutation const &q){
		n=q.n;
		int *b = new int[n];
		for (int i=0; i<n; i++)
			b[i]=q.a[i];
		a=b;
		this->form_loops();
	}

	~permutation(){
		delete a; 
		delete loops;  //no memory leak da.
	}

	permutation const operator= (permutation const &q){ //q might hav different size. account for it!!
		n=q.n;
		delete a;

		int b*= new int[n];
		for (int i=0; i<n; i++)
			b[i]=q.a[i];
		a=b;
		this->form_loops();
		return *this;
	}

	int size() const{
		return n;
	}

	int* to_array() const{
		return a;
	}

	permutation const operator-() const{ //given inverse function
		int b[n];
		for(int i=0; i<n; i++) 	
			b[a[i]]=i;
		class permutation inverse_permutation(n,b);
		return I_permutation;
	}

	permutation const operator* (permutation const &q) const{
		int b[n];
		for (int i=0; i<n; i++)
			b[i]=a[q.a[i]];
		class permutation r(n,b);
		return r;	
	}

	permutation const square_root() const{ //return identity p(i)=i if no squareroot 
		int b[n];
		for (int i=0; i<n; i++)b[i]=i;
		permutation IDENTITY(n,b);

		for(int SIZE=2; SIZE<n; SIZE+=2){
			if(size_count[SIZE].size()%2) return IDENTITY;
		}



		int b[n];
		// class permutation p(*this);//maybe useless //p is temporary.
		
		for(int lp_size=1; lp_size<n+1; lp_size++){
			
			if(lp_size%2){
				for(int index=0; index<size_count[lp_size].size(); index++){
					int lp=size_count[lp_size][index];
					for(int lp_index=0; lp_index < lp_size-1; lp_index++){
						b[loop[lp][index]]=loop[lp][index+1];
					}
						b[loop[lp][lp_size-1]]=loop[lp][0];
				}
			}

			else{
				for(int index=0; index<size_count[lp_size].size(); index+=2){
					int lp1=size_count[lp_size][index];
					int lp2=size_count[lp_size][index+1];
					for(int lp_index=0; lp_index < lp_size-1; lp_index++){
						b[loop[lp1][index]]=loop[lp2][index];
						b[loop[lp2][index]]=loop[lp1][index+1];
					}
						b[loop[lp1][lp_size-1]]=loop[lp2][lp_size-1];
						b[loop[lp2][lp_size-1]]=loop[lp1][0];
				}
			}
		} 

		permutation f(n,b);
		return f;
	}

	permutation const operator^ (long long int power) const{ //mind the long long!

		int b[n];
		for (int i=0; i<n; i++)b[i]=i;
		permutation IDENTITY(n,b);

		if(power==0) return IDENTITY; 

		power=power%idty_index;

		return p*(p^power-1);
	}

	bool is_power(permutation const &q) const{


	}

	int log(permutation const &q) const{ //find smallest value i, if it exists. Compute to modulo 10^9+7.
											// reutrn -1, if no such i.

	}



};