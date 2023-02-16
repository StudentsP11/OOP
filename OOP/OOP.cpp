#include <iostream>
#define INTERFACE_BASE() 

using std::string;

class Student
{
public:
	Student(string &&name, string &&group)
		: name_(name), group_(group)
	{}

	void change_group(string &&group)
	{
		group_ = group;
	}

	const string& name() const
	{
		return name_;
	}
protected:
	string name_;
	string group_;
};

class Aspirant : Student
{
public:
	Aspirant(string&& name, float work_progress)
	: Student(std::move(name), "aspirant"),
		work_progress_(work_progress)
	{}

private:
	float work_progress_;
};

string test_simple;

class IProjectile
{
public:
	virtual void print() = 0;

	virtual ~IProjectile() = default;
};

class Bullet : public IProjectile
{
	void print() final
	{
		std::cout << '\'';
	}
};

class Missile : public IProjectile
{
	void print() final
	{
		std::cout << "=>";
	}
};

class Laser : public IProjectile
{
	void print() final
	{
		std::cout << "---";
	}
};

class IItem
{
public:
	virtual void take() = 0;
	virtual void drop() = 0;

	virtual ~IItem() = default;
};

class Weapon : IItem
{
	IProjectile* projectile;

	Weapon(IProjectile* projectile)
	{
		this->projectile = projectile;
	}

	virtual void attack() = 0;
};

int main()
{
	Student("1", "2");

	return 0;
}