#include<iostream>
using namespace std;

class AbstractSmile
{
public:
    virtual void transform() = 0;
    virtual void ability() = 0;
    virtual ~AbstractSmile() {}
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

//定义工厂类--父类

class AbstractFactory
{
public:
    virtual AbstractSmile* createSmile() = 0;
    virtual ~AbstractFactory() {}
};

class SheepFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile() override
    {
        return new SheepSmile;
    }
    ~SheepFactory()
    {
        cout << "释放 SheepFactory 类相关的内存资源" << endl;
    }
};

class LionFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile() override
    {
        return new LionSmile;
    }
    ~LionFactory()
    {
        cout << "释放 LionFactory 类相关的内存资源" << endl;
    }

};

class BatFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile() override
    {
        return new BatSmile;
    }
    ~BatFactory()
    {
        cout << "释放 BatFactory 类相关的内存资源" << endl;
    }
};



int main3()
{

    AbstractFactory* factory = new LionFactory;
    AbstractSmile* obj = factory->createSmile();
    obj->transform();
    obj->ability();
    delete obj;
    delete factory;

    return 0;
}