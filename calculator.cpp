#include <iostream> 
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <math.h>
#include <string.h>
#include <iomanip>

using namespace std;

char basic_op_de[4]={'+','-','*','/'};

unsigned char Prior_de[8][8] ={ 		// 运算符优先级表 
   		  // '+' '-' '*' '/' '(' ')' '#' '^' 
 		/*+*/'>','>','<','<','<','>','>','<', 
 		/*-*/'>','>','<','<','<','>','>','<', 
 		/***/'>','>','>','>','<','>','>','<', 
 		/*/*/'>','>','>','>','<','>','>','<',
 		/*(*/'<','<','<','<','<','=',' ','<',
 		/*)*/'>','>','>','>',' ','>','>','>',
 		/*#*/'<','<','<','<','<',' ','=','<',
 		/*^*/'>','>','>','>','<','>','>',' ',
};

char graph_de[8]={'+','-','*','/','(',')','#','^'};


bool In_de(char a,char b[7])       { //判断是否为运算符
	int i;
	bool c=false;
	for(i=0;i<=7;i++)
	{
		if(a==b[i])
		c=true;
	}
	return c;
}

char  Precede_de(char a,char b)     {//判断优先级
	int i,j;
	if(a=='+') i=0;
	if(a=='-') i=1;
	if(a=='*') i=2;
	if(a=='/') i=3;
	if(a=='(') i=4;
	if(a==')') i=5;
	if(a=='#') i=6;
	if(a=='^') i=7;
	if(b=='+') j=0;
	if(b=='-') j=1;
	if(b=='*') j=2;
	if(b=='/') j=3;
	if(b=='(') j=4;
	if(b==')') j=5;
	if(b=='#') j=6;
	if(b=='^') j=7;
	return Prior_de[i][j];
}

double Operate_de(double Num1,char b,double Num2)     {//进行运算
	double result=1;
	switch(b){
		case'+':return Num1+Num2;break;
		case'-':return Num1-Num2;break;
		case'*':return Num1*Num2;break;
		case'/':return Num1/Num2;break;
    }
} 

double EvaluateExpression_de(char* string)            //求表达式的值 
{
	int count=0;
	stack<double> p1;       //运算数 
	stack<char> p2;
	stack<double> *S1; 			 
	stack<char> *S2;     //运算符 
	S1=&p1;
	S2=&p2;
	char temp,y,x,c,cpre='('; //prec用与记录前一个字符 
	double Num1,Num2,num; 
	char str[50];
	str[0]='\0';
	int i=0;
	

	temp='#';
	S2->push(temp);
	
	c=string[count];
	count++;
	
	while(c!='#'||S2->top()!='#'){
		if(!In_de(c,graph_de)||c=='.') {	//是运算数 (含小数点)
			str[i]=c;
			i++;
			cpre=c;
			c=string[count];
        	count++;
			if(In_de(c,graph_de)){    //不是运算数了，则把字符串转化为数字后压栈 
				str[i]='\0';
				num=atof(str);
				S1->push(num); 
				i=0;                 //字符串初始化 
				str[i]='\0';
			}
		}
		else{
				if(cpre=='('&&c=='-'){
				    S1->push(0);	
				}
				switch(Precede_de(S2->top(),c)){
					case'<':
						S2->push(c);				//进栈 
						cpre=c;
						c=string[count];
        				count++;
						break;
					case'=':
						x=S2->top();
						S2->pop();
						cpre=c;
						c=string[count];
        				count++;
						break;
					case'>':
						y=S2->top();
						S2->pop();
						Num2=S1->top();
						S1->pop();
						Num1=S1->top();
						S1->pop();
					S1->push(Operate_de(Num1,y,Num2));break;		//进栈 
				}		
		}
	}
	Num1=S1->top();
	S1->pop();
	return Num1;
}

char basic_op[3]={'+','-','*'};

 
unsigned char Prior[6][6] ={ 		// 运算符优先级表 
   		  // '+' '-' '*' '(' ')' '#'  
 		/*+*/'>','>','<','<','>','>',
 		/*-*/'>','>','<','<','>','>',
 		/***/'>','>','>','<','>','>',
 		/*(*/'<','<','<','<','=',' ',
 		/*)*/'>','>','>','>','>','>',
 		/*#*/'<','<','<','<',' ','=',
};

char graph[6]={'+','-','*','(',')','#'};

bool In(char a,char b[6]) {       //判断是否为运算符
	int i;
	bool c=false;
	for(i=0;i<=5;i++)
	{
		if(a==b[i])
		c=true;
	}
	return c;
}

char  Precede(char a,char b) { //判断优先级
	int i,j;
	if(a=='+') i=0;
	if(a=='-') i=1;
	if(a=='*') i=2;
	if(a=='(') i=3;
	if(a==')') i=4;
	if(a=='#') i=5;
	if(b=='+') j=0;
	if(b=='-') j=1;
	if(b=='*') j=2;
	if(b=='(') j=3;
	if(b==')') j=4;
	if(b=='#') j=5;
	return Prior[i][j];
}
int HCF(int n,int m)    {//最大公约数
	 int p,r,temp;
     if (n<m) {
	    temp=n;
        n=m;
        m=temp;                //把大数放在n中, 小数放在m中
     }
	 p=n*m;                     //先将n和m的乘积保存在p中, 以便求最小公倍数时用
 	while (m!=0){               //求n和m的最大公约数
	 	r=n%m;
     	n=m;
     	m=r;
	 }
	return n;
}

int LCD(int n,int m) {  //最小公倍数 
	 int p,r,temp;
     if (n<m){
	   temp=n;
       n=m;
       m=temp;                //把大数放在n中, 小数放在m中
     }
	 p=n*m;                     //先将n和m的乘积保存在p中, 以便求最小公倍数时用
 	while (m!=0)               //求n和m的最大公约数
    {r=n%m;
     n=m;
     m=r;
	 }
	return p/n;
}
char *yuefen(int l,int r) {        //约分 
	char  *left=(char*)malloc(sizeof(char)*200);
	char  *right=(char*)malloc(sizeof(char)*200);
	char  *temp_result2=(char*)malloc(sizeof(char)*1000);
	if(HCF(l,r)!=1){//不互质
		int k=HCF(l,r);
		l=l/k;
		r=r/k;
	}
	itoa(l,left,10);
	itoa(r,right,10);
	strcpy(temp_result2,left);
	strcat(temp_result2,"/");
	strcat(temp_result2,right);

	
	return temp_result2;
} 

char * Operate(char* Num1,char b,char* Num2){ //进行运算
	int num1_l,num1_r,num2_l,num2_r,num3_l,num3_r;
	char *Num1_left=(char*)malloc(sizeof(char)*200);
	char *Num1_right=(char*)malloc(sizeof(char)*200);
	char *Num2_left=(char*)malloc(sizeof(char)*200);
	char *Num2_right=(char*)malloc(sizeof(char)*200);
	char  *temp_result1=(char*)malloc(sizeof(char)*1000);
	
	int i=0,j;                            //分割字符串为4个数 
	for(i=0;Num1[i]!='/';i++){
		Num1_left[i]=Num1[i];
	} 
	Num1_left[i]='\0';
	j=i;
	for(i=0;;i++){
		Num1_right[i]=Num1[i+j+1];
		if(Num1_right[i]=='\0')   
		  break;
	} 
	for(i=0;Num2[i]!='/';i++){
		Num2_left[i]=Num2[i];
	} 
	Num2_left[i]='\0';
	j=i;
	for(i=0;;i++){
		Num2_right[i]=Num2[i+j+1];
		if(Num2_right[i]=='\0')   
		break;
	} 
    
	num1_l=atoi(Num1_left);        //字符串转整型数字 
    num1_r=atoi(Num1_right);
    num2_l=atoi(Num2_left);
    num2_r=atoi(Num2_right);
    
	switch(b){
	  case'+': 
	        if(num1_r==num2_r){  //同分母
				num1_l=num1_l+num2_l;	
				strcpy(temp_result1,yuefen(num1_l,num1_r));
			} 
			else{            //分母不同
				num3_r=LCD(num1_r,num2_r);  //通分后的分母
				num1_l=num1_l*num3_r/num1_r;
				num2_l=num2_l*num3_r/num2_r;
				num3_l=num1_l+num2_l;      //通分之后的分子
				strcpy(temp_result1,yuefen(num3_l,num3_r));
			} 
             break;

	  case'-':
		    if(num1_r==num2_r){  //同分母
				num1_l=num1_l-num2_l;
				strcpy(temp_result1,yuefen(num1_l,num1_r));
			} 
			else{           //分母不同
				num3_r=LCD(num1_r,num2_r);  //通分后的分母
				num1_l=num1_l*num3_r/num1_r;
				num2_l=num2_l*num3_r/num2_r;
				num3_l=num1_l-num2_l;      //通分之后的分子
				strcpy(temp_result1,yuefen(num3_l,num3_r));
			} 
	        break;
	  case'*':
			num3_r=num1_r*num2_r;
			num3_l=num1_l*num2_l;
			strcpy(temp_result1,yuefen(num3_l,num3_r)); 
	        break;
    }

    return temp_result1;
} 

char* EvaluateExpression(char* string){            //求表达式的值 
	int str_counter;
	char **str= (char**)malloc(sizeof(char*)*20);        //存储运算数的字符串载体 
  	for(str_counter=0; str_counter<20; str_counter++)   {
  	  str[str_counter] = (char*)malloc(sizeof(char)*200);
  	  str[str_counter][0]='\0';                              //初始化 
  	}    
	str_counter=0;
	
	int temp_result_counter;
	char ** temp_result=(char**)malloc(sizeof(char)*20);      //作为中间运算结果的载体 
	for(temp_result_counter=0; temp_result_counter<20; temp_result_counter++) {
  	  temp_result[temp_result_counter] = (char*)malloc(sizeof(char)*1000);
  	  temp_result[temp_result_counter][0]='\0';                              //初始化 
  	}    
	temp_result_counter=0;
	
	int count=0;
	stack<char *> p1;       //运算数 
	stack<char> p2;
	stack<char *> *S1; 			 
	stack<char> *S2;     //运算符 
	S1=&p1;
	S2=&p2;
	char temp,y,x,c,cpre='(';                    //cpre用于记录前一个字符 
	char * Num1=(char*)malloc(sizeof(char)*200);
	char * Num2=(char*)malloc(sizeof(char)*200); 

	int i=0;
	
	temp='#';
	S2->push(temp);
	
	c=string[count];
	count++;
	
	while(c!='#'||S2->top()!='#'){
		if(!In(c,graph))  					//是运算数 (含小数点)
		{
			str[str_counter][i]=c;
			i++;
			cpre=c;
			c=string[count];
        	count++;
			if(In(c,graph)){              //不是运算数了，则把字符串转化为数字后压栈 
				str[str_counter][i]='\0';
				S1->push(str[str_counter]);        //压栈的不是内容，是地址 
                str_counter++;
                i=0;
			}
		}
		else{                              //运算符 
			
			switch(Precede(S2->top(),c)){
					case'<':
						S2->push(c);				//进栈 
						cpre=c;
						c=string[count];
        				count++;
						break;
					case'=':
						x=S2->top();
						S2->pop();
						cpre=c;
						c=string[count];
        				count++;
						break;
					case'>':
						y=S2->top();
						S2->pop();
						strcpy(Num2,S1->top());
						S1->pop();
						strcpy(Num1,S1->top());
						S1->pop();
						strcpy(temp_result[temp_result_counter],Operate(Num1,y,Num2));          //修改中间结果 
						S1->push(temp_result[temp_result_counter]);
						temp_result_counter++;
						break;		
			}		
		}
	}
	strcpy(Num1,S1->top());
	S1->pop();
	return Num1;	
}


int main()
{
	int swi;
	cout<<"-----------欢迎使用小学生计算器---------\n"<<endl;
	cout<<"--------------输入1；小数计算---------\n"<<endl;
	cout<<"--------------输入2；分数计算---------\n"<<endl;
	cout<<"--------------输入0；退出---------\n"<<endl;
	
	cout<<"你的选择:";
	cin>>swi;
	if(swi==0)  return 0; 
	else if(swi==1){
		int count ,left ,right ,op_num,LR,temp;
	double result;
	double stu_answer;
	
	char *op=(char *)malloc(sizeof(char)*3); 
	char *left_string=(char *)malloc(sizeof(char)*200);
	char *temp_string=(char *)malloc(sizeof(char)*1000);
	
	srand(time(0));
	temp=rand()%20+1;
	itoa(temp,temp_string,10);
	
	for(count=1;count<=5;count++){ 

		op_num=rand()%4;
		op[0]=basic_op_de[op_num];
		op[1]='\0';
		LR=rand()%2;
		if(LR==0){          //上一步的表达式在左侧
		
			left=rand()%20+1;
			itoa(left,left_string,10);
			strcat(temp_string,op);
			strcat(temp_string,left_string);
		} 
		else{            //上一步的表达式在右侧
		

			left=rand()%20+1;
			itoa(left,left_string,10);
			strcat(left_string,op);
			strcat(left_string,temp_string);
			strcpy(temp_string,left_string);
		}
		LR=rand()%5;
		if(LR<=1){	       //加括号
		
			char zuokuohao[200]="(",youkuohao[4]=")";
			strcat(zuokuohao,temp_string);
			strcat(zuokuohao,youkuohao);
			strcpy(temp_string,zuokuohao) ;
		}  
	   
	} 
	
	cout<<"题目是:"<<temp_string<<endl<<endl;	
	
	strcat(temp_string,"#");
   
    result=EvaluateExpression_de(temp_string);
    
    cout<<"请输入你的答案:（保留两位小数）     ";
    cin>>stu_answer;
    cout<<endl<<"正确答案为:    "<<setprecision(2) <<std::fixed<<result<<endl<<endl;
	if(result==stu_answer)
		cout<<"恭喜你，答对了"<<endl<<endl;
	else
		cout<<"答错了，没关系，这道题有点难"<<endl<<endl;
	
    
	} 
	if(swi==2){
		int count ,left ,right ,op_num,LR,temp;
	
	char *op=(char *)malloc(sizeof(char)*3); 
	char *left_string=(char *)malloc(sizeof(char)*200);
	char *right_string=(char *)malloc(sizeof(char)*200);
	char *temp_string=(char *)malloc(sizeof(char)*1000);
	char *temp_string_right=(char *)malloc(sizeof(char)*200);
	char *result=(char *)malloc(sizeof(char)*1000);
	
	char stu_answer[100];
	
	srand(time(0));
	temp=rand()%20+1;
	itoa(temp,temp_string,10);
	strcat(temp_string,"/");
	temp=rand()%50+1;
	itoa(temp,temp_string_right,10);
	strcat(temp_string,temp_string_right);
	
	for(count=1;count<=5;count++){
	 

		op_num=rand()%3;
		op[0]=basic_op[op_num];
		op[1]='\0';
		LR=rand()%2;
		if(LR==0){          //上一步的表达式在左侧
		
			right=rand()%50+1;
			itoa(right,right_string,10);
			left=rand()%20+1;
			itoa(left,left_string,10);
			strcat(temp_string,op);
			strcat(temp_string,left_string);
			strcat(temp_string,"/");
			strcat(temp_string,right_string);
		} 
		else{          //上一步的表达式在右侧
		
			right=rand()%50+1;
			itoa(right,right_string,10);
			left=rand()%20+1;
			itoa(left,left_string,10);
			strcat(left_string,"/");
			strcat(left_string,right_string);
			strcat(left_string,op);
			strcat(left_string,temp_string);
			strcpy(temp_string,left_string);
		}
		LR=rand()%5;
		if(LR<=1){	       //加括号
		
			char zuokuohao[200]="(",youkuohao[4]=")";
			strcat(zuokuohao,temp_string);
			strcat(zuokuohao,youkuohao);
			strcpy(temp_string,zuokuohao) ;
		}  
	   
	} 
	cout<<"题目是:"<<temp_string<<endl<<endl;	
	
	strcat(temp_string,"#");
   
    strcpy(result,EvaluateExpression(temp_string));
    
    cout<<"请输入你的答案:     ";
    cin>>stu_answer;
    cout<<endl<<"正确答案为:    "<<result<<endl<<endl;
	if(strcmp(result,stu_answer)==0)
		cout<<"恭喜你，答对了"<<endl<<endl;
	else
		cout<<"答错了，没关系，这道题超纲了"<<endl<<endl;
	}

}
