// testyh.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>
#include <yh/yh.h>

USING_NS_YH;
typedef yh::ds::LinkedList<int> MyList;

typedef std::vector<int> MyListA;

static MyList gl;

void funa()
{
	for (MyList::iterator iter=gl.begin();iter!=gl.end();++iter)
	{
		printf("a:%d",*iter);
		if (*iter==4)
		{
			iter=gl.erase(iter);
			--iter;
			//break;
		}
	}
}

void funb()
{
	for (MyList::iterator iter=gl.begin();iter!=gl.end();++iter)
	{
		printf("b:%d",*iter);
		if (*iter==5)
		{
			iter=gl.erase(iter);
			--iter;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
    YHDEBUG("hello world");

	for (int i = 1; i < 10; i++)
	{
		gl.push_back(i);
	}
	
	//int j=0;
	//for (MyList::Iterator iter=l.begin();iter!=l.end();++iter)
	//{
	//	
	//	if (*iter==4)
	//	{
	//		MyList::Iterator tmp=iter;
	//		iter=l.erase(iter);
	//		l.erase(tmp+1);
	//		//l.erase(iter+2);
	//	}
	//	j++;
	//	printf("%d",*iter);
	//}
	//printf("\n");
	//for (MyList::Iterator iter=l.begin();iter!=l.end();++iter)
	//{
	//	printf("%d",*iter);
	//}

	//MyList copy=gl;

	for (MyList::reverse_iterator iter=gl.rbegin();iter!=gl.rend();++iter)
	{
		printf("%d",*iter);
		//MyList::iterator next=iter+1;
		if (*iter==4)
		{
			
			//funa();
			//
			//funb();
		}
		
		//iter=next;
	}

	printf("\n");

	for (MyList::iterator iter=gl.begin();iter!=gl.end();++iter)
	{
		printf("%d",*iter);
	}
    
    getchar();
    return 0;
}

