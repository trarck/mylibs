//
//  Message.m
//  Message

//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "Message.h"

NS_YH_BEGIN


Message::~Message(void)
{
    //YHDEBUG("Message destroy begin");
	YH_SAFE_RELEASE_NULL(_sender);
	YH_SAFE_RELEASE_NULL(_receiver);
	YH_SAFE_RELEASE_NULL(_data);
	YH_SAFE_RELEASE_NULL(_extData);
    //YHDEBUG("Message destroy end");
}

NS_YH_END