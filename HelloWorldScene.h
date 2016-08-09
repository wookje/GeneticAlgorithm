#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <time.h>
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "DNA.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

#define WHEEL_MAX_TURN_ANGLE 35.0
//#define SPEED_TO_CAR_SPACE_FRAME 0.005
#define SPEED_TO_CAR_SPACE_FRAME 0.05
#define MAX_SPEED 50
#define ACCELERATING 1
#define DECELERATING 2
#define COASTING 3
#define STEADY 4

#define TAG_FRAME_MAIN 1
#define TAG_FRAME_MAP 10
#define TAG_SPR_CAR 11
#define TAG_TXT_INFO1 12
#define TAG_TXT_INFO2 13
#define TAG_CHECK_BACK 15
#define TAG_CHECK_LEFT 16
#define TAG_CHECK_RIGHT 17

#define DNA_CNT 10
#define DNA_RANGE 10
#define DNA_INTERVER 5.0f

class HelloWorld : public cocos2d::Layer
{
private:
	DNA *list[DNA_CNT];
	Sprite* car;
	Text *info;
	Text *info2;
	CCTMXTiledMap *map;
	int spawnx, spawny;
	int nowDNA = 0;
	double currentSpeed=0;
	double speed=0;
	double WheelAngle=0;
	double WheelSpeed=0;
	int movement = 0;
	bool isBack = false;
	int nowG = 0;

public:

    static cocos2d::Scene* createScene();

    virtual bool init();
    CREATE_FUNC(HelloWorld);

	double getMinTurnRadius();
	double getAngleOnTurnCircle(double radius, double velocity);
	double getCarTurnAngle();
	void setMode(bool mode);
	void setMovement(int m);
	void setWheelAngle(double percent);
	double getWheelAngle();
	void ResetCar();
	void process(int type);
	double getCarAngle();
	void setCarAngle(double angle);
	double getCarSpeed();
	void adjustSpeed(int type);
	void adjustPosition(int type);
	void setBodyRoll(double speed, double turnAngle);
	bool CheckCollision();

	void StartDNA();
	void NextDNA();
	void NextGeneration();
	void ResultDNA(int op);

	void callback(float delta);
	void callback2(float delta);
	void update(float delta);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	void SelectOption(Ref * pSender, CheckBox::EventType type);

	bool comp(const DNA* &i, const DNA* &j) {
		return i->fit > j->fit;
	}

	double toRadians(double angdeg) {
		return angdeg / 180.0 * M_PI;
	}

	string int2string(int number)
	{
		ostringstream convStream;
		convStream << number;
		return convStream.str();
	}

	string double2string(double num) {
		ostringstream convStream;
		convStream << num;
		return convStream.str();
	}
};

#endif // __HELLOWORLD_SCENE_H__
