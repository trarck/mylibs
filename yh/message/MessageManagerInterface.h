//
//  对消息优先级的支持
//

#ifndef YHGE_MESSAGE_MESSAGEMANAGERINTERFACE_H_
#define YHGE_MESSAGE_MESSAGEMANAGERINTERFACE_H_

#include "Message.h"
#include "MessageHandler.h"

NS_YH_BEGIN

class MessageManagerInterface : public Ref {
public:
    
    /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
    
     /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
    
    virtual bool registerReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle ,Ref*  handleObject);

	virtual bool registerReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle);
	
	virtual bool registerReceiver(Ref* receiver ,unsigned int type ,Ref* sender,MessageHandler* handler);
	
	/**
	 * 检查是否已经注册某个消息。
	 */
	virtual bool isRegisterReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle ,Ref*  handleObject);

	virtual bool isRegisterReceiver(Ref* receiver ,unsigned int type ,Ref* sender,SEL_MessageHandler handle);

	/**
	 * 取消注册到接收者的处理对象的处理方法，该方法注册到发送者的某个消息。
	 */
	virtual void removeReceiver(Ref* receiver,unsigned int type ,Ref* sender,SEL_MessageHandler handle,Ref*  handleObject);

    /**
	 * 取消接收者的处理方法，该方法注册到发送者的某个消息。
	 */
	virtual void removeReceiver(Ref* receiver,unsigned int type ,Ref* sender,SEL_MessageHandler handle);

	/**
	 * 取消接收者注册到某个发送者的某个消息的所有处理方法。
	 */
    virtual void removeReceiver(Ref* receiver,unsigned int type ,Ref* sender);

	/**
	 * 取消接收者注册到某个消息的所有处理方法。
	 */
    virtual void removeReceiver(Ref* receiver,unsigned int type);

	/**
	 * 取消接收者的所以注册信息。
	 */
    virtual void removeReceiver(Ref* receiver);
    
	/**
	 * 取消接收者处理某个消息的某个方法。
	 */
    virtual void removeReceiver(Ref* receiver,unsigned int type ,SEL_MessageHandler handle);
    
	/**
	 * 取消接收者注册到发送者的任意消息的某个处理方法。
	 */
    virtual void removeReceiver(Ref* receiver,Ref* sender,SEL_MessageHandler handle);
    
	/**
	 * 取消接收者注册到发送者的所有消息的所有处理方法。
	 */
    virtual void removeReceiver(Ref* receiver,Ref* sender);

	/**
	 * 取消接收者注册到任意发送者任意消息的某个处理方法。
	 */
    virtual void removeReceiver(Ref* receiver,SEL_MessageHandler handle);
   	
    /**
	 * 取消注册到接收者的处理对象的所有处理方法，该方法注册到发送者的某个消息。
	 */
	virtual void removeReceiverAllHanldes(Ref* receiver,unsigned int type ,Ref* sender,Ref*  handleObject);

    /**
	 * 取消接收者处理某个消息的所有方法。
	 */
	virtual void removeReceiverAllHanldes(Ref* receiver,unsigned int type ,Ref*  handleObject);

    /**
	 * 取消接收者注册到发送者的任意消息的所有处理方法。
	 */
    virtual void removeReceiverAllHanldes(Ref* receiver,Ref* sender,Ref*  handleObject);

    /**
	 * 取消接收者注册到任意发送者任意消息的所有处理方法。
	 */
	virtual void removeReceiverAllHanldes(Ref* receiver,Ref*  handleObject);

	/**
	 * 发送消息。
	 */
	virtual void dispatchMessage(Message* message);

	/**
	 * 发送消息到某个接收者。
	 */
	virtual void dispatchMessage(Message* message ,Ref*  receiver);


	/**
	 * 发送消息的工具方法。
	 */
    virtual void dispatchMessage(unsigned int type ,Ref* sender ,Ref* receiver,Ref* data);
    
    /**
	 * 发送消息的工具方法。
	 */
    virtual void dispatchMessage(unsigned int type ,Ref* sender ,Ref* receiver);     
};

NS_YH_END

#endif // YHGE_MESSAGE_MESSAGEMANAGERINTERFACE_H_