#include<iostream>
using namespace std;

class Person
{
public:
	Person(const Person& p) = delete;
	Person& operator=(const Person& p) = delete;
	static Person* getPerson()
	{
		return p_Person;
	}
private:
	Person() = default;
	static Person* p_Person;
};
Person* Person::p_Person = new Person;

class Person2
{
public:
	Person2(const Person2& p) = delete;
	Person2& operator=(const Person2& p) = delete;
	static Person2* getPerson()
	{
		static Person2 p_Person2;
		return &p_Person2;
	}
private:
	Person2() = default;
};


int main11()
{
	Person* p= Person::getPerson();
	Person2* p2 = Person2::getPerson();


	return 0;
}