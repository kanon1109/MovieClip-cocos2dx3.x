#include "MovieClipTest.h"
#include "MovieClip.h"


MovieClipTest::MovieClipTest()
{
	string plist = "attack.plist";
	string textureFileName = "attack.png";
	MovieClip* mc = MovieClip::create(plist, textureFileName);
	auto size = Director::getInstance()->getWinSize();
	mc->setPosition(size.width / 2, size.height / 2);
	mc->setCompleteCallBack(CC_CALLFUNCN_SELECTOR(MovieClipTest::playCompete));
	mc->play(12, 1);
	CCLOG("getTotalFrames %d", mc->getTotalFrames());
	this->addChild(mc);

	mc = MovieClip::create(mc->getFrameList());
	mc->setPosition(size.width / 2 + mc->getContentSize().width, size.height / 2);
	mc->play(12, 0);
	this->addChild(mc);
}


MovieClipTest::~MovieClipTest()
{
}

void MovieClipTest::playCompete(Node* node)
{
	MovieClip* mc = (MovieClip*)node;
	mc->gotoAndPlay(2, 4);
}
