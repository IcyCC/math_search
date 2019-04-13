#include <iostream> 
#include<string.h>
//#include "word.h"
using namespace std;
class ExpNode
{
	public:
		string value;
		ExpNode *left_node;
		ExpNode *right_node;
};
class Token
{
  public:
    TokenType type;    //类型
    std::string value; //值
};

string fz_left[100] ; // 左符号栈 
ExpNode *sz_left[100] ; // 左数字栈 
int fhead_left = 0 ; // 左符号栈指针 
int shead_left = 0 ; // 左数字栈指针 

string fz_right[100] ; // 右符号栈 
ExpNode *sz_right[100] ; // 右数字栈 
int fhead_right = 0 ; // 右符号栈指针 
int shead_right = 0 ; // 右数字栈指针 

void math_Right(string f) // 从数字栈中取出栈顶的两个数字 进行 f 运算 结果继续放到一颗的树中，树的根节点基本保持在 sz[0]中
{
	
    ExpNode *Left,*Right
	Left = new ExpNode();
	Right = new ExpNode();
	--shead_right;
	Left->value = sz_right[shead_right]->value;
	Left->left_node = sz_right[shead_right]->left_node;
	Left->right_node = sz_right[shead_right]->right_node;
	
	Right->value 	  = sz_right[shead_right+1]->value;
	Right->left_node  = sz_right[shead_right+1]->left_node;
	Right->right_node = sz_right[shead_right+1]->right_node;
	
	sz_right[shead_right]->left_node = Left;
	sz_right[shead_right]->right_node = Right; 
	sz_right[shead_right]->value =  f;
	
    -- fhead_right ;  
    sz_right[shead_right + 1]->value = 0 ;
	sz_right[shead_right + 1]->left_node = NULL ;
	sz_right[shead_right + 1]->right_node = NULL ;
}

void math_Left(string f) // 从数字栈中取出栈顶的两个数字 进行 f 运算 结果继续放到一颗的树中，树的根节点基本保持在 sz[0]中
{
	
    ExpNode *Left,*Right
	Left  = new ExpNode();
	Right = new ExpNode();
	--shead_left;
	Left->value 		= sz_left[shead_left]->value;
	Left->left_node 	= sz_left[shead_left]->left_node;
	Left->right_node 	= sz_left[shead_left]->right_node;
	
	Right->value 		= sz_left[shead_left+1]->value;
	Right->left_node 	= sz_left[shead_left+1]->left_node;
	Right->right_node 	= sz_left[shead_left+1]->right_node;
	
	sz_left[shead_left]->left_node = Left;
	sz_left[shead_left]->right_node = Right; 
	sz_left[shead_left]->value =  f;
	
    -- fhead_left ;  
    sz_left[shead_left + 1]->value = 0 ;
	sz_left[shead_left + 1]->left_node = NULL ;
	sz_left[shead_left + 1]->right_node = NULL ;
}
void init()
{
	sz_left[shead_left] = new ExpNode(); //左子树第0个得先分配空间，防止内存溢出
	sz_left[shead_left]->right_node = NULL;
	sz_left[shead_left]->left_node = NULL;
	
	sz_right[shead_right] = new ExpNode(); //右子树第0个得先分配空间，防止内存溢出
	sz_right[shead_right]->right_node = NULL;
	sz_right[shead_right]->left_node = NULL;
}

double get_tree(Token a[],int len)    //这只能识别如 a+b = c 或者 a+b 只有一个符号作为连接左右两个式子的公式变为树 ，如果有多个 连接符，比如 a>b>c这样是无法识别的
{
	
    int flag = 0;   //表示一开始为 ‘=’ 的左子树
	init(); //初始化第0个栈，防止溢出
	
	ExpNode *root;
	root = new ExpNode();
	root->right_node = NULL;
	root->left_node = NULL;
	
    for(int i = 0 ; i <= len ; ++ i )
    {   
        // 如果读到 "("  则直接放入栈中 
        if(a[i].value == '(' ) { 
				if(flag = 0)
					fz_left[++ fhead_left] = a[i].value ;
				else
					fz_right[++ fhead_right] = a[i].value;
                continue ;
				
            }
        // 如果读到 ")"  则将 "(" 之前的运算符全部出栈 
        if(a[i].value==')') { 
				if(flag == 0)
				{
					while(fz_left[fhead_left] != '(')
						math_Left(fz_left[fhead_left]) ;
					
					-- fhead_left ;
				}
				else
				{
					while(fz_right[fhead_right]! = '(')
						math_Right(fz_right[fhead_right]);
						
					-- fhead_right;
				}
                continue ;
            }
        // 读到数字直接放在数字栈顶就ok啦 
        if(a[i].type == "value")
		{     
            if(flag == 0)
			{
				++ shead_left ;
				sz_left[shead_left] = new ExpNode();
				sz_left[shead_left]->left_node = NULL;
				sz_left[shead_left]->right_node = NULL;
				sz_left[shead_left]->value = a[i].value;
			}
			else
			{
				++ shead_right ;
				sz_right[shead_right] = new ExpNode();
				sz_right[shead_right]->left_node = NULL;
				sz_right[shead_right]->right_node = NULL;
				sz_right[shead_right]->value = a[i].value;
			}
			
			continue;
        }
        else if(a[i].value == "="  || a[i].value == "<" || a[i].value ==">" || a[i].value == "\neq" || a[i].value == "\approx" )
		{
			
			while(fhead_left != 0) {
				math_Left(fz_left[fhead_left]) ;
			}
			
			root->left_node = sz_left[shead_left];
			
			root->value = a[i].value;
				
			flag = 1;
		}
		else
		{
			
            if(a[i].value == '*' || a[i].value == '/' ){ 
        // 如果读到 "/" 或 "*"  直接放在符号栈栈顶 
        			if(flag == 0)
                    	fz_left[++fhead_left] = a[i].value;
                    else
                    	fz_right[++fhead_right] = a[i].value;
                    continue;
                }
            else 
            {
			
				if(flag == 0)
				{
					while(fz_left[fhead_left] == '*' || fz_left[fhead_left] == '/' || fz_left[fhead_left] == a[i].value){ 
        // 如果读到 "+" 或 "-"  
        // 则将栈顶跟自己一样的符号和 "/"  "*" 全部弹出
        // 这个可以手动列几个式子体会一下 (^-^) 
						math_Left(fz_left[fhead_left]);
						}
					fz_left[++ fhead_left] = a[i].value ;
				}
				else  //右子树 
				{
					while(fz_right[fhead_right] == '*' || fz_right[fhead_right] == '/' || fz_right[fhead_right] == a[i].value){ 
						math_Right(fz_right[fhead_right]);
						}
					fz_right[++ fhead_right] = a[i].value;
					
				}
			}
        
			
        }
	}
	while(fhead_left != 0) {
				math_Left(fz_left[fhead_left]) ;
			}
    while(fhead_right != 0) {
				math_Right(fz_right[fhead_right]) ;
			}
			
	root->r_node = sz_right[shead_right];
			
    // 当栈中仅有一个数字的时候 运算式的答案就是它啦 

   return root;
}
