
#ifndef __Bridge_H__
#define __Bridge_H__

#include "cocos2d.h"
using namespace cocos2d;
//creating a class representing every image in the layer in other word every square in the layer surface and walls
class bridge : public Sprite
{
public:
	//this bool determins if the sprite has been clamed
	bool isClaimed;

	//constructor 
	bridge();
	//this is where we initiate the sprite with a file path,
	static bridge* bridgeinit();


};
#endif