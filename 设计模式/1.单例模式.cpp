#include<iostream>
#include<mutex>
#include<atomic>
#include<queue>
#include<thread>
using namespace std;

/*
��һ����Ŀ�У�ȫ�ַ�Χ�ڣ�ĳ�����ʵ�����ҽ���һ����
ͨ�����Ψһʵ��������ģ���ṩ���ݵ�ȫ�ַ��ʣ�
����ģʽ�ͽе���ģʽ��
*/

//����һ������ģʽ���������
//��Ҫ���������ȥ������Ĺ��캯��
//����ģʽ--->�������ʱ�򴴽���������
//�ڶ��̵߳ĳ�����û���̰߳�ȫ���⣬���߳̿���ͬʱ���ʵ�������
#if 0
class TaskQueue
{
public:
	//TaskQueue() = delete;//1.deleteֱ�ӽ���ɾ��
	TaskQueue(const TaskQueue& t) = delete;
	TaskQueue& operator = (const TaskQueue& t) = delete;
	static TaskQueue* getInstance()
	{
		return m_taskQ;
	}
	void print()
	{
		cout << "��������ĳ�Ա����" << endl;
	}

private:
	//2.�����Բ������ʵ���Ĺ��캯��Ȩ����Ϊ˽��
	TaskQueue() = default;//default��������ΪĬ����Ϊ
	//TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator = (const TaskQueue& t) = default;
	//ֻ��ͨ���������ʾ�̬���Ի򷽷�
	static TaskQueue* m_taskQ;//��̬������Ψһ�ģ�������
};
//�Ե����Ķ�����г�ʼ��
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;
#endif


//����ģʽ-->ʲôʱ��ʹ���������������ʹ�õ�ʱ����ȥ������Ӧ��ʵ��
#if 0
class TaskQueue
{
public:
	//TaskQueue() = delete;//1.deleteֱ�ӽ���ɾ��
	TaskQueue(const TaskQueue& t) = delete;
	TaskQueue& operator = (const TaskQueue& t) = delete;
	static TaskQueue* getInstance()
	{	//���߳�ʱ�����ܻ�new�����ʵ����
		//����һ����Ҫ�ӻ�����,Ч��̫�ͣ�ֻ��ͬ��ִ��
		//��������˫�ؼ������ + ԭ�ӱ�������ֹ�ײ�ִ��ʱ˳����ҵ����߳�ֱ��ʹ��δ��ʼ�����ڴ�����
		//��taskq��ԭ�ӱ�����ȡ��
		TaskQueue* task = m_taskQ.load();
		if (task == nullptr)
		{
			m_mutex.lock();
			TaskQueue* task = m_taskQ.load();//��ֹ�����߳��Ѿ����new����
			if (task == nullptr)
			{
				task = new TaskQueue;//���ú�����ʱ���ٴ���ʵ������ʡ�ռ�
				m_taskQ.store(task);//���浽ԭ�ӱ�����
			}
			m_mutex.unlock();
		}
		return task;
	}
	void print()
	{
		cout << "��������ĳ�Ա����" << endl;
	}

private:
	//2.�����Բ������ʵ���Ĺ��캯��Ȩ����Ϊ˽��
	TaskQueue() = default;//default��������ΪĬ����Ϊ
	//TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator = (const TaskQueue& t) = default;
	//ֻ��ͨ���������ʾ�̬���Ի򷽷�
	//static TaskQueue* m_taskQ;//��̬������Ψһ�ģ�������
	static mutex m_mutex;
	static atomic<TaskQueue*> m_taskQ;//ʹ��atomic��ָ��ŵ�ԭ�ӱ�����
};
//�Ե����Ķ�����г�ʼ��
//TaskQueue* TaskQueue::m_taskQ = nullptr;
atomic<TaskQueue*> TaskQueue::m_taskQ;
mutex TaskQueue::m_mutex;//��Ҫ����������(�����ʼ����
#endif

#if 0
//����ģʽ
//ʹ�þ�̬�ľֲ��������̰߳�ȫ���⣨����������֧��C++11��
//���ָ���߼�����һ��δ����ʼ�����������������в���ִ��Ӧ���ȴ��ñ�����ɳ�ʼ����
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
		cout << "��������ĳ�Ա����" << endl;
	}

private:
	TaskQueue() = default;//default��������ΪĬ����Ϊ
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
		cout << "��������ĳ�Ա����" << endl;
	}
	//�ж���������Ƿ�Ϊ��
	bool isEmpty()
	{
		//ʹ��lock_guard����
		lock_guard<mutex> locker(m_mutex);
		bool flag = m_data.empty();
		return flag;
	}
	//�������
	void addTask(int node)
	{
		lock_guard<mutex> locker(m_mutex);
		m_data.push(node);
	}
	//ɾ������
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
	//ȡ��һ������
	int takeTask()
	{
		lock_guard<mutex> locker(m_mutex);
		if (m_data.empty())return -1;
		return m_data.front();
	}

private:
	TaskQueue() = default;
	static TaskQueue* m_taskQ;
	//�����������
	queue<int> m_data;
	mutex m_mutex;
};
//�Ե����Ķ�����г�ʼ��
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;
#endif



int main1()
{ 

	TaskQueue* taskQ = TaskQueue::getInstance();

	//������
	thread t1([=]() {
		for (int i = 0; i < 10; i++)
		{
			taskQ->addTask(i + 100);
			cout << " push data : " << i + 100 << ", threadId: " <<
				this_thread::get_id() << endl;
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	});


	//������
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

	//�������߳�
	t1.join();
	t2.join();

	return 0;
}