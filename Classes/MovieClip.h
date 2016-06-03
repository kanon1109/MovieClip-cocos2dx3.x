#ifndef _MOVIE_CLIP_
#define _MOVIE_CLIP_
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
class MovieClip:public Sprite
{
public:
	MovieClip();
	~MovieClip();

	//************************************
	// Method:    create					创建
	// Parameter: string & plist			动画plist地址
	// Parameter: string & textureFileName	纹理图片地址
	// Parameter: string & prefix			前缀（用于需要在一个plist动画里截取一段动作）
	// Returns:   MovieClip*
	//************************************
	static MovieClip* create(string &plist, string &textureFileName, string prefix = "");

	bool init(string &plist, string &textureFileName, string &prefix);

	//************************************
	// Method:    create						根据帧数据列表创建一个动画对象
	// Parameter: vector<string> & frameList	帧数据列表
	// Returns:   MovieClip*
	//************************************
	static MovieClip* create(vector<string> &frameList);

	bool initWithFrameList(vector<string> &frameList);
	//************************************
	// Method:    play				播放
	// Parameter: int fps			帧频
	// Parameter: int loopTimes		循环次数
	// Parameter: bool isReverse	是否倒放
	// Returns:   void
	//************************************
	void play(int fps = 30, int loopTimes = 1, bool isReverse = false);

	//暂停
	void stop();

	//************************************
	// Method:    gotoAndPlay		从某一帧开始播放
	// Parameter: int startFrame	起始帧
	// Parameter: int endFrame		结束帧
	// Parameter: int fps			帧频
	// Parameter: int loopTimes		循环播放次数
	// Parameter: bool isReverse	是否逆序播放
	// Returns:   void
	//************************************
	void gotoAndPlay(int startFrame, int endFrame, int fps = 30, int loopTimes = 1, bool isReverse = false);
	
	//************************************
	// Method:    gotoAndStop		停止在某一帧
	// Parameter: int frame			停止的帧数
	// Returns:   void
	//************************************
	void gotoAndStop(int frame);

	//************************************
	// Method:    setCompleteCallBack		添加播放完毕的回调监听
	// Parameter: SEL_CallFuncN selector	回调函数
	// Returns:   void
	//************************************
	void setCompleteCallBack(SEL_CallFuncN selector);

	//是否在播放状态
	bool getIsPlaying() const { return isPlaying; }

	//总帧数
	int getTotalFrames() const { return totalFrames; }

	//当前帧
	int getCurrentFrame() const { return currentFrame; }

	//获取当前帧数据（用于快速克隆一个movieClip对象）
	vector<string> getFrameList() const { return frameList; }
private:
	//是否在播放状态
	bool isPlaying;
	//循环次数
	int loopTimes;
	//帧频
	int fps;
	//帧数据
	vector<string> frameList;
	//总帧数
	int totalFrames;
	//起始帧
	int startFrame;
	//结束帧
	int endFrame;
	//当前帧
	int currentFrame;
	//是否倒放
	bool isReverse;
	//播放一次结束后的回调函数
	SEL_CallFuncN m_selector;
	//主循环
	void loop(float dt);
	//更新帧
	void updateFrame();
	//更新sprite的纹理
	void updateTexture();
};
#endif
