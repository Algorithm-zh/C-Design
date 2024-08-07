#include<iostream>
using namespace std;

class AbstractSmile
{
public:
	virtual void transform() = 0;
	virtual void ability() = 0;
	virtual ~AbstractSmile(){}
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

//���幤���࣬�򵥹���ģʽ����������ֻ��һ��
//Υ���˷��ԭ��
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