#include<iostream>
using namespace std;


#if 0
//�����������è���ǹ�����ϵ
//�����
class Foreigner
{
public:
	virtual string confession() = 0;
	void setResult(string res)
	{
		cout << "Panda say:" << res << endl;
	}
	virtual ~Foreigner(){}
};

class American : public Foreigner
{
public:
	string confession() override
	{
		return "������";
	}
};
class French : public Foreigner
{
public:
	string confession() override
	{
		return "������";
	}
};

class Panda
{
public:
	void recvMessage(string msg)
	{
		cout << msg << endl;
	}
	string sendMessage()
	{
		return string("����ԭ��");
	}
};

//��������
//�����������
class AbstractChopper
{
public:
	AbstractChopper(Foreigner* foreigner) : m_foreigner(foreigner){}
	virtual void translateToPanda() = 0;
	virtual void translateToHuman() = 0;
	virtual ~AbstractChopper(){}
protected:
	Foreigner* m_foreigner;
	Panda m_panda;
};

class EnglishCopper :public AbstractChopper
{
public:
	using AbstractChopper::AbstractChopper;//�̳����еĹ��캯��
	void translateToPanda()
	{
		string msg = m_foreigner->confession();
		//�������ԣ������ݴ��ݸ���è
		m_panda.recvMessage("������˵��" + msg);
	}
	void translateToHuman()
	{
		string msg = m_panda.sendMessage();
		//����è����ת��ΪӢ����ݸ������
		m_foreigner->setResult("������" + msg);
	}
};

class FrenchCopper :public AbstractChopper
{
public:
	using AbstractChopper::AbstractChopper;//�̳����еĹ��캯��
	void translateToPanda()
	{
		string msg = m_foreigner->confession();
		//�������ԣ������ݴ��ݸ���è
		m_panda.recvMessage("������˵��" + msg);
	}
	void translateToHuman()
	{
		string msg = m_panda.sendMessage();
		//����è����ת��ΪӢ����ݸ������
		m_foreigner->setResult("������" + msg);
	}
};

#endif



#if 1
//�����������è���Ǽ̳й�ϵ
//�����
class Foreigner
{
public:
	virtual string confession() = 0;
	void setResult(string res)
	{
		cout << "Panda say:" << res << endl;
	}
	virtual ~Foreigner() {}
};

class American : public Foreigner
{
public:
	string confession() override
	{
		return "������";
	}
};
class French : public Foreigner
{
public:
	string confession() override
	{
		return "������";
	}
};

class Panda
{
public:
	void recvMessage(string msg)
	{
		cout << msg << endl;
	}
	string sendMessage()
	{
		return string("����ԭ��");
	}
};

//��������
//�����������
class AbstractChopper : public Panda
{
public:
	AbstractChopper(Foreigner* foreigner) : m_foreigner(foreigner) {}
	virtual void translateToPanda() = 0;
	virtual void translateToHuman() = 0;
	virtual ~AbstractChopper() {}
protected:
	Foreigner* m_foreigner;
};

class EnglishCopper :public AbstractChopper
{
public:
	using AbstractChopper::AbstractChopper;//�̳����еĹ��캯��
	void translateToPanda()
	{
		string msg = m_foreigner->confession();
		//�������ԣ������ݴ��ݸ���è
		recvMessage("������˵��" + msg);
	}
	void translateToHuman()
	{
		string msg = sendMessage();
		//����è����ת��ΪӢ����ݸ������
		m_foreigner->setResult("������" + msg);
	}
};

class FrenchCopper :public AbstractChopper
{
public:
	using AbstractChopper::AbstractChopper;//�̳����еĹ��캯��
	void translateToPanda()
	{
		string msg = m_foreigner->confession();
		//�������ԣ������ݴ��ݸ���è
		recvMessage("������˵��" + msg);
	}
	void translateToHuman()
	{
		string msg = sendMessage();
		//����è����ת��ΪӢ����ݸ������
		m_foreigner->setResult("������" + msg);
	}
};

#endif


int main6()
{
	Foreigner* foreigner = new American;
	AbstractChopper* adapter = new EnglishCopper(foreigner);
	adapter->translateToPanda();
	adapter->translateToHuman();
	delete foreigner;
	delete adapter;
	cout << " ======================= " << endl;
	foreigner = new French;
	adapter = new FrenchCopper(foreigner);
	adapter->translateToPanda();
	adapter->translateToHuman();
	delete foreigner;
	delete adapter;

	return 0;
}