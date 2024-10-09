#include<iostream>
using namespace std;

//代理类的基类
class Communication
{
public:
	virtual void communicate() = 0;
	virtual ~Communication(){}
};
//子类
class Speaker : public Communication
{
public:
	void communicate()
	{
		cout << "开始说话" << endl;
	}
};

//代理类
class DenDenMuShi : public Communication
{
public:
	DenDenMuShi()
	{
		m_isStart = true;
		m_speaker = new Speaker;
	}
	bool isStart()
	{
		return m_isStart;
	}
	void setStart(bool flag)
	{
		m_isStart = flag;
	}
	void communicate() override
	{
		if (m_isStart)
		{
			cout << "电话虫开始实时模仿通话者" << endl;
			m_speaker->communicate();

		}
	}
	~DenDenMuShi()
	{
		if (m_speaker)
		{
			delete m_speaker;
		}
	}
private:
	Speaker* m_speaker = nullptr;//被代理人
	bool m_isStart = false;//开关控制代理权限
};

int main8()
{

	//直接交流
	Communication* speaker = new Speaker;
	speaker->communicate();
	delete speaker;
	//通过电话虫交流
	cout << "========================" << endl;
	speaker = new DenDenMuShi;
	speaker->communicate();
	delete speaker;


	return 0;
}