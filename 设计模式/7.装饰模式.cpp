#include<iostream>
using namespace std;

//战士基类
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

//黑胡子
class Teach : public Soldier
{
public:
	using Soldier::Soldier;
	void fight() override
	{
		cout << m_Name << "体术战斗" << endl;
	}
};

//恶魔果实基类
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

//暗暗果实
class DarkFruit : public DevilFruit
{
public:
	void fight() override
	{
		m_soldier->fight();
		//使用恶魔果实能力战斗
		cout << m_soldier->getName()
			<< "吃了暗暗果实，可以拥有黑洞一样的吸引力" << endl;
		warning();
	}
private:
	void warning()
	{
		cout << m_soldier->getName()
			<< "注意：吃了暗暗果实，身体元素化之后不会躲避攻击，会吸收上海" << endl;
	}
};
//震震果实
class QuakeFruit : public DevilFruit
{
public:
	void fight() override
	{
		m_soldier->fight();
		//使用恶魔果实能力战斗
		cout << m_soldier->getName()
			<< "吃了震震果实，可以在任意空间引发震动！" << endl;
	}

};

//大丙果实
class PieFruit : public DevilFruit
{
public:
	void fight() override
	{
		m_soldier->fight();
		//使用恶魔果实能力战斗
		cout << m_soldier->getName()
			<< "吃了大丙果实，获得大丙铠甲！" << endl;
		ability();
	}
	void ability()
	{
		cout << "最强复制，可以将身边事物变成大饼，帮助队友回血" << endl;
	}

};


int main7()
{
	Soldier* soldier = new Teach("黑胡子");
	DevilFruit* dark = new DarkFruit;
	DevilFruit* quake = new QuakeFruit;
	DevilFruit* pie = new PieFruit;
	//通过暗暗果实去装饰黑胡子
	dark->enchantment(soldier);
	//通过震震果实去装饰黑胡子
	quake->enchantment(dark);
	//通过大丙果实去装饰黑胡子
	pie->enchantment(quake);
	pie->fight();



	delete soldier;
	delete dark;
	delete quake;
	delete pie;

	return 0;
}