#include<iostream>
using namespace std;

class AbstractSmile
{
public:
    virtual void transform() = 0;
    virtual void ability() = 0;
    virtual ~AbstractSmile() {}
};

// �����ħ��ʵ�� ������̬
class SheepSmile : public AbstractSmile
{
public:
    void transform()
    {
        cout << "������� -- ɽ������̬..." << endl;
    }
    void ability()
    {
        cout << "���ֱ۱������ǵ���ʽ -- �����" << endl;
    }
};

// �����ħ��ʵ�� ʨ����̬
class LionSmile : public AbstractSmile
{
public:
    void transform()
    {
        cout << "������� -- ʨ������̬..." << endl;
    }
    void ability()
    {
        cout << "��ݡ� ������֮��..." << endl;
    }
};

// �����ħ��ʵ�� ������̬
class BatSmile : public AbstractSmile
{
public:
    void transform()
    {
        cout << "������� -- ��������̬..." << endl;
    }
    void ability()
    {
        cout << "��������֮�򽣹���..." << endl;
    }
};

//���幤����--����

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
        cout << "�ͷ� SheepFactory ����ص��ڴ���Դ" << endl;
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
        cout << "�ͷ� LionFactory ����ص��ڴ���Դ" << endl;
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
        cout << "�ͷ� BatFactory ����ص��ڴ���Դ" << endl;
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