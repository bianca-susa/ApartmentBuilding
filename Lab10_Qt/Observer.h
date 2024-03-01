#pragma once
class Observer
{
public:
	virtual void update() = 0;
};

#include <vector>
#include <algorithm>

class Observable
{
private:
	std::vector<Observer*> observers;

public:
	void add_observer(Observer* obs)
	{
		observers.push_back(obs);
	}

	void remove_observer(Observer* obs)
	{
		observers.erase(std::remove(observers.begin(),observers.end(),obs),observers.end());
	}

protected:
	void notify()
	{
		for (auto obs : observers)
		{
			obs->update();
		}
	}
};