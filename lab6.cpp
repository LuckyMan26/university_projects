#include <iostream>
#include <fstream>
using namespace std;
string AllignText(string s){
int number_of_words=0;
for(int i=1;i<s.size();i++){
    if(s[i]==' '){
            number_of_words++;
    }
}
if(number_of_words==1){
    return s;
}

}
int main(){
ofstream fout;
fout.open("output.txt");
ifstream fin;
fin.open("input.txt");
    if (!fin.is_open())
        cout << "Error\n";
    else{
    string str;
    while(!fin.eof()){
        str="";
       getline(fin,str);
       cout<<str<<endl;
    }
    }
fin.close();
fout.close();

}
