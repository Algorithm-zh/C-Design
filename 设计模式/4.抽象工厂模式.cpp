#include<iostream>
using namespace std;
// ����
class ShipBody
{
public:
    virtual string getShipBody() = 0;
    virtual ~ShipBody() {}
};

class WoodBody : public ShipBody
{
public:
    string getShipBody() override
    {
        return string("��<ľ��>�����ִ�����...");
    }
};

class IronBody : public ShipBody
{
public:
    string getShipBody() override
    {
        return string("��<����>�����ִ�����...");
    }
};

class MetalBody : public ShipBody
{
public:
    string getShipBody() override
    {
        return string("��<�Ͻ�>�����ִ�����...");
    }
};

// ����
class Engine
{
public:
    virtual string getEngine() = 0;
    virtual ~Engine() {}
};

class Human : public Engine
{
public:
    string getEngine() override
    {
        return string("ʹ��<��������>...");
    }
};

class Diesel : public Engine
{
public:
    string getEngine() override
    {
        return string("ʹ��<��ȼ������>...");
    }
};

class Nuclear : public Engine
{
public:
    string getEngine() override
    {
        return string("ʹ��<��������>...");
    }
};

// ����
class Weapon
{
public:
    virtual string getWeapon() = 0;
    virtual ~Weapon() {}
};

class Gun : public Weapon
{
public:
    string getWeapon() override
    {
        return string("�䱸��������<ǹ>");
    }
};

class Cannon : public Weapon
{
public:
    string getWeapon() override
    {
        return string("�䱸��������<�Զ�������>");
    }
};

class Laser : public Weapon
{
public:
    string getWeapon() override
    {
        return string("�䱸��������<����>");
    }
};

// �ִ���
class Ship
{
public:
    Ship(ShipBody* body, Weapon* weapon, Engine* engine) :
        m_body(body), m_weapon(weapon), m_engine(engine)
    {
    }
    string getProperty()
    {
        string info = m_body->getShipBody() + m_weapon->getWeapon() + m_engine->getEngine();
        return info;
    }
    ~Ship()//��Ϲ�ϵ������������������ȫ������
    {
        delete m_body;
        delete m_engine;
        delete m_weapon;
    }
private:
    ShipBody* m_body = nullptr;
    Weapon* m_weapon = nullptr;
    Engine* m_engine = nullptr;
};

// ������
class AbstractFactory
{
public:
    virtual Ship* createShip() = 0;
    virtual ~AbstractFactory() {}
};

class BasicFactory : public AbstractFactory
{
public:
    Ship* createShip() override
    {
        Ship* ship = new Ship(new WoodBody, new Gun, new Human);
        cout << "<������>ս���������, ������ˮ��..." << endl;
        return ship;
    }
};

class StandardFactory : public AbstractFactory
{
public:
    Ship* createShip() override
    {
        Ship* ship = new Ship(new IronBody, new Cannon, new Diesel);
        cout << "<��׼��>ս���������, ������ˮ��..." << endl;
        return ship;
    }
};

class UltimateFactory : public AbstractFactory
{
public:
    Ship* createShip() override
    {
        Ship* ship = new Ship(new MetalBody, new Laser, new Nuclear);
        cout << "<�콢��>ս���������, ������ˮ��..." << endl;
        return ship;
    }
};




int main4()
{
    AbstractFactory* factory = new UltimateFactory;
    Ship* ship = factory->createShip();
    cout << ship->getProperty() << endl;
    delete ship;
    delete factory;

	return 0;
}