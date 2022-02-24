#include <iostream>
#include <ctime>
#include <cstring>
#define MaxLvL 3
using namespace std;
struct node{
int data;
node** next;
node(int value,int level){
this->data=value;
next=new node*[level+1];
memset(next,0,sizeof(node*)*(level+1));
}
};
int random_level(){
int lvl=0;
int a=rand()%2;
while(a==1&&lvl<MaxLvL){
    a=rand()%2;
    lvl++;
}
return lvl;
}
struct skiplist{
node* head;
int cur_level;
skiplist(){
cur_level=0;
node* n=new node(-1,MaxLvL);
head=n;
}
void print(){
node* n;

for(int i=0;i<=cur_level;i++){
    n=head->next[i];
    while(n){
    cout<<n->data<<" ";
    n=n->next[i];
    }
    cout<<endl;
}
}
void insert(int elem){
node* n;
n=head;

node* update[MaxLvL+1];
memset(update,0,sizeof(node*)*(MaxLvL+1));
for(int i=cur_level;i>=0;i--){
    while((n->next[i]!=NULL)&&(n->next[i]->data<elem)){
        n=n->next[i];
    }
    update[i]=n;
}
n=n->next[0];

if(n==nullptr||n->data<elem){
    int lev=random_level();
    if(lev>cur_level){
        for(int i=cur_level+1;i<lev+1;i++){
            update[i]=head;
        }
        cur_level=lev;
    }
    node* temp=new node(elem,lev);
    for(int i=0;i<lev+1;i++){
        temp->next[i]=update[i]->next[i];
        update[i]->next[i]=temp;
    }
}
}
void search(int key){
node* n=head;
for(int i=cur_level;i>=0;i--){
    while(n->next[i]&&n->next[i]->data<key){
        n=n->next[i];
    }
}
n=n->next[0];
if(n&&n->data==key){
    cout<<"Elements was founded\n";
}
}

};
int main(){
srand(time(NULL));
skiplist l;
l.insert(1);
l.insert(2);
l.insert(3);
l.insert(4);
l.insert(5);
l.print();
}
