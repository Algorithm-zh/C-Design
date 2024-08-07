#include<iostream>
using namespace std;

//������Ļ���
class Communication
{
public:
	virtual void communicate() = 0;
	virtual ~Communication(){}
};
//����
class Speaker : public Communication
{
public:
	void communicate()
	{
		cout << "��ʼ˵��" << endl;
	}
};

//������
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
			cout << "�绰�濪ʼʵʱģ��ͨ����" << endl;
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
	Speaker* m_speaker = nullptr;//��������
	bool m_isStart = false;//���ؿ��ƴ���Ȩ��
};

int main8()
{

	//ֱ�ӽ���
	Communication* speaker = new Speaker;
	speaker->communicate();
	delete speaker;
	//ͨ���绰�潻��
	cout << "========================" << endl;
	speaker = new DenDenMuShi;
	speaker->communicate();
	delete speaker;


	return 0;
}