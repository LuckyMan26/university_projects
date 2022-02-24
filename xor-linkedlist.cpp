#include <iostream>

using namespace std;
struct node{
int value;
node* link;
};
node* XOR(node* x, node* y) {
    return (node*)((uintptr_t)(x) ^ (uintptr_t)(y));
}
struct list{
node* head;
list(){
head=nullptr;
}
void print(){
node* curr=new node();
node* prev=new node();
node* next=new node();
curr=head;
prev=nullptr;
while(curr){
    cout<<curr->value<<" ";
    next=XOR(prev,curr->link);
    prev=curr;
    curr=next;
}
cout<<endl;
}
void insert_beg(int elem){
node* n=new node();
n->value=elem;
n->link=head;
if(head){
    head->link=XOR(n,head->link);
}
head=n;
}
int length(){
node* curr=new node();
node* prev=new node();
node* next=new node();
curr=head;
prev=nullptr;
int count=0;
while(curr){
    count++;
    next=XOR(prev,curr->link);
    prev=curr;
    curr=next;
}
return count;
}
void append(int elem){
node* curr=new node();
node* prev=new node();
node* next=new node();
curr=head;
prev=nullptr;
node* temp=new node();
temp->value=elem;
if(this->length()>0){
for(int i=0;i<this->length()-1;i++){
    next=XOR(prev,curr->link);
    prev=curr;
    curr=next;
}
curr->link=XOR(prev,temp);
temp->link=curr;
}
else{
    temp->link=head;
    head=temp;
}
}
void insert_pos(int elem,int pos){
if(pos>this->length()-1||pos<0){
    cout<<"Invalid position\n";
}
else{
node* curr=new node();
node* prev=new node();
node* next=new node();
curr=head;
prev=nullptr;
node* temp=new node();
temp->value=elem;
if(pos==0){
    this->insert_beg(elem);
}
else{
    for(int i=0;i<=pos-1;i++){
    next=XOR(prev,curr->link);
    prev=curr;
    curr=next;
    }
    next=XOR(prev,curr->link);
    prev->link=XOR(XOR(prev->link,curr),temp);
    temp->link=XOR(prev,curr);
    curr->link=XOR(temp,next);
}
}
}
void delete_elem(int pos){
if(pos>this->length()-1||pos<0){
    cout<<"Invalid position\n";
}
else{
node* curr=new node();
node* prev=new node();
node* next=new node();
curr=head;
prev=nullptr;

if(pos==0){
     next=head->link;
     next->link=XOR(prev,XOR(next->link,curr));
     head=next;
}
else{
    if(pos!=this->length()-1){
    for(int i=0;i<=pos-1;i++){
    next=XOR(prev,curr->link);
    prev=curr;
    curr=next;
    }
    next=XOR(prev,curr->link);
    next->link=XOR(prev,XOR(next->link,curr));
    prev->link=XOR(XOR(prev->link,curr),next);
    free(curr);
    }
    else{
    for(int i=0;i<=pos-1;i++){
    next=XOR(prev,curr->link);
    prev=curr;
    curr=next;
    }
    prev->link=XOR(XOR(prev->link,curr),nullptr);
    free(curr);
    }
}
}
}
int get(int pos){
if(pos>this->length()-1||pos<0){
    cout<<"Invalid position\n";

}
else{
node* curr=new node();
node* prev=new node();
node* next=new node();
curr=head;
prev=nullptr;
if(pos==0){
    cout<<head->value<<endl;
    return head->value;
}
else{
    for(int i=0;i<=pos-1;i++){
    next=XOR(prev,curr->link);
    prev=curr;
    curr=next;
    }
    cout<<curr->value<<"\n";
    return curr->value;
}
}
}
void set(int pos,int elem){
if(pos>this->length()-1||pos<0){
    cout<<"Invalid position\n";
}
else{
node* curr=new node();
node* prev=new node();
node* next=new node();
curr=head;
prev=nullptr;
if(pos==0){
    head->value=elem;
    return;
}
else{
    for(int i=0;i<=pos-1;i++){
    next=XOR(prev,curr->link);
    prev=curr;
    curr=next;
    }
    curr->value=elem;
    return;
}
}
}
node* search(int key){
node* curr=new node();
node* prev=new node();
node* next=new node();
curr=head;
prev=nullptr;
    while(curr){
    if(curr->value==key){
        cout<<"It exist\n";
        return curr;
    }
    next=XOR(prev,curr->link);
    prev=curr;
    curr=next;
    }
cout<<"Nothing was founded\n";
return nullptr;
}
};
int main(){
list l;
//l.print();
//l.print();
l.append(4);
l.append(2);
l.append(5);
l.insert_beg(2);
l.insert_pos(10,0);
l.print();
l.delete_elem(4);
l.get(2);
l.search(1000);
l.print();
}
