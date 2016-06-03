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
	// Method:    create					����
	// Parameter: string & plist			����plist��ַ
	// Parameter: string & textureFileName	����ͼƬ��ַ
	// Parameter: string & prefix			ǰ׺��������Ҫ��һ��plist�������ȡһ�ζ�����
	// Returns:   MovieClip*
	//************************************
	static MovieClip* create(string &plist, string &textureFileName, string prefix = "");

	bool init(string &plist, string &textureFileName, string &prefix);

	//************************************
	// Method:    create						����֡�����б���һ����������
	// Parameter: vector<string> & frameList	֡�����б�
	// Returns:   MovieClip*
	//************************************
	static MovieClip* create(vector<string> &frameList);

	bool initWithFrameList(vector<string> &frameList);
	//************************************
	// Method:    play				����
	// Parameter: int fps			֡Ƶ
	// Parameter: int loopTimes		ѭ������
	// Parameter: bool isReverse	�Ƿ񵹷�
	// Returns:   void
	//************************************
	void play(int fps = 30, int loopTimes = 1, bool isReverse = false);

	//��ͣ
	void stop();

	//************************************
	// Method:    gotoAndPlay		��ĳһ֡��ʼ����
	// Parameter: int startFrame	��ʼ֡
	// Parameter: int endFrame		����֡
	// Parameter: int fps			֡Ƶ
	// Parameter: int loopTimes		ѭ�����Ŵ���
	// Parameter: bool isReverse	�Ƿ����򲥷�
	// Returns:   void
	//************************************
	void gotoAndPlay(int startFrame, int endFrame, int fps = 30, int loopTimes = 1, bool isReverse = false);
	
	//************************************
	// Method:    gotoAndStop		ֹͣ��ĳһ֡
	// Parameter: int frame			ֹͣ��֡��
	// Returns:   void
	//************************************
	void gotoAndStop(int frame);

	//************************************
	// Method:    setCompleteCallBack		��Ӳ�����ϵĻص�����
	// Parameter: SEL_CallFuncN selector	�ص�����
	// Returns:   void
	//************************************
	void setCompleteCallBack(SEL_CallFuncN selector);

	//�Ƿ��ڲ���״̬
	bool getIsPlaying() const { return isPlaying; }

	//��֡��
	int getTotalFrames() const { return totalFrames; }

	//��ǰ֡
	int getCurrentFrame() const { return currentFrame; }

	//��ȡ��ǰ֡���ݣ����ڿ��ٿ�¡һ��movieClip����
	vector<string> getFrameList() const { return frameList; }
private:
	//�Ƿ��ڲ���״̬
	bool isPlaying;
	//ѭ������
	int loopTimes;
	//֡Ƶ
	int fps;
	//֡����
	vector<string> frameList;
	//��֡��
	int totalFrames;
	//��ʼ֡
	int startFrame;
	//����֡
	int endFrame;
	//��ǰ֡
	int currentFrame;
	//�Ƿ񵹷�
	bool isReverse;
	//����һ�ν�����Ļص�����
	SEL_CallFuncN m_selector;
	//��ѭ��
	void loop(float dt);
	//����֡
	void updateFrame();
	//����sprite������
	void updateTexture();
};
#endif
