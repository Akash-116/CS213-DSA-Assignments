#include<vector>
#include<iostream>
using namespace std;


long long int gcd(long long int a, long long int b)  
{  
    if (a == 0) 
        return b;  
    return gcd(b % a, a);  
}  
  
// Function to return LCM of two numbers  
long long int lcm(long long int a, long long int b)  
{  
    return (a*b)/gcd(a, b);  
}  



class permutation{

	int *a;  //equal to some new int[n]
	int n;
	vector<int> *loop;


	void form_loop(){
		loop = new vector<int> [n];
		for(int i=0; i<n; i++){
			loop[i].push_back(i);
			int next = a[i];
			while(next!=i){
				if(next<i){
					loop[i].clear();
					break;
				}
				loop[i].push_back(next);
				next=a[next];
			}
			// size_count[loop[i].size()].push_back(i);
		}
		// this->do_idty_index();
	 // cout<<"yipp"<<endl;
	return;
	}


public:
	permutation(int n, int a[]) {  //i<=n<=100
		this->n = n;
		int *b = new int[n];
		for (int i=0; i<n; i++)
			b[i]=a[i];
		this->a = b;
		form_loop();
	}

	permutation (permutation const &q){
		n=q.n;
		int *b = new int[n];
		for (int i=0; i<n; i++)
			b[i]=q.a[i];
		a=b;
		form_loop();
	}

	~permutation(){
		delete[] a; 
		delete[] loop;
		// cout << "deleted!";
	}

	permutation const operator= (permutation const &q){ //q might hav different size. account for it!!
		n=q.n;
		delete a;

		int *b = new int[n];
		for (int i=0; i<n; i++)
			b[i]=q.a[i];
		a=b;
		return *this;
		form_loop();
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
		return inverse_permutation;
	}

	permutation const operator* (permutation const &q) const{
		int b[n];
		for (int i=0; i<n; i++)
			b[i]=a[q.a[i]];
		class permutation r(n,b);
		return r;	
	}

	permutation const square_root() const{ //return identity p(i)=i if no squareroot 
		int bqw[n];
		for (int i=0; i<n; i++)bqw[i]=i;
		permutation IDENTITY(n,bqw);

	}

	permutation const operator^ (long long int power) const{ //mind the long long!

	}

	bool is_power(permutation const &q) const{


	}

	int log(permutation const &q) const{ //find smallest value i, if it exists. Compute to modulo 10^9+7.
											// reutrn -1, if no such i.

	}

	void print_perm() const{
		for(int i=0; i<n; i++){
			cout << a[i] << " ";
		}
		cout << endl;
		return;
	}


};


int main(){

	int a[]={1,0,2,4,5,3};
	permutation p(6,a);
	p.print_perm();
	permutation q=p*p;
	q.print_perm();

	permutation r=-p;
	r.print_perm();





}