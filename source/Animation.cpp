#include "../include/Animation.h"
#include <string>
#include <stdio.h>
Animation::Animation()
{
}
void Animation::init(std::string n)
{
    name = n;
    length = 0;

}
void Animation::addAnim(int frame, int time){
    animPair a;
    a.frame = frame;
    a.time = time;
    data.push_back(a);
    length+=time;

}
int Animation::getFrame(int time){
    int a = time%length;

	for (int i = 0; i < data.size();){
        a-=data[i].time;
        printf("ah %d %d \n", a,i);
        if(a<=0)
        {
            return data[i].frame;
        }
    }
    return data[(data.size()-1)].frame;
}
Animation::~Animation()
{
    //dtor
}
