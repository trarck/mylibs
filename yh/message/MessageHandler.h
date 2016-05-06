//
// 执行消息的函数句柄
//

#ifndef YHGE_MESSAGE_MESSAGEHANDLER_H_
#define YHGE_MESSAGE_MESSAGEHANDLER_H_

#include <functional>
#include "../YHMacros.h"
#include "../base/Ref.h"

NS_YH_BEGIN

class Message;

//定义处理函数类型
typedef void (Ref::*SEL_MessageHandler)(Message*);
#define MESSAGE_SELECTOR(_SELECTOR) static_cast<yh::SEL_MessageHandler>(&_SELECTOR)

class MessageHandler : public Ref {
public:
    
	MessageHandler()
		:_target(NULL),
		 _handle(NULL),
		 _function(nullptr)
	{
		//YHDEBUG("MessageHandler create");
	}

    ~MessageHandler();

	Ref* getTarget()
	{
		return _target;
	}

	void setTarget(Ref* pTarget)
	{
		YH_SAFE_RETAIN(pTarget);
		YH_SAFE_DELETE(_target);
		_target=pTarget;
	}

	SEL_MessageHandler getHandle()
	{
		return _handle;
	}

	void setHandle(SEL_MessageHandler handle)
	{
		_handle=handle;
	}

	bool initWithTarget(Ref* pTarget,SEL_MessageHandler handle)
	{
		setTarget(pTarget);
		_handle=handle;
		return true;
	}

	bool initWithFunction(const std::function<void(Message*)> &func)
	{
		_function=func;
		return true;
	}

	void execute(Message *msg)
	{
		if(_handle){
			(_target->*_handle)(msg);
		}else if (_function){
			_function(msg);
		}
	}

private:
	Ref* _target;
	SEL_MessageHandler _handle;

	std::function<void(Message*)> _function;
};


NS_YH_END

#endif  // YHGE_MESSAGE_MESSAGEHANDLER_H_
