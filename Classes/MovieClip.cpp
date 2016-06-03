#include "MovieClip.h"
using namespace std;
MovieClip::MovieClip() 
:isPlaying(false),
isReverse(false),
totalFrames(0),
startFrame(0),
endFrame(0),
currentFrame(0),
loopTimes(-1),
m_selector(NULL)
{
}


MovieClip::~MovieClip()
{
}

MovieClip* MovieClip::create(string &plist, string &textureFileName, string prefix)
{
	MovieClip* mc = new MovieClip();
	if (mc && mc->init(plist, textureFileName, prefix))
	{
		mc->autorelease();
		return mc;
	}
	CC_SAFE_DELETE(mc);
	return NULL;
}

bool MovieClip::init(string &plist, string &textureFileName, string &prefix)
{
	//将纹理和plist加入帧缓存
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist, textureFileName);
	//获取plist的全路径
	string& fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
	//将plist转换成字典
	__Dictionary* dict = __Dictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());
	//获取plist中的frames字段的帧数据
	__Dictionary* frameDict = (__Dictionary*)dict->objectForKey("frames");
	//将frame存入list 并且排序
	list<string> keyList;
	DictElement* pElement = NULL;
	//ios平台下由于framesDict无法顺序读取，会造成动画错乱bug。增加平台判断排序keyList。
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	CCDICT_FOREACH(frameDict, pElement)
	{
		keyList.push_back(pElement->getStrKey());
	}
	keyList.sort();
	for (list<string>::iterator it = keyList.begin(); it != keyList.end(); ++it)
	{
		string spriteFrameName = *it;
		if (!prefix.empty())
		{
			//提取key的子字符串
			string subStr = spriteFrameName.substr(0, prefix.length());
			//比较子字符串的参数 如果相同则放入帧数组
			if (subStr.compare(prefix) == 0)
				this->frameList.push_back(spriteFrameName);
		}
		else
		{
			this->frameList.push_back(spriteFrameName);
		}
	}
#else
	//将帧的key存入数组
	CCDICT_FOREACH(frameDict, pElement)
	{
		string spriteFrameName = pElement->getStrKey();
		if (!prefix.empty())
		{
			//提取key的子字符串
			string subStr = spriteFrameName.substr(0, prefix.length());
			//比较子字符串的参数 如果相同则放入帧数组
			if (subStr.compare(prefix) == 0)
				this->frameList.push_back(spriteFrameName);
		}
		else
		{
			this->frameList.push_back(spriteFrameName);
		}
	}
#endif
	this->totalFrames = frameList.size();
	this->startFrame = 1;
	this->currentFrame = this->startFrame;
	this->endFrame = this->totalFrames;
	this->gotoAndStop(this->startFrame);
	//createWithContentsOfFileThreadSafe需要手动释放资源
	dict->release();
	return true;
}


MovieClip* MovieClip::create(vector<string> &frameList)
{
	MovieClip* mc = new MovieClip();
	if (mc && mc->initWithFrameList(frameList))
	{
		mc->autorelease();
		return mc;
	}
	CC_SAFE_DELETE(mc);
	return NULL;
}


bool MovieClip::initWithFrameList(vector<string> &frameList)
{
	this->frameList = frameList;
	this->totalFrames = frameList.size();
	this->startFrame = 1;
	this->currentFrame = this->startFrame;
	this->endFrame = this->totalFrames;
	this->gotoAndStop(this->startFrame);
	return true;
}

void MovieClip::play(int fps, int loopTimes /*= 1*/, bool isReverse /*= false*/)
{
	this->isPlaying = true;
	this->fps = fps;
	this->isReverse = isReverse;
	this->loopTimes = loopTimes;
	this->updateTexture();
	this->schedule(CC_SCHEDULE_SELECTOR(MovieClip::loop), (float)(1.0f / fps));
}

void MovieClip::stop()
{
	this->unschedule(CC_SCHEDULE_SELECTOR(MovieClip::loop));
}

void MovieClip::loop(float dt)
{
	this->updateTexture();
	this->updateFrame();
}


void MovieClip::updateFrame()
{
	if (!this->isReverse)
	{
		//正序播放
		this->currentFrame++;
		if (this->currentFrame > this->endFrame)
		{
			//一个动作播放完毕
			this->currentFrame = this->startFrame;
			//如果不是无限循环
			if (this->loopTimes > 0)
			{
				this->stop();
				//调用回调
				if (this->m_selector)
					(this->*m_selector)(this);
			}
		}
	}
	else
	{
		//逆序播放
		this->currentFrame--;
		if (this->currentFrame < this->startFrame)
		{
			//一个动作播放完毕
			this->currentFrame = this->endFrame;
			//如果不是无限循环
			if (this->loopTimes > 0)
			{
				this->stop();
				//调用回调
				if (this->m_selector) 
					(this->*m_selector)(this);
			}
		}
	}
}

void MovieClip::updateTexture()
{
	string& frameStr = this->frameList.at(this->currentFrame - 1);
	this->initWithSpriteFrameName(frameStr);
}

void MovieClip::setCompleteCallBack(SEL_CallFuncN selector)
{
	this->m_selector = selector;
}

void MovieClip::gotoAndPlay(int startFrame, int endFrame, int fps /*= 30*/, int loopTimes /*= 1*/, bool isReverse /*= false*/)
{
	if (startFrame < 1) startFrame = 1;
	if (startFrame > this->totalFrames) startFrame = this->totalFrames;
	if (endFrame < 1) endFrame = 1;
	if (endFrame > this->totalFrames) endFrame = this->totalFrames;
	this->startFrame = startFrame;
	this->endFrame = endFrame;
	this->play(fps, loopTimes, isReverse);
}

void MovieClip::gotoAndStop(int frame)
{
	this->stop();
	if (frame > this->totalFrames) frame = totalFrames;
	if (frame < 1) frame = 1;
	this->currentFrame = frame;
	this->updateTexture();
}



