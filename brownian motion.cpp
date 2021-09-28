#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace sf;

struct PARTICLE
{
CircleShape st;
PARTICLE(double x,double y,int r){
st.setRadius(r);
st.setPosition(x,y);
st.setOrigin(r,r);
st.setFillColor(Color::Red);
}
};
float getDistance(float x1,float y1,float x2,float y2){
float distance_x=(x2-x1);
float distance_y=(y2-y1);
return (sqrt(distance_x*distance_x+distance_y*distance_y));
}
int main(){
    srand(time(NULL));
    vector<PARTICLE> p;
    double array[50][2];
    int r=10;
    for(int i=0;i<50;i++){
      double x=rand()%1000;
      double y=rand()%1000;
      double vx=(1+rand()%20)/100.0;
      double vy=(1+rand()%20)/100.0;
       array[i][0]=vx;
      array[i][1]=vy;
      p.push_back(PARTICLE(x,y,r));
    }
int w=1000;
int h=1000;

 RenderWindow window(VideoMode( w,  h), "Brownian Motion");
 while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

          int j=-1;
          int x=0;
        for(vector<PARTICLE>::iterator i=p.begin();i!=p.end();++i){

j++;
         i->st.move(array[j][0],array[j][1]);

         if(i->st.getPosition().x>w-r){
                    array[j][0]=- array[j][0];
                    i->st.setPosition(w-r,i->st.getPosition().y);
                 }
        if(i->st.getPosition().x<r){

                    array[j][0]=-array[j][0];
                    i->st.setPosition(r,i->st.getPosition().y);
                 }
                    if(i->st.getPosition().y<r){
                    array[j][1]=-array[j][1];
                    i->st.setPosition( i->st.getPosition().x,r);
                 }
         if(i->st.getPosition().y>(h-r-50)){
                        array[j][1]=-array[j][1];
                        i->st.setPosition( i->st.getPosition().x,h-r-50);
                 }
             window.draw(i->st);

             for(vector<PARTICLE>::iterator k=p.begin();k!=p.end();++k){

                 if((getDistance(i->st.getPosition().x,i->st.getPosition().y,k->st.getPosition().x,k->st.getPosition().y)<=2*r+0.1)&&(i!=k)){
                  float posx= k->st.getPosition().x-i->st.getPosition().x;
                float posy=k->st.getPosition().y-i->st.getPosition().y;

                if((posx>=0)&&(posy>=0)){
                     i->st.setPosition( i->st.getPosition().x-0.01,i->st.getPosition().y-0.01);
                }
                if((posx>=0)&&(posy<=0)){
                     i->st.setPosition(i->st.getPosition().x-0.01,i->st.getPosition().y+0.01);
                }
                if((posx<=0)&&(posy<=0)){
                     i->st.setPosition(i->st.getPosition().x+0.01,i->st.getPosition().y+0.01);
                }
                if((posx<=0)&&(posy>=0)){
                     i->st.setPosition(i->st.getPosition().x+0.01,i->st.getPosition().y-0.01);
                }
                    float Dx=(i->st.getPosition().x-k->st.getPosition().x);
                    float Dy=(i->st.getPosition().y-k->st.getPosition().y);
                    float d=getDistance(i->st.getPosition().x,i->st.getPosition().y,k->st.getPosition().x,k->st.getPosition().y);
                    float s=Dx/d;
                    float c=Dy/d;
                    float Vn1=array[x][0]*s+array[x][1]*c;
                    float Vn2=array[j][0]*s+array[j][1]*c;
                    float Vt1=-array[x][0]*c+array[x][1]*s;
                    float Vt2=-array[j][0]*c+array[j][1]*s;
                    swap(Vn1,Vn2);
                    array[j][0]=Vn2*s-Vt2*c;
                    array[j][1]=Vn2*c+Vt2*s;
                    array[x][0]=Vn1*s-Vt1*c;
                    array[x][1]=Vn1*c+Vt1*s;
                    i->st.setFillColor(Color::Green);
                    k->st.setFillColor(Color::Blue);

                 }
                  x++;
             }
            x=0;

        }
        j=-1;
        window.display();
        window.clear();
        }
        return 0;
}



