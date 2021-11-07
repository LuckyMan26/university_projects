#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;
float integral(float(*)(float),float,float,int);
float integral1(float(*)(float),float,float,int);
double find_min(float(*)(float),float,float);
double find_max(float(*)(float),float,float);
double find_max_x(float(*)(float),float,float);
double find_min_x(float(*)(float),float,float);
float fourier_serie(float x,std::vector<float> vec1,std::vector<float> vec2,float y){
float res=y/2;
for(int i=0;i<50;++i){
res+=vec1[i]*sin((i+1)*x)+vec2[i]*sin((i+1)*x);
}
return res;
}
float f(float x){
    return exp(x);
}
float integral(float(*f)(float),float a,float b,int m){
    const int n=10000;
    const double width = (b-a)/n;
 double integral = 0;
    for(int step = 0; step < n; step++) {
        const double x1 = a + step*width;
        const double x2 = a + (step+1)*width;

        integral += 0.5*(x2-x1)*(f(x1)*sin(m*x1) + f(x2)*sin(m*x2));
    }

    return integral;
}
float integral1(float(*)(float),float a,float b,int m){
    const int n=10000;
    const double width = (b-a)/n;
 double integral = 0;
    for(int step = 0; step < n; step++) {
        const double x1 = a + step*width;
        const double x2 = a + (step+1)*width;

        integral += 0.5*(x2-x1)*(f(x1)*cos(m*x1) + f(x2)*cos(m*x2));
    }

    return integral;
}
double find_min(float(*f)(float),float a,float b){
double Min=f(a);
for(double i=a;i<=b;i+=0.001){
    if(f(i)<Min){
        Min=f(i);
    }
}
return Min;
}
double find_max(float(*f)(float),float a,float b){
double Max=f(a);
for(double i=a;i<=b;i+=0.001){
    if(f(i)>Max){
        Max=f(i);
    }
}
return Max;
}
double find_max_x(float(*f)(float),float a,float b){
double Max=f(a);
double something=a;
for(double i=a;i<=b;i+=0.001){
    if(f(i)>Max){
        Max=f(i);
        something=a;
    }
}
return something;
}
double find_min_x(float(*f)(float),float a,float b){

double Min=f(a);
double something=a;
for(double i=a;i<=b;i+=0.001){
    if(f(i)<Min){
        Min=f(i);
        something=a;
    }
}
return something;
}


int main(){
int w=500;
int h=500;
RenderWindow window(VideoMode(w,h),"task 18");
float a=-M_PI;
float b=M_PI;

const int n=10000;
    const double width = (b-a)/n;
 double Integral = 0;
    for(int step = 0; step < n; step++) {
        const double x1 = a + step*width;
        const double x2 = a + (step+1)*width;

        Integral += 0.5*(x2-x1)*(f(x1) + f(x2));
    }

 vector<float> array1;
float x;
x=Integral*(1/M_PI);
cout<<x/2<<endl;
 vector<float> array2;

for(int i=0;i<50;++i){
    array1.push_back((1/M_PI)*integral(f,a,b,i+1));
}
for(int i=0;i<50;++i){
    array2.push_back((1/M_PI)*integral1(f,a,b,i+1));
}
for(int i=0;i<50;i++){
    cout<<array1[i]<<" "<<array2[i]<<endl;
}
 double res=x/2;
VertexArray line(Lines, 2);
line[0].position = Vector2f(-500, 0);
line[0].color = Color::Blue;
line[1].position = Vector2f(500, 0);
VertexArray line2(Lines,2);
line2[0].position = Vector2f(0, 500);
line2[0].color = Color::Blue;
line2[1].position = Vector2f(0, -500);
View view;
view.setCenter(0,0);
view.setSize(2*M_PI,-2*M_PI);

while(window.isOpen()){
    Event event;


    while(window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            window.close();
        }
        if (event.type == sf::Event::KeyPressed)
{
    if (event.key.code == sf::Keyboard::Right)
    {
      view.move(1,0);
    }
    if (event.key.code == sf::Keyboard::Left)
    {
      view.move(-1,0);
    }
    if (event.key.code == sf::Keyboard::Up)
    {
      view.move(0,-1);
    }
    if (event.key.code == sf::Keyboard::Down)
    {
      view.move(0,1);
    }
}
if(event.type==Event::MouseWheelMoved){
    if(event.mouseWheel.delta>0){
        view.zoom(0.5);
    }
    if(event.mouseWheel.delta<0){
        view.zoom(2);
    }
}
    }
    window.setView(view);
    window.clear();
    window.draw(line);
    window.draw(line2);
    for(double i=-M_PI;i<=M_PI;i+=0.001){
        for(int j=0;j<50;j++){

             res+=array1[j]*sin((j+1)*i)+array2[j]*cos((j+1)*i);

        }
        Vertex point(Vector2f(i,res),Color::Red);
        Vertex point1(Vector2f(i,f(i)),Color::Blue);
      res=x/2;
      window.draw(&point,1,sf::Points);
      window.draw(&point1,1,sf::Points);
    }
    window.display();
}
const int n1=10000;
    const double width1 = (b-a)/n1;
 double Integral_mistake = 0;
    for(int step = 0; step < n; step++) {
        const double x1 = a + step*width;
        const double x2 = a + (step+1)*width;
        Integral_mistake += 0.5*(x2-x1)*(abs(f(x1)-fourier_serie(x1,array1,array2,x)) + abs(f(x2)-fourier_serie(x2,array1,array2,x)));
    }
cout<<"Integral mistake: "<<Integral_mistake;
int array[2]={};
cout<<endl;
cout<<array[0]<<" "<<array[1];

}


