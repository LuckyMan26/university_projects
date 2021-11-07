#include <iostream>
#include <stack>
#include <cmath>
#include <string>
using namespace std;
int prior(char c){
if(c=='('){
    return 0;
   }
if(c=='+'){
    return 1;
}
if(c=='*'){
    return 2;
}
if(c=='-'){
    return 1;
}
if(c=='/'){
    return 2;
}
if(c=='^'){
    return 3;
}
}
double op(stack<double> numbers,char s){
  switch(s){
                 case('+'):{
                    double n1=numbers.top();
                    numbers.pop();
                    double n2=numbers.top();
                    numbers.pop();
                     return n1+n2;
                    break;
                 }

                case('-'):{
                    double n1=numbers.top();
                    numbers.pop();
                    double n2=numbers.top();
                    numbers.pop();
                   return n2-n1;
                    break;
                }
                case('*'):{
                    double n1=numbers.top();
                    numbers.pop();
                    double n2=numbers.top();
                    numbers.pop();
                      return n1*n2;;
                    break;
                }
                case('/'):{
                    double n1=numbers.top();
                    numbers.pop();
                    double n2=numbers.top();
                    numbers.pop();
                   return n2/n1;
                    break;
                }
                case('^'):{
                    double n1=numbers.top();
                    numbers.pop();
                    double n2=numbers.top();
                    numbers.pop();
                   return pow(n2,n1);
                    break;
                }
  }
}
int find_integer(string s,int n){
int count=0;
int j=n-1;
while(isdigit(s[j+1])){
    j++;
    count++;
}
int number=0;
int i=n-1;
while(isdigit(s[i+1])){
    i++;
    number+=(s[i]-'0')*pow(10,count+n-i-1);
}
return number;
}
bool rightness(string a){
	bool rightness = true;
	if (a[0] == '+'||a[0] == '*'||a[0] == '/'){
        return false;
	}
	else if (a[a.length()-1]=='+'||a[a.length()-1]=='-'||a[a.length()-1]=='*'||a[a.length()-1]=='/'){
		return false;
	}
	else {
		for (int i = 0; (i < a.length()); i++) {
			if ((a[i] == '+'||a[i] == '-'||a[i] == '*'||a[i] == '/'||a[i]=='(')&&(a[i+1] == '+'||a[i+1] == '*'||a[i+1] == '/'||a[i+1]==')')){
				return false;
				}
			if((a[i] == '/')&&(a[i+1] == '0')){
				return false;
			}
		}
	}
	stack <double> stack;
	char left = '(', right = ')';
	int err = 0;
	for (int i = 0; i < a.size() && !err; ++i) {
		if (a[i] == left) stack.push(i);
		else if (a[i] == right) {
			if (stack.size() > 0) stack.pop();
			else return false;
		}
	}
	if (!err && stack.size() > 0) {
            return false;
           }

	return rightness;
}
bool is_one_number_in_brackets(string s,int index1,int index2){
int count=0;
for(int i=index1;i<=index2;i++){
    if(isdigit(s[i])){
            int j=i+1;
        while(isdigit(s[j])){
            j++;
        }
    count++;
    }
}
if(count==1){
    return true;
}
else{
    return false;
}
}
string change(string s,char n,string n_change){
int i=0;
for(i=0;i<s.length();i++){
    if(s[i]==n){
        s.replace(i,1,n_change);
        i+=n_change.length();
    }
}
return s;
}
int main(){
    char c;
    string s,s1;
    string result;
    cin>>s1;
    stack<char> sign;
    stack<double> numbers;
int i=0;
s=s1;
string n;
if(s1[0]=='-'){

       s.insert(0,"0",0,1);
    }
for(int i=0;i<s.length();i++){
    if(!isdigit(s[i])&&(s[i]!='+')&&(s[i]!='-')&&(s[i]!='*')&&(s[i]!='/')&&(s[i]!='(')&&(s[i]!=')')&&(s[i]!='^')){
        cout<<"Enter variable: "<<endl;
        cin>>c;
        cout<<"Please enter value of variable"<<endl;
        cin>>n;
        s=change(s,c,n);
        break;
    }
}
cout<<s<<endl;
for(int j=0;j<s1.length();j++){
    if(s1[j]=='('){
        if(s1[j+1]=='-'){
        s.insert(j+1,"0",0,1);
       }
       }
}

if(rightness(s)){
    for(;i<s.length();i++){
        if(isdigit((s[i]))){

            numbers.push(find_integer(s,i));
            int j=i-1;
        while(isdigit(s[j+1])){
            j++;
        }
            i=j;

        }

        else{
            if((s[i]!='(')&&(s[i]!=')')){
                if(sign.empty()){
                    sign.push(s[i]);
                }
                else{
                    if(prior(s[i])>prior(sign.top())){
                        sign.push(s[i]);
                    }
                    else{

                        while((!sign.empty())&&(prior(s[i])<=prior(sign.top()))){
                        double n=op(numbers,sign.top());
                        numbers.pop();
                        numbers.pop();
                        numbers.push(n);
                        sign.pop();
                    }
                    sign.push(s[i]);
                    }
                }
            }
            else if(s[i]=='('){
                        sign.push(s[i]);

                    }
            else if(s[i]==')'){
                while(sign.top()!='('){
                        double n=op(numbers,sign.top());
                        numbers.pop();
                        numbers.pop();
                        sign.pop();
                        numbers.push(n);

                      }

                      sign.pop();
            }
        }

        }
}
else{
    cout<<"Error"<<endl;
    return 0;
}
while(!(sign.empty())){


                double n=op(numbers,sign.top());
                numbers.pop();

                numbers.pop();
                numbers.push(n);
            sign.pop();

}
cout<<"Result: "<<numbers.top();
}
