#include "CCAudioHelper.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace experimental;
CCAudioHelper * CCAudioHelper::s_ptrInstance = nullptr;

CCAudioHelper::CCAudioHelper():
    EFFECTMAX(17)
{
    _musicFilePaths["cateran"] = "Sound/Music/cateran.mp3";
    _musicFilePaths["general"] = "Sound/Music/general.mp3";
    _musicFilePaths["scholar"] = "Sound/Music/scholar.mp3";
    _musicFilePaths["waiter"] = "Sound/Music/waiter.mp3";
    _musicFilePaths["marry"] = "Sound/Music/marry.mp3";
    _musicFilePaths["normal"] = "Sound/Music/normal.mp3";
    CCLOG("CCAudioHelper create");
}

CCAudioHelper::~CCAudioHelper()
{
    unload();
    SimpleAudioEngine::end();
    CCLOG("CCAudioHelper delete");
}

bool CCAudioHelper::init()
{
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    return true;
}

void CCAudioHelper::preload()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    char effectBasePath[] = {"Sound/Effect/Android/"};
    char effectSuffix[] =  {".ogg"};
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    char effectBasePath[] = {"Sound/Effect/Window/"};
    char effectSuffix[] =  {".wav"};

#endif
    char filePath[64] = {};
    for (int i(1); i <= EFFECTMAX; i++)
    {
        _effectsID.push_back(0);
        sprintf(filePath, "%s%d%s", effectBasePath, i, effectSuffix);
        _effectFilePaths.push_back(filePath);
        if (CCFileUtils::getInstance()->isFileExist(filePath))
        {
            SimpleAudioEngine::getInstance()->preloadEffect(filePath);
        }
    }

    for (auto &iter:_musicFilePaths)
    {
        if (CCFileUtils::getInstance()->isFileExist(iter.second))
        {
            SimpleAudioEngine::getInstance()->preloadBackgroundMusic(iter.second.c_str());
        }
    }
}

void CCAudioHelper::unload()
{
    for (auto& iter:_effectFilePaths)
    {
        SimpleAudioEngine::getInstance()->unloadEffect(iter.c_str());
    }
    _effectFilePaths.clear();
}

CCAudioHelper* CCAudioHelper::getInstance()
{
    if (nullptr == s_ptrInstance)
    {
        s_ptrInstance = new CCAudioHelper();
        s_ptrInstance->init();
    }
    return s_ptrInstance;
}

void CCAudioHelper::destroyInstance()
{
    CC_SAFE_DELETE(s_ptrInstance);
}

bool CCAudioHelper::playEffect(int id, bool bLoop /*= false*/)
{
    if (0 <= --id && id < static_cast<int>(_effectFilePaths.size()))
    {
        _effectsID[id] = SimpleAudioEngine::getInstance()->playEffect(
            _effectFilePaths[id].c_str(),bLoop
            );
        return true;
    }
    return false;
}

bool CCAudioHelper::pauseEffect(int id)
{
    if (0 <= --id && id < static_cast<int>(_effectFilePaths.size()))
    {
        SimpleAudioEngine::getInstance()->pauseEffect(
             _effectsID[++id]);
        return true;
    }
    return false;
}

bool CCAudioHelper::stopEffect(int id)
{
    if (0 <= --id && id < static_cast<int>(_effectFilePaths.size()))
    {
        SimpleAudioEngine::getInstance()->stopEffect(
            _effectsID[++id]);
        return true;
    }
    return false;
}

bool CCAudioHelper::resumeEffect(int id)
{
    if (0 <= --id && id < static_cast<int>(_effectFilePaths.size()))
    {
        SimpleAudioEngine::getInstance()->resumeEffect(
            _effectsID[++id]);
        return true;
    }
    return false;
}

void CCAudioHelper::pauseAllAudio()
{
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void CCAudioHelper::resumeAllAudio()
{
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void CCAudioHelper::test()
{
    /*std::*/
}

bool CCAudioHelper::playMusic(const std::string& name, bool bLoop /*= true*/)
{
    auto iter = _musicFilePaths.find(name);
    if (_musicFilePaths.end() !=
        iter)
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(iter->second.c_str(), bLoop);
        return true;
    }
    else
    {
        return false;
    }
}

void CCAudioHelper::pauseMusic(std::string name)
{
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void CCAudioHelper::resumeMusic()
{
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void CCAudioHelper::stopMusic()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
