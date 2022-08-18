#include <iostream>

long long int z=1;

struct quad_tree{
	int value;
	int height;

	struct quad_tree* topleft=NULL; 
	struct quad_tree* topright=NULL;
	struct quad_tree* bottomright=NULL;
	struct quad_tree* bottomleft=NULL;

	quad_tree(int n){
		value=0;
		height=n;
	}

	quad_tree(int x,int n){
		value=x;
		height=n;
	}

	~quad_tree(){
		if(topleft!=NULL){
			delete topleft;
			delete bottomleft;
			delete topright;
			delete bottomright;
		}
	}

	quad_tree(quad_tree const &Q){
		value=Q.value;
		height=Q.height;
		if(Q.topleft!=NULL){
			topleft=new quad_tree(*Q.topleft);
			topright=new quad_tree(*Q.topright);
			bottomleft=new quad_tree(*Q.bottomleft);
			bottomright=new quad_tree(*Q.bottomright);
		}
	}

	void set(int x1, int y1, int x2, int y2, int b){

		if(topleft==NULL){
			if(value!=b){
				int k=(1<<(height-1))-1;
				if( (x1==0  &&  x1==2*k+1  &&  y1==0  &&  y2==2*k+1) || height==0 ){
					value=b;
				}			
				else{
					topleft=new quad_tree(value,height-1);
					topright=new quad_tree(value,height-1);
					bottomleft=new quad_tree(value,height-1);
					bottomright=new quad_tree(value,height-1);
					this->set(x1,y1,x2,y2,b);
				}
			}
		}
		else{
			int k=(1<<(height-1))-1;
			if(x1==0  &&  x1==2*k+1  &&  y1==0  &&  y2==2*k+1){
				value=b;
				delete topleft;
				delete bottomleft;
				delete topright;
				delete bottomright;
				topright=NULL;
				topleft=NULL;
				bottomright=NULL;
				bottomleft=NULL;
			}
			else if(x1<=k && x2<=k && y1<=k && y2<=k){
				topleft->set(x1,y1,x2,y2,b);
				this->check();
			}
			else if(x1<=k && x2>k && y1<=k && y2<=k){
				topleft->set(x1,y1,k,y2,b);
				topright->set(0,y1,x2-k-1,y2,b);
				this->check();
			}
			else if(x1>k && x2>k && y1<=k && y2<=k){
				topright->set(x1-k-1,y1,x2-k-1,y2,b);
				this->check();
			}
			else if(x1<=k && x2<=k && y1<=k && y2>k){
				topleft->set(x1,y1,x2,k,b);
				bottomleft->set(x1,0,x2,y2-k-1,b);
				this->check();
			}
			else if(x1<=k && x2>k && y1<=k && y2>k){
				topleft->set(x1,y1,k,k,b);
				topright->set(0,y1,x2-k-1,k,b);
				bottomleft->set(x1,0,k,y2-k-1,b);
				bottomright->set(0,0,x2-k-1,y2-k-1,b);
				this->check();
			}
			else if(x1>k && x2>k && y1<=k && y2>k){
				topright->set(x1-k-1,y1,x2-k-1,k,b);
				bottomright->set(x1-k-1,0,x2-k-1,y2-k-1,b);
				this->check();
			}
			else if(x1<=k && x2<=k && y1>k && y2>k){
				bottomleft->set(x1,y1-k-1,x2,y2-k-1,b);
				this->check();
			}
			else if(x1<=k && x2>k && y1>k && y2>k){
				bottomleft->set(x1,y1-k-1,k,y2-k-1,b);
				bottomright->set(0,y1-k-1,x2-k-1,y2-k-1,b);
				this->check();
			}
			else if(x1>k && x2>k && y1>k && y2>k){
				bottomright->set(x1-k-1,y1-k-1,x2-k-1,y2-k-1,b);
				this->check();
			}
		}
	}

	int get(int x1, int y1){
		if(topleft==NULL){
			return value;
		}
		else{
			int k=(1<<(height-1))-1;
			if(x1<=k && y1<=k){
				return topleft->get(x1,y1);
			}
			else if(x1>k && y1<=k){
				return topright->get(x1-k-1,y1);
			}
			else if(x1<=k && y1>k){
				return bottomleft->get(x1,y1-k-1);
			}
			else {
				return bottomright->get(x1-k-1,y1-k-1);
			}
		}
	}

	int size() const{
		return height;
	}

	void intersect(quad_tree const &Q){
		if(topleft==NULL && Q.topleft==NULL){
			value=(value)*(Q.value);
		}
		else if(topleft==NULL && Q.topleft!=NULL){
			if(value==1){
				value=Q.value;
				topleft=new quad_tree(*(Q.topleft));
				topright=new quad_tree(*Q.topright);
				bottomleft=new quad_tree(*Q.bottomleft);
				bottomright=new quad_tree(*Q.bottomright);
			}
		}
		else if(topleft!=NULL && Q.topleft==NULL){
			if(Q.value==0){
				delete topleft;
				delete bottomleft;
				delete topright;
				delete bottomright;
				topright=NULL;
				topleft=NULL;
				bottomright=NULL;
				bottomleft=NULL;
				value=Q.value;
			}
		}
		else {
			topleft->intersect(*(Q.topleft));
			topright->intersect(*(Q.topright));
			bottomleft->intersect(*(Q.bottomleft));
			bottomright->intersect(*(Q.bottomright));
			this->check();
		}
	}

	void overlap(quad_tree &Q){
		if(topleft==NULL && Q.topleft==NULL){
			value=value+Q.value-(value*Q.value);
			
		}
		else if(topleft==NULL && Q.topleft!=NULL){
			if(value==0){
				value=Q.value;
				topleft=new quad_tree(*(Q.topleft));
				topright=new quad_tree(*Q.topright);
				bottomleft=new quad_tree(*Q.bottomleft);
				bottomright=new quad_tree(*Q.bottomright);
			}
		}
		else if(topleft!=NULL && Q.topleft==NULL){
			if(Q.value==1){
				delete topleft;
				delete bottomleft;
				delete topright;
				delete bottomright;
				topright=NULL;
				topleft=NULL;
				bottomright=NULL;
				bottomleft=NULL;
				value=Q.value;
			}
		}
		else{
			topleft->overlap(*Q.topleft);
			topright->overlap(*Q.topright);
			bottomleft->overlap(*Q.bottomleft);
			bottomright->overlap(*Q.bottomright);
			this->check();
		}
	}

	void complement(){
		if(topleft==NULL){
			value=1-value;
		}
		else{
			topleft->complement();
			topright->complement();
			bottomleft->complement();
			bottomright->complement();
		}
	}

	void resize(int m){
		if(m>height){
			height=m;
			if(topleft!=NULL){
				topleft->resize(m-1);
				topright->resize(m-1);
				bottomleft->resize(m-1);
				bottomright->resize(m-1);
				this->check();
			}
		}
		else if(m<height){
			if(topleft==NULL){
				height=m;
			}
			else{
				if(m==0){
					long long int k = z<<(2*height);
					k=k/2;
					if(this->sum()>=k){
						value=1;
					}
					else{
						value=0;
					}
					height=m;
					delete topleft;
					delete bottomleft;
					delete topright;
					delete bottomright;
					topright=NULL;
					topleft=NULL;
					bottomright=NULL;
					bottomleft=NULL;
				}
				else{
					height=m;
					topleft->resize(m-1);
					topright->resize(m-1);
					bottomleft->resize(m-1);
					bottomright->resize(m-1);
					this->check();
				}
			}
		}
	}

	long long int sum(){
		if(topleft==NULL){
			if(value==0){
				return 0;
			}
			else{
				long long int k=z<<(2*height);
				return k;
			}
		}
		else{
			return topleft->sum()+topright->sum()+bottomleft->sum()+bottomright->sum();
		}
	}
	void check(){
		if(topleft->topleft==NULL && topright->topleft==NULL && bottomright->topleft==NULL && bottomleft->topleft==NULL){
			if(topleft->value==topright->value && topright->value==bottomleft->value && bottomleft->value==bottomright->value){
				this->value=topleft->value;
				delete topleft;
				delete bottomleft;
				delete topright;
				delete bottomright;
				topright=NULL;
				topleft=NULL;
				bottomright=NULL;
				bottomleft=NULL;
			}
		}
	}
};