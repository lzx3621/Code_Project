#ifndef __AUDIOHELPER_H__
#define __AUDIOHELPER_H__

#include "cocos2d.h"


class CCAudioHelper 
{
public:
    CCAudioHelper();
    ~CCAudioHelper();
    virtual bool init() ;
    virtual bool playEffect(int id, bool bLoop = false);
    virtual bool pauseEffect(int id);
    virtual bool resumeEffect(int id);
    virtual bool stopEffect (int id);
    virtual bool playMusic(const std::string& name, bool bLoop = true);
    virtual void pauseMusic(std::string name);
    virtual void resumeMusic();
    virtual void stopMusic();
    virtual void preload();
    virtual void unload();
    virtual void pauseAllAudio();
    virtual void resumeAllAudio();
    static CCAudioHelper* getInstance();
    static void destroyInstance();
protected:
    void test();

    const int EFFECTMAX;
    std::vector<std::string> _effectFilePaths;
    std::unordered_map<std::string ,std::string> _musicFilePaths;
    std::vector<int> _effectsID;
    std::vector<int> _musicID;
    static CCAudioHelper *s_ptrInstance;
};

#endif // __AUDIOHELPER_H__
