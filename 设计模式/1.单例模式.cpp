#include<iostream>
#include<mutex>
#include<atomic>
#include<queue>
#include<thread>
using namespace std;

/*
在一个项目中，全局范围内，某个类的实例有且仅有一个，
通过这个唯一实例向其他模块提供数据的全局访问，
这种模式就叫单例模式。
*/

//定义一个单例模式的任务队列
//不要让类的外面去调用类的构造函数
//饿汉模式--->定义类的时候创建单例对象
//在多线程的场景下没有线程安全问题，多线程可以同时访问单例对象
#if 0
class TaskQueue
{
public:
	//TaskQueue() = delete;//1.delete直接将其删除
	TaskQueue(const TaskQueue& t) = delete;
	TaskQueue& operator = (const TaskQueue& t) = delete;
	static TaskQueue* getInstance()
	{
		return m_taskQ;
	}
	void print()
	{
		cout << "单例对象的成员函数" << endl;
	}

private:
	//2.将可以产生多个实例的构造函数权限设为私有
	TaskQueue() = default;//default就是设置为默认行为
	//TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator = (const TaskQueue& t) = default;
	//只能通过类名访问静态属性或方法
	static TaskQueue* m_taskQ;//静态变量，唯一的，属于类
};
//对单例的对象进行初始化
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;
#endif

//懒汉模式-->什么时候使用这个单例对象，在使用的时候再去创建对应的实例
#if 0
class TaskQueue
{
public:
	//TaskQueue() = delete;//1.delete直接将其删除
	TaskQueue(const TaskQueue& t) = delete;
	TaskQueue& operator = (const TaskQueue& t) = delete;
	static TaskQueue* getInstance()
	{	//多线程时，可能会new出多个实例，
		//方法一：需要加互斥锁,效率太低，只能同步执行
		//方法二：双重检查锁定 + 原子变量（防止底层执行时顺序打乱导致线程直接使用未初始化的内存区域）
		//将taskq从原子变量中取出
		TaskQueue* task = m_taskQ.load();
		if (task == nullptr)
		{
			m_mutex.lock();
			TaskQueue* task = m_taskQ.load();//防止其它线程已经完成new操作
			if (task == nullptr)
			{
				task = new TaskQueue;//调用函数的时候再创建实例，节省空间
				m_taskQ.store(task);//保存到原子变量中
			}
			m_mutex.unlock();
		}
		return task;
	}
	void print()
	{
		cout << "单例对象的成员函数" << endl;
	}

private:
	//2.将可以产生多个实例的构造函数权限设为私有
	TaskQueue() = default;//default就是设置为默认行为
	//TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator = (const TaskQueue& t) = default;
	//只能通过类名访问静态属性或方法
	//static TaskQueue* m_taskQ;//静态变量，唯一的，属于类
	static mutex m_mutex;
	static atomic<TaskQueue*> m_taskQ;//使用atomic将指针放到原子变量里
};
//对单例的对象进行初始化
//TaskQueue* TaskQueue::m_taskQ = nullptr;
atomic<TaskQueue*> TaskQueue::m_taskQ;
mutex TaskQueue::m_mutex;//需要在外面声明(无需初始化）
#endif

#if 0
//懒汉模式
//使用静态的局部对象解决线程安全问题（编译器必须支持C++11）
//如果指令逻辑进入一个未被初始化的声明变量，所有并发执行应当等待该变量完成初始化。
class TaskQueue
{
public:
	TaskQueue(const TaskQueue& t) = delete;
	TaskQueue& operator = (const TaskQueue& t) = delete;
	static TaskQueue* getInstance()
	{	
		static TaskQueue task;
		return &task;
	}
	void print()
	{
		cout << "单例对象的成员函数" << endl;
	}

private:
	TaskQueue() = default;//default就是设置为默认行为
};
#endif


#if 1
class TaskQueue
{
public:
	TaskQueue(const TaskQueue& t) = delete;
	TaskQueue& operator = (const TaskQueue& t) = delete;
	static TaskQueue* getInstance()
	{
		return m_taskQ;
	}
	void print()
	{
		cout << "单例对象的成员函数" << endl;
	}
	//判断任务队列是否为空
	bool isEmpty()
	{
		//使用lock_guard加锁
		lock_guard<mutex> locker(m_mutex);
		bool flag = m_data.empty();
		return flag;
	}
	//添加任务
	void addTask(int node)
	{
		lock_guard<mutex> locker(m_mutex);
		m_data.push(node);
	}
	//删除任务
	bool popTask()
	{
		lock_guard<mutex> locker(m_mutex);
		if (m_data.empty())
		{
			return false;
		}
		m_data.pop();
		return true;
	}
	//取出一个任务
	int takeTask()
	{
		lock_guard<mutex> locker(m_mutex);
		if (m_data.empty())return -1;
		return m_data.front();
	}

private:
	TaskQueue() = default;
	static TaskQueue* m_taskQ;
	//定义任务队列
	queue<int> m_data;
	mutex m_mutex;
};
//对单例的对象进行初始化
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;
#endif



int main1()
{ 

	TaskQueue* taskQ = TaskQueue::getInstance();

	//生产者
	thread t1([=]() {
		for (int i = 0; i < 10; i++)
		{
			taskQ->addTask(i + 100);
			cout << " push data : " << i + 100 << ", threadId: " <<
				this_thread::get_id() << endl;
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	});


	//消费者
	thread t2([=]() {
		this_thread::sleep_for(chrono::milliseconds(500));
		while(!taskQ->isEmpty())
		{
			int num = taskQ->takeTask();
			cout << " take data : " << num << ", threadId: " <<
				this_thread::get_id() << endl;
			taskQ->popTask();
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
	});

	//阻塞主线程
	t1.join();
	t2.join();

	return 0;
}