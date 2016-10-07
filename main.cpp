#include <iostream>
#include "SDL2/SDL.h"
#include "GameObject.h"
#include "SDLFactory.h"
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;
using namespace game_Core;
using namespace game_SDL;
settings* s;

int main(int argc, char** argv) {
    struct stat info;
    int ret = 0;
    if(stat("Assets", &info)!=0){
        cout << "Cannot access Assets!\n";
        getchar();
        ret = -1;
    }
    else if(info.st_mode & S_IFDIR) {
        s = new settings();
        AbstractFactory *AF = new SDLFactory(s);
        GameObject *GO = new GameObject(AF, s);
        if (GO->init() == 1) {
            ret = GO->loop();
        }
        s->save();
        delete (GO);
        delete (AF);
        delete (s);
    }
    else{
        cout << "Assets not found!\n";
        ret = -1;
    }
    return ret;
}