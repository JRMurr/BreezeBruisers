#include "Animation.h"
#include <string>
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
    data.insert(a);
    length+=time;
}
int Animation::getFrame(int time){
    int a = time%length;
    for(int i = 0; i < data.size()){
        a-=data.at(i).time;
        if(a<=0)
        {
            return data.at(i).frame;
        }
    }
    return data.at(data.size()-1).frame;
}
Animation::~Animation()
{
    //dtor
}
