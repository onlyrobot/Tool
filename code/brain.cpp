#include "brain.h"
#include <string>
#include <fstream>
using namespace std;
void Link::pulse()
{
	event->height += weight;
	if (event->height >= event->ceil)
	{
		event->height = 0; //restore to zero
		(*event)();
	}
}
void Event::operator()()
{
	for (Action * action : active_actions)
	{
		(*action)();
	}
	for (Link * link : links)
	{
		link->pulse();
	}
}
Object::Object(Object * base, int value) : value(value), size(new Object())
{
	try
	{
		base->subs.push_back(this);
		++base->size;
	}
	catch (Object)
	{
		cout << "base cannot be size object" << endl;
	}
}
int Object::operator=(int value) //assigned with a new value and triggle events
{
	if (this->value < value)
	{
		for (Event * event : value_increased)
		{
			(*event)();
		}
	}
	else if (this->value > value)
	{
		for (Event * event : value_decreased)
		{
			(*event)();
		}
	}
	for (Event * event : value_changed)
	{
		(*event)();
	}
	return 0;
}
void Action::operator()()
{
	switch (op)
	{
	case 1: *objs[0] = objs[1]->value + objs[2]->value; break;
	case 2: *objs[0] = objs[1]->value - objs[2]->value; break;
	default: cout << "error operator" << endl; break;
	}
}


void parse_code(ifstream & code)
{
	char c;
	while (code)
	{
		
	}
}
int main()
{
	first = new Object();
	start = new Object(first, -1);
	input = new Object(first, -1);
	output = new Object(first, -1);
	ifstream code("E:/code.txt");
	parse_code(code);
	code.close();
}