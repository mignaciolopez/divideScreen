/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	auto sizeInpixels = Director::getInstance()->getWinSizeInPixels();
	auto size = Director::getInstance()->getWinSize();

	auto layer1 = Layer::create();
	auto camera1 = Camera::create();
	camera1->setPosition3D(Vec3(size.width / 2, size.height / 2, 700.0f));
	camera1->lookAt(Vec3::ZERO);
	camera1->setRotation3D(Vec3::ZERO);
	camera1->setCameraFlag(CameraFlag::USER1);
	layer1->addChild(camera1 , 1);
	this->addChild(layer1, 1);

	//Down Side part
	auto fboSize = Size(sizeInpixels.width, sizeInpixels.height / 2);
	auto fboDown = experimental::FrameBuffer::create(1, fboSize.width, fboSize.height);

	auto rtDown = experimental::RenderTarget::create(fboSize.width, fboSize.height);
	auto rtDSDown = experimental::RenderTargetDepthStencil::create(fboSize.width, fboSize.height);
	fboDown->attachRenderTarget(rtDown);
	fboDown->attachDepthStencilTarget(rtDSDown);

	
	auto camera2 = Camera::create();
	auto spriteDown = Sprite::createWithTexture(fboDown->getRenderTarget()->getTexture());
	spriteDown->setFlippedY(true);
	spriteDown->setPosition(0.0f, 0.0f);
	spriteDown->setAnchorPoint(Vec2(0.0f, 0.0f));
	spriteDown->setCameraMask(static_cast<int>(CameraFlag::USER1));
	layer1->addChild(spriteDown, 2);

	
	//camera2 = Camera::createPerspective(60, (GLfloat)fboSize.width / fboSize.height, 0.0f, 3000.0f);
	//camera2 = Camera::createOrthographic(fboSize.width, fboSize.height, 1.0f, 1000.0f);
	//
	camera2->setDepth(-1);
	camera2->setFrameBufferObject(fboDown);
	camera2->setCameraFlag(CameraFlag::USER2);

	auto layer2 = Layer::create();
	layer2->addChild(camera2);
	layer2->setCameraMask(static_cast<int>(CameraFlag::USER2));

	//experimental::Viewport vp = experimental::Viewport(0.0f, 0.0f, size.width, size.height / 2);
	//m_camera->setViewport(vp);

	camera2->setPosition3D(Vec3(0.f, 0.f, 700.0f));
	camera2->lookAt(Vec3::ZERO);
	camera2->setRotation3D(Vec3::ZERO);

	layer1->addChild(layer2, 2);
	
	

	//Up Side part
	auto fboUp = experimental::FrameBuffer::create(1, fboSize.width, fboSize.height);

	auto rtUp = experimental::RenderTarget::create(fboSize.width, fboSize.height);
	auto rtDSUp = experimental::RenderTargetDepthStencil::create(fboSize.width, fboSize.height);
	fboUp->attachRenderTarget(rtUp);
	fboUp->attachDepthStencilTarget(rtDSUp);


	auto camera3 = Camera::create();
	auto spriteUp = Sprite::createWithTexture(fboUp->getRenderTarget()->getTexture());
	spriteUp->setFlippedY(true);
	spriteUp->setPosition(0.0f, fboSize.height);
	spriteUp->setAnchorPoint(Vec2(0.0f, 0.0f));
	spriteUp->setCameraMask(static_cast<int>(CameraFlag::USER1));
	layer1->addChild(spriteUp, 3);


	//camera2 = Camera::createPerspective(60, (GLfloat)fboSize.width / fboSize.height, 0.0f, 3000.0f);
	//camera2 = Camera::createOrthographic(fboSize.width, fboSize.height, 1.0f, 1000.0f);
	//
	camera3->setDepth(-1);
	camera3->setFrameBufferObject(fboUp);
	camera3->setCameraFlag(CameraFlag::USER3);

	auto layer3 = Layer::create();
	layer3->addChild(camera3);
	layer3->setCameraMask(static_cast<int>(CameraFlag::USER3));

	//experimental::Viewport vp = experimental::Viewport(0.0f, 0.0f, size.width, size.height / 2);
	//m_camera->setViewport(vp);

	camera3->setPosition3D(Vec3(0.f, 0.f, 700.0f));
	camera3->lookAt(Vec3::ZERO);
	camera3->setRotation3D(Vec3::ZERO);

	layer1->addChild(layer3, 3);



    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    layer1->addChild(menu, 5);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    

    // add "HelloWorld" splash screen"
    auto player1 = Sprite::create("HelloWorld.png");
    if (player1 == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
		player1->setPosition(0, 0);

        // add the sprite as a child to this layer
        layer2->addChild(player1, 1);
		player1->setCameraMask(static_cast<int>(CameraFlag::USER2));
    }


	auto player2 = Sprite::create("HelloWorld.png");
	if (player2 == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		player2->setPosition(0, 0);

		// add the sprite as a child to this layer
		layer3->addChild(player2, 0);
		player2->setCameraMask(static_cast<int>(CameraFlag::USER3));
	}

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
