#include "lex.h"

#define NUM_DROP 6
#define NUM_NORMAL 23
#define NUM_SPECI 2
#define SIZE 10


string drop[NUM_DROP] = {"$$", "$", "\!", "\,", "\quad", " "};

/*
\neq,\ne=>neq
\leq,\le=>le
\times,\cdot=>*
\pi=>pi
\vert=>|
\approx=>appr
*/ 
string normal[NUM_NORMAL]={"-", "+", "<", ">", "=", "\neq", "\leq", "\le", "\geq", "\ge", "\times", "^", "\approx", "\div", "\frac", "\cdot", "\pi", "\vert", "|", "{", "}", "(", ")"};
string speci[NUM_SPECI]={".", "\%"};
/*
some rules:
val+frac => val
(ab)c=a(bc).=>(a*b)*c=>a*(b*c).   judge if isn't the num, special treat.  
\cdot=>*
\pi=>val
*/


void HandleFrac(vector<Token> &vec, string &s, string number);
void SplitToTimes(vector<Token> &vec, string s);//ab=>a*b
void CreateToken(vector<Token> &vec, string s, TokenMeta met, int typ);//mt: 0:val 1:opr
void HandleString(string s, vector<Token> &vec);
int MatchWhere(string s, string match[], int len);//whether s start with one in string[]
int StartWith(string s, string head);//whether s start with head:yes-1,no-0
void TraverseDrop(string &s);//drop all-type useless
void DropAllMark(string &s, const string &mark);//drop one-type useless
void HandleVert(vector<Token> &vec, string &temp);
 
/*
define vector<Token> vec;
call HandleString(string s, vector<Token> &vec);
int main(){
	vector<Token> vec;
 	string test="$$ 1.2 + 50\% +a\cdotb +|123|  + \pi \div1 +5\frac{\frac{1}{2}}{11}  a\leqb$$ a^5 a(ab)c |123|  \times \vert123\vert"; 
//	string test="a(ab)c";
//	string test="\vert123\vert nihaoa";
 	HandleString(test,vec);
	for(int i=0;i<vec.size() ;i++){
		cout << i << " : "<< vec[i].value << endl;
	}
}
 */
 
 
//drop one-type useless
void DropAllMark(string &s, const string &mark){
    size_t nSize = mark.size();
    while(1){
        size_t pos = s.find(mark);
        if(pos == string::npos) //dont't find
        {
            return;
        }
        s.erase(pos,nSize);
    }
}

//drop all-type useless
void TraverseDrop(string &s){
	for(int i=0; i<NUM_DROP; i++){
		DropAllMark(s, drop[i]);
	}
}

//whether s start with head:yes-1,no-0
int StartWith(string s, string head){
	if(strncmp(s.c_str(), head.c_str(), head.length()) == 0)
	{
	 	return 1;
	}
	else{
		return 0;
	}
}

//whether s start with one in string[]
int MatchWhere(string s, string match[], int len){
	int i=0;	
	for(i; i<len; i++){
		if(StartWith(s, match[i])==1)
			return i;
	}
	if(i==len)
		return i;
}


void HandleString(string s, vector<Token> &vec){
	string temp=s; 
	TraverseDrop(temp);
	
	string number;
	string symbol;
	string point;
	
	while(temp.size()!=0){
			int ms=NUM_SPECI;
			int mn=NUM_NORMAL;
			
			while(temp.size()!=0 && temp.at(0)>=48 && temp.at(0)<=57){
			//	printf("%c\n",temp.at(0));
				number+=temp.at(0);
				temp.erase(0,1);	
			}
			
			//match number
			if(number.size()!=0){
				ms=MatchWhere(temp, speci, NUM_SPECI);
				// xx% or xx.xx
				if(ms<NUM_SPECI){
					if(speci[ms]=="\%"){
						point+="%";
						temp.erase(0, speci[ms].size() );
						
						point=number+point;
						CreateToken(vec, point, VAL, 17);
						
						point.clear();
					}	
					else if(speci[ms]=="."){
						point+=speci[ms];
						temp.erase(0, speci[ms].size() );
						
							
						while(temp.size()!=0 && temp.at(0)>=48 && temp.at(0)<=57){
						//	printf("%c\n",temp.at(0));
							point+=temp.at(0);
							temp.erase(0,1);	
						}
						point=number+point;
						CreateToken(vec, point, VAL, 17);
						
						point.clear();
					}	
				}
				else{
					
					//val+frac=>val
					mn=MatchWhere(temp, normal, NUM_NORMAL);
					if(mn<NUM_NORMAL && normal[mn]=="\frac"){
						temp.erase(0, normal[mn].size() );
						HandleFrac(vec, temp, number);
					}
					else{
						//just number
						CreateToken(vec, number, VAL, 17);
					}
				
				}
				number.clear();
				if(StartWith(temp, "(")){
					CreateToken(vec, "*", OP, 2);
				}
			}
			
			
			//match symbols:"\frac", "\cdot", "\pi"
			mn=MatchWhere(temp, normal, NUM_NORMAL);
			//frac=>val
			if(mn<NUM_NORMAL && normal[mn]=="\frac"){
				temp.erase(0, normal[mn].size() );
				HandleFrac(vec, temp, "");
				continue;
			}
			//cdot=>/times
			else if(mn<NUM_NORMAL && normal[mn]=="\cdot"){
				temp.erase(0, normal[mn].size() );
				CreateToken(vec, "*", OP, 2);
				continue;
			}
			//pi=>val
			else if(mn<NUM_NORMAL && normal[mn]=="\pi"){
				temp.erase(0, normal[mn].size() );
				CreateToken(vec, "pi", VAL, 17);
				continue;
			}
			//geq=>ge
			else if(mn<NUM_NORMAL && (normal[mn]=="\ge" || normal[mn]=="\geq")){
				temp.erase(0, normal[mn].size() );
				CreateToken(vec, "ge", OP, 8);
				continue;
			}
			//leq=>le
			else if(mn<NUM_NORMAL && (normal[mn]=="\leq" || normal[mn]=="\le")){
				temp.erase(0, normal[mn].size() );
				CreateToken(vec, "le", OP, 7);
				continue;
			}	
			//\vert=>|
			else if(mn<NUM_NORMAL && (normal[mn]=="\vert" || normal[mn]=="|")){
				
				temp.erase(0, normal[mn].size() );
				HandleVert(vec, temp);
				continue;
			}	
		//	else if(StartWith)
			else if(mn<NUM_NORMAL && normal[mn]=="\times"){
				temp.erase(0, normal[mn].size() );
				CreateToken(vec, "*", OP, 2);
				continue;
			}
			else if(mn<NUM_NORMAL && normal[mn]=="\div"){
				temp.erase(0, normal[mn].size() );
				CreateToken(vec, "/", OP, 3);
				continue;
			}
			else if(mn<NUM_NORMAL && normal[mn]=="\approx"){
				temp.erase(0, normal[mn].size() );
				CreateToken(vec, "appr", OP, 10);
				continue;
			}
			//neq
			else if(mn<NUM_NORMAL && normal[mn]=="\neq"){
				temp.erase(0, normal[mn].size() );
				CreateToken(vec, "neq", OP, 9);
				continue;
			}
			else if(mn<NUM_NORMAL && normal[mn]==")"){
				temp.erase(0, normal[mn].size() );
				CreateToken(vec, ")", OP, 5);
				if(temp.size()!=0 && ( (temp.at(0)>=48 && temp.at(0)<=57) || (temp.at(0)>=97 && temp.at(0)<=122) )){
					CreateToken(vec, "*", OP, 2);	
				}
				continue;
			}
			//normal symbol=>opr
			else if(mn<NUM_NORMAL){
				temp.erase(0, normal[mn].size() );
				CreateToken(vec, normal[mn], OP, -1);
				continue;
			}
			
		
			//abc
			while(temp.size()!=0 && temp.at(0)>=97 && temp.at(0)<=122){
			//	printf("%c\n",temp.at(0));
				if(mn=MatchWhere(temp, normal, NUM_NORMAL)<NUM_NORMAL){
					break;
				}
				else if(StartWith(temp,"|")==1 || StartWith(temp,"\vert")==1 || StartWith(temp,"vert")==1 || StartWith(temp, "ert")){
				//	HandleVert(vec, temp);
					break;
				}
				
				symbol+=temp.at(0);
				temp.erase(0,1);	
			}
		
			if(symbol.size()!=0){
				SplitToTimes(vec, symbol);
			}
			symbol.clear() ;
			
			if(StartWith(temp, "(")){
				CreateToken(vec, "*", OP, 2);
			}
	}
	
} 
//mt: 0:val 1:opr
void CreateToken(vector<Token> &vec, string s, TokenMeta met, int typ){
	Token t;
	t.meta=met;
	
	if(typ==-1){
		if(s=="+"){
			t.type=ADD;
			t.value=s;
		}
		else if(s=="-"){
			t.type=SUB;
			t.value=s;
		}
		else if(s=="<"){
			t.type=LT;
			t.value=s;
		}
		else if(s==">"){
			t.type=GT;
			t.value=s;
		}	
		else if(s=="="){
			t.type=EQ;
			t.value=s;
		}
		else if(s=="("){
			t.type=LPAREN;
			t.value=s;
		}
		else if(s==")"){
			t.type=RPAREN;
			t.value=s;
		}	
		else if(s=="^"){
			t.type=INV;		
			t.value=s;	
		}
				
	}
		
	t.type=TokenType(typ);
	t.value=s;
	vec.push_back(t); 
}


//ab=>a*b
void SplitToTimes(vector<Token> &vec, string s){
	while(s.size()!=0){
		string temp;
		temp+=s.at(0);
		s.erase(0,1);
		CreateToken(vec, temp, VAL, 17);
		CreateToken(vec, "*", OP, 2);
	}	
	vec.pop_back();
} 

void HandleFrac(vector<Token> &vec, string &s, string number){
	string back;
	string num;
	string symbol;
	int limit=2;
	int i=0;	
	int mn=0;

	if(number.size() != 0){
		back+=number;
	}
	back+="frac";
	
	while(i<limit){
		//number
		while(s.at(0)>=48 && s.at(0)<=57){
		//	printf("%c\n",temp.at(0));
			num+=s.at(0);
			s.erase(0,1);	
		}
		
		if(num.size() !=0 ){
			back+=num;
			num.clear(); 
		}
		
		//abc
		while(s.at(0)>=97 && s.at(0)<=122){
		//	printf("%c\n",temp.at(0));
			symbol+=s.at(0);
			s.erase(0,1);	
		}
	
		while(symbol.size()!=0){
			if(symbol.size()!=1){
				back+=symbol.at(0);
				back+="*";
				symbol.erase(0,1);
			}
			else{
				back+=symbol.at(0);
				symbol.erase(0,1);
			}
		}
		
		//symbols
		mn=MatchWhere(s, normal, NUM_NORMAL);
		if(normal[mn]=="\frac"){
			limit+=2;
			back+="frac";
			s.erase(0, normal[mn].size() );
		}
		else if(normal[mn]=="}"){
			back+="}";
			i+=1;
			s.erase(0, normal[mn].size() );
		}
		else if(normal[mn]=="\times"){
			back+="*";
			s.erase(0, normal[mn].size() );
		}
		else if(normal[mn]=="\div"){
			back+="/";
			s.erase(0, normal[mn].size() );
		}
		else if(normal[mn]=="\vert"){
			back+="|";
			s.erase(0, normal[mn].size() );
		}
		else if(normal[mn]=="\pi"){
			back+="pi";
			s.erase(0, normal[mn].size() );
		}
		else{
			back+=normal[mn];
			s.erase(0, normal[mn].size() );
		}
		
	}
	
	CreateToken(vec, back, VAL, 17);
}



void HandleVert(vector<Token> &vec, string &temp){
	string value;
	value+="|";
	string number;
	
	while(temp.size()!=0 && StartWith(temp,"|")!=1 && StartWith(temp,"\vert")!=1){
		value+=temp.at(0);
		temp.erase(0,1);
	}

	value+="|";
	if(StartWith(temp,"|")){
		temp.erase(0,sizeof("|")-1);
	}
	else{
		temp.erase(0,sizeof("\vert")-1);
	}
	CreateToken(vec,value,VAL,17);
	
}


vector<Token> Lexer::parser(string raw){
	vector<Token> vec;
	HandleString(raw, vec);
	return vec;
}