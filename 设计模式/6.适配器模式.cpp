#include<iostream>
using namespace std;


#if 0
//适配器类和熊猫类是关联关系
//外国人
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
		return "我有罪";
	}
};
class French : public Foreigner
{
public:
	string confession() override
	{
		return "我有罪";
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
		return string("不可原谅");
	}
};

//适配器类
//适配器类基类
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
	using AbstractChopper::AbstractChopper;//继承所有的构造函数
	void translateToPanda()
	{
		string msg = m_foreigner->confession();
		//解析语言，将数据传递给熊猫
		m_panda.recvMessage("美国人说：" + msg);
	}
	void translateToHuman()
	{
		string msg = m_panda.sendMessage();
		//将熊猫语言转换为英语，传递给外国人
		m_foreigner->setResult("美国人" + msg);
	}
};

class FrenchCopper :public AbstractChopper
{
public:
	using AbstractChopper::AbstractChopper;//继承所有的构造函数
	void translateToPanda()
	{
		string msg = m_foreigner->confession();
		//解析语言，将数据传递给熊猫
		m_panda.recvMessage("法国人说：" + msg);
	}
	void translateToHuman()
	{
		string msg = m_panda.sendMessage();
		//将熊猫语言转换为英语，传递给外国人
		m_foreigner->setResult("法国人" + msg);
	}
};

#endif



#if 1
//适配器类和熊猫类是继承关系
//外国人
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
		return "我有罪";
	}
};
class French : public Foreigner
{
public:
	string confession() override
	{
		return "我有罪";
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
		return string("不可原谅");
	}
};

//适配器类
//适配器类基类
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
	using AbstractChopper::AbstractChopper;//继承所有的构造函数
	void translateToPanda()
	{
		string msg = m_foreigner->confession();
		//解析语言，将数据传递给熊猫
		recvMessage("美国人说：" + msg);
	}
	void translateToHuman()
	{
		string msg = sendMessage();
		//将熊猫语言转换为英语，传递给外国人
		m_foreigner->setResult("美国人" + msg);
	}
};

class FrenchCopper :public AbstractChopper
{
public:
	using AbstractChopper::AbstractChopper;//继承所有的构造函数
	void translateToPanda()
	{
		string msg = m_foreigner->confession();
		//解析语言，将数据传递给熊猫
		recvMessage("法国人说：" + msg);
	}
	void translateToHuman()
	{
		string msg = sendMessage();
		//将熊猫语言转换为英语，传递给外国人
		m_foreigner->setResult("法国人" + msg);
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