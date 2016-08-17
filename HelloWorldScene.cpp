#include "HelloWorldScene.h"
#include "math.h"
#define key EventKeyboard::KeyCode

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
 
	this->setKeypadEnabled(true);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto frame_main = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("frame/MainScene.csb"));
	frame_main->retain();
	frame_main->setTag(TAG_FRAME_MAIN);
	this->addChild(frame_main);
	
	auto check = (CheckBox*)frame_main->getChildByTag(TAG_CHECK_BACK);
	check->addEventListener(CC_CALLBACK_2(HelloWorld::SelectOption, this));

	auto check_right = (CheckBox*)frame_main->getChildByTag(TAG_CHECK_RIGHT);
	check_right->addEventListener(CC_CALLBACK_2(HelloWorld::SelectOption, this));

	auto check_left = (CheckBox*)frame_main->getChildByTag(TAG_CHECK_LEFT);
	check_left->addEventListener(CC_CALLBACK_2(HelloWorld::SelectOption, this));

	map = (CCTMXTiledMap*)frame_main->getChildByTag(TAG_FRAME_MAP);

	CCTMXObjectGroup *objectGroup = map->objectGroupNamed("obj1");
	if (objectGroup == NULL) return false;
	ValueMap spawnPoint = objectGroup->getObject("Spawn");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();
	int w = spawnPoint["width"].asInt();
	int h = spawnPoint["height"].asInt();
	spawnx = x + w / 2;
	spawny = y + h / 2;

	car = (Sprite*)frame_main->getChildByTag(TAG_SPR_CAR);
	car->setPosition(ccp(spawnx, spawny));

	info = (Text*)frame_main->getChildByTag(TAG_TXT_INFO1);
	info2 = (Text*)frame_main->getChildByTag(TAG_TXT_INFO2);

	this->scheduleUpdate();

    return true;
}

double HelloWorld::getMinTurnRadius() {
	double normalMinRadius = 0.1;
	double maxSpeedBeforeGripLoss = 20;
	double minTurnRadius = 0;
	if (currentSpeed < maxSpeedBeforeGripLoss) {
		minTurnRadius = normalMinRadius;
	}
	else {
		double momentumRadiusAdjustment = pow(currentSpeed, 2) - maxSpeedBeforeGripLoss;
		minTurnRadius = normalMinRadius + momentumRadiusAdjustment;
	}

	return minTurnRadius;
}

double HelloWorld::getAngleOnTurnCircle(double radius, double velocity) {
	double distance = velocity * SPEED_TO_CAR_SPACE_FRAME;
	double circleCirumference = 2 * M_PI * radius;
	double distanceOfCirclePct = distance / circleCirumference;
	double angleTravelledAlongCircle = 360 * distanceOfCirclePct;
	double carTurnAngle = 90 - angleTravelledAlongCircle;
	return carTurnAngle;
}

double HelloWorld::getCarTurnAngle() {
	double rotationFactor = 0.6;
	double targetTurnAngle = getWheelAngle() * rotationFactor;
	double turnCircleMinRadius = getMinTurnRadius();
	double maxTurnAngle = getAngleOnTurnCircle(turnCircleMinRadius, currentSpeed);

	//if (abs(targetTurnAngle) > abs(maxTurnAngle)) return maxTurnAngle;
	//else return targetTurnAngle * currentSpeed * 0.004;
	return targetTurnAngle * currentSpeed / INC_SPEED *0.004;
}

void HelloWorld::setMode(bool mode)
{
	isBack = mode;
}

void HelloWorld::setMovement(int m) {
	movement = m;
}

void HelloWorld::setWheelAngle(double percent) {
	WheelAngle = percent;
}

double HelloWorld::getWheelAngle() {
	return WheelAngle;
}

void HelloWorld::ResetCar()
{
	currentSpeed = 0;
	movement = STEADY;
	setCarAngle(0);
	setWheelAngle(0); 
	car->setPosition(ccp(spawnx, spawny));
}

void HelloWorld::process(int type) {
	adjustSpeed(type);
	adjustPosition(type);
}

double HelloWorld::getCarAngle() {
	return car->getRotation();
}

void HelloWorld::setCarAngle(double angle)
{
	car->setRotation(angle);
}

double HelloWorld::getCarSpeed() {
	return currentSpeed;
}

void HelloWorld::adjustSpeed(int type) {
	double ACCELERATION, COAST_DECELERATION, DECELERATION;
	switch (type) {
	case ACCELERATING:
		if (currentSpeed >= MAX_SPEED*INC_SPEED) return;
		currentSpeed = MAX_SPEED*INC_SPEED;
		break;
	case COASTING:
		if (currentSpeed <= 0) {
			currentSpeed = 0;
			return;
		}
		COAST_DECELERATION = -0.75;
		currentSpeed = currentSpeed + COAST_DECELERATION;
		break;
	case DECELERATING:
		if (currentSpeed <= 0) {
			currentSpeed = 0;
			return;
		}
		DECELERATION = -3;
		currentSpeed = currentSpeed + DECELERATION;
		break;
	case STEADY:
		break;
	}
}

void HelloWorld::adjustPosition(int type) {
	double speedInGeometrySpace = currentSpeed *SPEED_TO_CAR_SPACE_FRAME;
	double wheelTurnAngle = getWheelAngle();
	double attemptedTurnAmount = getCarTurnAngle();

	if (abs(attemptedTurnAmount) > 8 || wheelTurnAngle*attemptedTurnAmount < 0) {
		if (wheelTurnAngle >= 0) attemptedTurnAmount = 0.5;
		else attemptedTurnAmount = -0.5;
	}
	
	double wheelTurnSpeedAttenuation = 1;
	if (currentSpeed > 15 * INC_SPEED) {
		double WHEEL_TURN_SPEED_ATTENUATION_FACTOR = 0.01;
		wheelTurnSpeedAttenuation = 1 - abs(WHEEL_TURN_SPEED_ATTENUATION_FACTOR * wheelTurnAngle / WHEEL_MAX_TURN_ANGLE);
	}

	if (type == ACCELERATING) {
		double a = getCarAngle() + attemptedTurnAmount;
	}

	double newCarAngle = getCarAngle() + attemptedTurnAmount;
	int INTnewCarAngle = (int)newCarAngle;
	
	newCarAngle = double(INTnewCarAngle % 360) + newCarAngle - (double)INTnewCarAngle;
	if (newCarAngle < 0) newCarAngle = 360.0 - newCarAngle;

	double xMovement = speedInGeometrySpace * sin(toRadians(newCarAngle));
	double yMovement = speedInGeometrySpace * cos(toRadians(newCarAngle));

	if (isBack) {
		yMovement *= -1;
		xMovement *= -1;
	}

	if (car->getPositionX()>640 || car->getPositionX() < 0) car->setPositionX(320);
	if (car->getPositionY()>640 || car->getPositionY() < 0) car->setPositionY(320);

	car->setPositionX(car->getPositionX() + xMovement);
	car->setPositionY(car->getPositionY() + yMovement);

	string str="X : ";
	str.append(int2string(car->getPositionX())+"\nY : ");
	str.append(int2string(car->getPositionY()) + "\nSpeed : ");
	str.append(int2string(currentSpeed) + "\nWheelAngle : ");
	str.append(int2string(getWheelAngle())+"\nCarAngle : ");
	str.append(int2string(getCarAngle())+"\nTurnAngle : ");
	str.append(int2string(attemptedTurnAmount));

	info->setString(str);

	setCarAngle(newCarAngle);
	currentSpeed = currentSpeed * wheelTurnSpeedAttenuation;

	if (CheckCollision()) {
		ResultDNA(1);
	}
}

bool HelloWorld::CheckCollision()
{
	int tmp1[] = { 0,0,0,1,-1,1,1,-1,-1 };
	int tmp2[] = { 0,1,-1,0,0,1,-1,1,-1 };
	int cx = car->getPositionX() / map->getTileSize().width;
	int cy = ((map->getMapSize().height*map->getTileSize().height) - car->getPositionY()) / map->getTileSize().height;
	TMXLayer *layer = map->getLayer("map");
	Rect carRect = car->getBoundingBox();

	for (int i = 0; i < 9; i++) {
		if (cx + tmp1[i] < layer->getLayerSize().width && cx + tmp1[i] >= 0 && cy + tmp2[i] >= 0 && cy + tmp2[i] <= layer->getLayerSize().height) {
			auto tile = (Sprite*)layer->getTileAt(ccp(cx + tmp1[i], cy + tmp2[i]));
			unsigned int tileGid = layer->tileGIDAt(ccp(cx + tmp1[i], cy + tmp2[i]));
			if (tileGid == 2) if (car->getBoundingBox().intersectsRect(tile->getBoundingBox())) return true;
		}
	}

	return false;
}

void HelloWorld::setBodyRoll(double speed, double turnAngle) {
	int direction = (turnAngle > 0) ? 1 : -1;
	double fudgeFactor = 3;
	double bodyRollAngle = speed * turnAngle * fudgeFactor;
	double MAX_BODY_ROLL_ANGLE = 3;
	//if (abs(bodyRollAngle) > MAX_BODY_ROLL_ANGLE) bodyRollAngle = direction * MAX_BODY_ROLL_ANGLE;
	setCarAngle(bodyRollAngle);
}

void HelloWorld::StartDNA()
{
	for (int i = 0; i < DNA_CNT; i++) {
		list[i] = new DNA();
		list[i]->CreateRandomData(DNA_RANGE);
	}
	NextDNA();
}

void HelloWorld::NextDNA()
{
	this->scheduleOnce(schedule_selector(HelloWorld::callback), DNA_INTERVER);
}

void HelloWorld::NextGeneration()
{
	DNA *nextG[DNA_CNT];
	double sum_fit = 0;
	double tmp1 = 0, tmp2 = 0;
	int flag = 0, res1 = -1, res2 = -1;
	sort(list, list + DNA_CNT, [](DNA* const &i, DNA* const &j)->bool {return i->fit > j->fit; });
	for (int i = 0; i < DNA_CNT; i++) sum_fit += list[i]->fit;
	std::random_device rdt;
	std::mt19937 mtt(rdt());
	std::uniform_real_distribution<double> randfit(0, sum_fit);

	for (int i = 0; i < DNA_CNT; i++) nextG[i] = new DNA();
	for (int i = 0; i < DNA_CNT / 10; i++) nextG[flag]->SetData(list[i]);
	for (int i = flag; i < DNA_CNT; i++) {
		tmp1 = randfit(mtt);
		tmp2 = randfit(mtt);
		res1 = res2 = -1;
		for (int j = 0; j < DNA_CNT; j++) {
			if (tmp1 <= list[j]->fit && res1 == -1) res1 = j;
			else tmp1 -= list[j]->fit;
			if (tmp2 <= list[j]->fit && res2 == -1) res2 = j;
			else tmp2 -= list[j]->fit;
		}
		if (res1 == res2) i--;
		else nextG[i]->SetData(list[res1]->CreateNextGene(list[res2]));
	}
	for (int i = 0; i < DNA_CNT; i++) list[i] = nextG[i];
	nowG++;
	NextDNA();
}

void HelloWorld::ResultDNA(int op)
{
	this->unschedule(schedule_selector(HelloWorld::callback));
	this->unschedule(schedule_selector(HelloWorld::callback2));
	list[nowDNA]->end = clock();
	list[nowDNA]->time = (double)(list[nowDNA]->end - list[nowDNA]->start) / CLOCKS_PER_SEC;
	list[nowDNA]->fit = MAX_SPEED*INC_SPEED*list[nowDNA]->time * (double)list[nowDNA]->now;
	//list[nowDNA]->fit = MAX_SPEED*list[nowDNA]->time;
	string str = "$$ Data Collision $$\n";
	if (op == 1) str = "$$ Data Collision $$\n";
	else if (op == 2) str = "$$ Data End $$\n";
	str.append("Generation : ");
	str.append(int2string(nowG) + "\nNowDNA : ");
	str.append(int2string(nowDNA) + "\nLength : ");
	str.append(int2string(list[nowDNA]->len) + "\nMutation : ");
	str.append(int2string(list[nowDNA]->isMutate) + "\nTime : ");
	str.append(double2string(list[nowDNA]->time) + "\nFitness : ");
	str.append(double2string(list[nowDNA]->fit));
	info2->setString(str);
	ResetCar();
	nowDNA++;
	if (nowDNA < DNA_CNT) NextDNA();
	else {
		nowDNA = 0;
		NextGeneration();
	}
}

void HelloWorld::callback(float delta)
{
	if (list[nowDNA]->now >= list[nowDNA]->gene.size()) {
		ResultDNA(2);
		return;
	}
	if (list[nowDNA]->isStart) movement = ACCELERATING;
	else {
		list[nowDNA]->isStart = true;
		movement = ACCELERATING; 
		list[nowDNA]->start = clock();
	}
	
	Drive dat = list[nowDNA]->gene.front();
	int len = list[nowDNA]->gene.size();
	double angle = list[nowDNA]->gene.at(list[nowDNA]->now).angle;
	double interval = list[nowDNA]->gene.at(list[nowDNA]->now).interval;
	setWheelAngle(angle);

	string str = "Generation : ";
	str.append(int2string(nowG) + "\nNowDNA : ");
	str.append(int2string(nowDNA) + "\nLength : ");
	str.append(int2string(len) + "\nWheelAngle : ");
	str.append(int2string(angle) + "\ninterval : ");
	str.append(int2string(interval));

	info2->setString(str);

	this->scheduleOnce(schedule_selector(HelloWorld::callback2), interval / INC_SPEED);
	list[nowDNA]->now++;
}

void HelloWorld::callback2(float delta)
{
	if (list[nowDNA]->now >= list[nowDNA]->gene.size()) {
		ResultDNA(2);
		return;
	}
	if (list[nowDNA]->isStart) movement = ACCELERATING;
	else {
		list[nowDNA]->isStart = true;
		movement = ACCELERATING;
		list[nowDNA]->start = clock();
	}

	Drive dat = list[nowDNA]->gene.front();
	int len = list[nowDNA]->gene.size();
	double angle = list[nowDNA]->gene.at(list[nowDNA]->now).angle;
	double interval = list[nowDNA]->gene.at(list[nowDNA]->now).interval;
	setWheelAngle(angle);

	string str = "Generation : ";
	str.append(int2string(nowG) + "\nNowDNA : ");
	str.append(int2string(nowDNA) + "\nLength : ");
	str.append(int2string(len) + "\nWheelAngle : ");
	str.append(int2string(angle) + "\ninterval : ");
	str.append(int2string(interval));

	info2->setString(str);

	this->scheduleOnce(schedule_selector(HelloWorld::callback), interval / INC_SPEED);
	list[nowDNA]->now++;
}

void HelloWorld::update(float delta) {
	process(movement);
}

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	switch (keycode) {
		//case key::KEY_UP_ARROW:movement = ACCELERATING; break;
	case key::KEY_DOWN_ARROW:movement = ACCELERATING; break;
	case key::KEY_UP_ARROW:StartDNA(); break;
	//case key::KEY_DOWN_ARROW:StartSimul(); break;
	case key::KEY_RIGHT_ARROW:setWheelAngle(-29); movement = ACCELERATING; break;
	case key::KEY_LEFT_ARROW:setWheelAngle(-2); movement = ACCELERATING; break;
	default:break;
	}
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	switch (keycode) {
	//case key::KEY_UP_ARROW:movement = COASTING; break;
	case key::KEY_DOWN_ARROW:movement = COASTING; break;
	case key::KEY_RIGHT_ARROW:setWheelAngle(0); movement = COASTING; break;
	case key::KEY_LEFT_ARROW:setWheelAngle(0); movement = COASTING; break;
	case key::KEY_ESCAPE:Director::getInstance()->end();
	}
}

void HelloWorld::SelectOption(Ref * pSender, CheckBox::EventType type)
{
	CheckBox* cbox = (CheckBox*)pSender;
	int tag = cbox->getTag();
	switch (type) {
	case CheckBox::EventType::SELECTED:
		if(tag==TAG_CHECK_BACK) isBack = true;
		if (tag == TAG_CHECK_RIGHT) setWheelAngle(30);
		if (tag == TAG_CHECK_LEFT) setWheelAngle(-26);
		break;
	case CheckBox::EventType::UNSELECTED:
		if (tag == TAG_CHECK_BACK) isBack = false;
		if (tag == TAG_CHECK_RIGHT) setWheelAngle(0);
		if (tag == TAG_CHECK_LEFT) setWheelAngle(0);
		break;
	default:
		break;
	}
}
