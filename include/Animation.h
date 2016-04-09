#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <string>


struct animPair{
    int frame = 0;
    int time = 100;
};
class Animation
{
    public:
        Animation();
        virtual ~Animation();
        void init(std::string n);
        void addAnim(int frame, int time);
        void addAnim(int frameStart, int frameEnd, int time);
        int getFrame(int time);
        std::vector<animPair> data;
        std::string name;
        int length;
    protected:

    private:
};

#endif // ANIMATION_H
