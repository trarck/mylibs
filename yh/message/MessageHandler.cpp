//
//  MessageHandler.m
//  Message
//
//  Created by trarck trarck on 11-12-27.
//

#include "MessageHandler.h"

NS_YH_BEGIN

//消息处理
MessageHandler::~MessageHandler()
{
	//YHDEBUG("MessageHandler destroy begin ");
	YH_SAFE_RELEASE(_target);
    //YHDEBUG("MessageHandler destroy end ");
}

NS_YH_END