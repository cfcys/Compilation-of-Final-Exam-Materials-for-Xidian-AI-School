#include<stdio.h>
#include<stdlib.h> 
#include<stdlib.h>
#include<sys/malloc.h>
#include<stdio.h>

#define MAXSIZE 100
/*定义顺序栈*/
typedef struct {
	int *base;  //用于栈存储的基地址 
	int *top;  //指向该基地址的栈顶指针 
	int stackSize;  //栈的大小 
}SqStackInt;
/*定义顺序栈*/
typedef struct {
	char *base;  //用于栈存储的基地址 
	char *top;  //指向该基地址的栈顶指针 
	int stackSize;  //栈的大小 
}SqStackChar;
/*初始化*/
int InitStack_Int(SqStackInt &S){
	S.base = (int *)malloc(MAXSIZE*sizeof(int));  //给基地址分配一个内存空间 
	S.top = S.base;  //将栈顶指针指向这个基地址 
	S.stackSize = MAXSIZE;  //设置栈的大小 
	return 0;
} 
int InitStack_Char(SqStackChar &S){
	S.base = (char *)malloc(MAXSIZE*sizeof(char));  //给基地址分配一个内存空间 
	S.top = S.base;  //将栈顶指针指向这个基地址 
	S.stackSize = MAXSIZE;  //设置栈的大小 
	return 0;
} 
/*进栈*/
int Push_Int(SqStackInt &S,int e){
	if(S.top-S.base==S.stackSize) return -1;
	*S.top = e;  //将输入的值压入栈中 
	S.top++;  //指针上移一个单位 

	return 0;
} 
int Push_Char(SqStackChar &S,char e){
	if(S.top-S.base==S.stackSize) return -1;
	*S.top = e;  //将输入的值压入栈中 
	S.top++;  //指针上移一个单位 

	return 0;
}
/*出栈*/
int Pop_Int(SqStackInt &S,int &e) {
	if(S.base==S.top) return -1;
	S.top--;  //指针下移一个 
	e = *S.top;  //将当前指针所指的值赋值给e 

	return 0;
}
int Pop_Char(SqStackChar &S,char &e) {
	if(S.base==S.top) return -1;
	
	S.top--;  //指针下移一个 
	e = *S.top;  //将当前指针所指的值赋值给e 

	
	return 0;
}
/*获取栈的长度*/
int GetLength_Int(SqStackInt S){
	return S.top-S.base;  
}
int GetLength_Char(SqStackChar S){
	return S.top-S.base;  
}
/*判断栈空*/ 
int StackEmpty_Int(SqStackInt S) {
	if(S.top==S.base) return 0;  //为空返回 0 
	return 1;  //不为空返回1 
} 
int StackEmpty_Char(SqStackChar S) {
	if(S.top==S.base) return 0;  //为空返回 0 
	return 1;  //不为空返回1 
} 
/*清空栈*/ 
int ClearStack_Int(SqStackInt S){
	if(S.base) //栈不为空 
	S.base = S.top;
	return 0;
} 
int ClearStack_Char(SqStackChar S){
	if(S.base) //栈不为空 
	S.base = S.top;
	return 0;
} 
/*销毁栈*/ 
int DestroyStack_Int(SqStackInt &S){
	if(S.base){
	free(S.base);
	S.stackSize = 0;
	S.top = S.base = NULL; 
	}
	return 0;
}
int DestroyStack_Char(SqStackChar &S){
	if(S.base){
	free(S.base);
	S.stackSize = 0;
	S.top = S.base = NULL; 
	}
	return 0;
}
/*读取栈顶元素*/
int GetTop_Int(SqStackInt S) {
	return *(S.top-1); 
}
char GetTop_Char(SqStackChar S) {
	return *(S.top-1); 
}



int isOper(char c){
	if(c == '#' || c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'){
		return 1; //是操作符 
	}else{
		return 0;  //不是操作符 
	}
}
/*
* c1:栈顶操作符
* c2:扫描操作符 
*
*/
char getStackTopPriority(char StackTop,char c){
	//printf("Priority:%c::%c\n",StackTop,c);
	if(StackTop == '#' || (StackTop == '(' && c != ')') || c == '(' ||( (StackTop == '+' || StackTop == '-')&&((c == '*' || StackTop == '*')))) {
		return '<';  //栈顶操作符优先级 小于等于 当前扫描操作符则  操作符进栈 
	}else if(StackTop =='(' && c == ')'){
		return '=';
	}else if(c == '*' || c == '/'||c == ')'){
		return '>' ;
	}else{
		return '>';
	}
	
}
/*
*从S1栈中弹出两个操作数 a和b 
*从S2栈中弹出一个操作符  oper 
* 然后两个操作数和一个操作符进行运算 
*/
int operate(int a,char oper,int b){
	if(oper == '+'){
		return a+b;
	}else if(oper=='-'){
		return a-b; 
	}else if(oper == '*'){
		return a*b;
	}else {
		return a/b;
	}
}
/*
错误可能有以下几个：
缺失操作数
非法算符
括号不配匹配
*/
int kuohao(char*a){
    int z = 1;
    int key = 0;
    char ch = a[z - 1];
    while (ch!='#'){

        if(ch=='(')
            key++;
        if(ch==')'){
            key--;
        }
        if(key<0){
            printf("括号不匹配（右括号多余）\n");
            return 1;
        }
      ch = a[z++];
    }
    if(key!=0){
        printf("括号不匹配（左括号多余）\n");
        return 1;
    }
    return 0;
}

int illegal(char*a){
    int z = 1;
    char ch = a[z-1];
    while(ch!='#'){
        if(!(ch<('9'+1)&&ch>('0'-1)||ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')')){
            printf("非法算符\n");
            return 1;
        }
        ch = a[z++];
        
    }
    return 0;
}

int lose(char*a){
        int z = 1,key=0;
        char ch = a[z-1];
        while(ch!='#'){
            if(ch=='*'||ch=='/'||ch=='+'||ch=='-'){
                key++;
            }
            if(ch<='9'&&ch>='0')
                key = 0;

            if (key == 2)
            {
                printf("运算数缺失\n");
                return 1;
            }

            ch = a[z++];

        }
        return 0;

}
    int wrong(char *a)
    {
        if(kuohao(a)|illegal(a)|lose(a))
            return 1;
        return 0;
    }

int main(){
	char arr[100] = {'\0'},k;
    int key = 0;
    char ch;
    k = getchar();
    if(k!='#'){
            printf("格式错误！");
            return 0;
    }

    while ((ch = getchar()) != '\n')
    {
        arr[key++] = ch;
    }
    if(arr[key-1]!='#'){
        printf("格式错误！");
        return 0;
    }

        key = 0;

        while (arr[key] != '#')
        {
                printf("%c", arr[key]);
                key++;
    }

    if(wrong(arr)){
        return 0;
    }
    SqStackInt S1;  //用来存储操作数的栈 int 类型 
	SqStackChar S2;
	//初始化两个栈 
	InitStack_Int(S1); 
	InitStack_Char(S2);
	//操作符栈 进栈一个 # 号作为结束标志 
	Push_Char(S2,'#');
	int i = 0;  //用于循环遍历 中缀表达式 arr 数组 
	while(arr[i]!='#'||GetTop_Char(S2)!='#'){
	
		if(!isOper(arr[i])){  //如果不是操作符 
			int e = arr[i] - '0';
			Push_Int(S1,e);  //进操作数 S1 栈 
			i++;
		}else{ 				//是操作符等待进入 S2 栈 
				char e = arr[i]; 
				//比较操作符 S2栈  当前栈顶操作符的和当前扫描到的操作符优先级大小 
				switch (getStackTopPriority(GetTop_Char(S2),e)){  
					
				case '<':{  //栈顶操作符优先级小--> 
					Push_Char(S2,e); 
					i++;
					break;
				}
					
				case '=' :{
					char x;
					Pop_Char(S2,x);
					i++;
					break;
				}
				
				case '>' :{
					int a,b;char oper;
					Pop_Int(S1,b);Pop_Int(S1,a);
					Pop_Char(S2,oper);
					int e = operate(a,oper,b);
					Push_Int(S1,e);
					
					break;
				}
			} 			
		} 
	}

	
	printf("运算结果为：%d\n",GetTop_Int(S1));
    return 0;
}
