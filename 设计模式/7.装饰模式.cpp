#include<iostream>
using namespace std;

//սʿ����
class Soldier
{
public:
	Soldier(){}
	Soldier(string name):m_Name(name){}
	string getName()
	{
		return m_Name;
	}
	virtual void fight() = 0;
	virtual ~Soldier() {}

protected:
	string m_Name = string();
};

//�ں���
class Teach : public Soldier
{
public:
	using Soldier::Soldier;
	void fight() override
	{
		cout << m_Name << "����ս��" << endl;
	}
};

//��ħ��ʵ����
class DevilFruit : public Soldier
{
public:
	void enchantment(Soldier* soldier)
	{
		m_soldier = soldier;
		m_Name = soldier->getName();
	}
protected:
	Soldier* m_soldier = nullptr;
};

//������ʵ
class DarkFruit : public DevilFruit
{
public:
	void fight() override
	{
		m_soldier->fight();
		//ʹ�ö�ħ��ʵ����ս��
		cout << m_soldier->getName()
			<< "���˰�����ʵ������ӵ�кڶ�һ����������" << endl;
		warning();
	}
private:
	void warning()
	{
		cout << m_soldier->getName()
			<< "ע�⣺���˰�����ʵ������Ԫ�ػ�֮�󲻻��ܹ������������Ϻ�" << endl;
	}
};
//�����ʵ
class QuakeFruit : public DevilFruit
{
public:
	void fight() override
	{
		m_soldier->fight();
		//ʹ�ö�ħ��ʵ����ս��
		cout << m_soldier->getName()
			<< "���������ʵ������������ռ������𶯣�" << endl;
	}

};

//�����ʵ
class PieFruit : public DevilFruit
{
public:
	void fight() override
	{
		m_soldier->fight();
		//ʹ�ö�ħ��ʵ����ս��
		cout << m_soldier->getName()
			<< "���˴����ʵ����ô�����ף�" << endl;
		ability();
	}
	void ability()
	{
		cout << "��ǿ���ƣ����Խ���������ɴ�����������ѻ�Ѫ" << endl;
	}

};


int main7()
{
	Soldier* soldier = new Teach("�ں���");
	DevilFruit* dark = new DarkFruit;
	DevilFruit* quake = new QuakeFruit;
	DevilFruit* pie = new PieFruit;
	//ͨ��������ʵȥװ�κں���
	dark->enchantment(soldier);
	//ͨ�������ʵȥװ�κں���
	quake->enchantment(dark);
	//ͨ�������ʵȥװ�κں���
	pie->enchantment(quake);
	pie->fight();



	delete soldier;
	delete dark;
	delete quake;
	delete pie;

	return 0;
}