#include <iostream>
#include <vector>
using namespace std;
#pragma once
struct Action;
struct Object;
struct Link;
struct Event;
vector<Object *> objs;
Object * first;
Object * start;
Object * input;
Object * output;
struct Link
{
	int weight;
	Event * event;
	void pulse();
};
struct Event
{
	int ceil;
	int height;
	vector<Action *> active_actions;
	vector<Link *> links;
	void operator()();
};
struct Object
{
	int value;
	Object * size;
	vector<Object *> subs;
	vector<Event *> value_increased;
	vector<Event *> value_decreased;
	vector<Event *> value_changed;
	Object() : value(0), size(NULL) {}; //create a special object
	Object(Object * base, int value); //create an object with it's value and base
	int operator=(int value); //assigned with a new value and triggle events
};
struct Action
{
	int op;
	vector<Object *> objs; //variables
	void operator()();
};