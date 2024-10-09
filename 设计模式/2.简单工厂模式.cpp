#include<iostream>
using namespace std;

class AbstractSmile
{
public:
	virtual void transform() = 0;
	virtual void ability() = 0;
	virtual ~AbstractSmile(){}
};

// 人造恶魔果实· 绵羊形态
class SheepSmile : public AbstractSmile
{
public:
    void transform()
    {
        cout << "变成人兽 -- 山羊人形态..." << endl;
    }
    void ability()
    {
        cout << "将手臂变成绵羊角的招式 -- 巨羊角" << endl;
    }
};

// 人造恶魔果实· 狮子形态
class LionSmile : public AbstractSmile
{
public:
    void transform()
    {
        cout << "变成人兽 -- 狮子人形态..." << endl;
    }
    void ability()
    {
        cout << "火遁· 豪火球之术..." << endl;
    }
};

// 人造恶魔果实· 蝙蝠形态
class BatSmile : public AbstractSmile
{
public:
    void transform()
    {
        cout << "变成人兽 -- 蝙蝠人形态..." << endl;
    }
    void ability()
    {
        cout << "声纳引箭之万剑归宗..." << endl;
    }
};

//定义工厂类，简单工厂模式工厂类有且只有一个
//违反了封闭原则
enum class Type:char{Sheep,Lion,Bat};
class SmileFactory
{
public:
    AbstractSmile* createSmile(Type type)
    {
        AbstractSmile* ptr = nullptr;
        switch (type)
        {
        case Type::Sheep:
            ptr = new SheepSmile;
            break;
        case Type::Lion:
            ptr = new LionSmile;
            break;
        case Type::Bat:
            ptr = new BatSmile;
            break;
        default:
            break;
        }
        return ptr;
    }
};

int main2()
{

    SmileFactory* factory = new SmileFactory;
    AbstractSmile* obj = factory->createSmile(Type::Lion);
    obj->transform();
    obj->ability();

    delete obj;
    delete factory;

    return 0;
}