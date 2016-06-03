#pragma once
#ifndef _MOVIE_CLIP_TEST_
#define _MOVIE_CLIP_TEST_
#include "cocos2d.h"
USING_NS_CC;
class MovieClipTest :
	public Scene
{
public:
	MovieClipTest();
	~MovieClipTest();
	CREATE_FUNC(MovieClipTest);

private:
	void playCompete(Node* node);
};
#endif // _MOVIE_CLIP_TEST_
