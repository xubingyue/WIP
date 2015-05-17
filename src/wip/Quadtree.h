#pragma once
#include "RBMath/Inc/AABB.h"
#include <vector>

class WIPSprite;

class Quadtree
{

private:
	typedef std::vector<WIPSprite*> _ObjectList;
	Quadtree* children[4];

public:
	static i32 MAX_OBJCT,MAX_LEVEL;
	static void reset_max_obj(i32 val);
	static void reset_max_level(i32 val);

	i32 level;
	RBAABB bound;

	Quadtree(i32 level,RBAABB bound);
	//clear all the tree
	void clear();
	//Splits the node into 4 subnodes
	void split();
	/*Determine which node the object belongs to. -1 means 
	object cannot completely fit within a child node and 
	is part of the parent node*/
	void get_index(RBAABB rect);
	/*
	Insert the object into the quadtree. If the node exceeds the capacity,
	it will split and add all objects to their corresponding nodes
	*/
	void insert(RBAABB rect);
	void retrieve(_ObjectList objs,RBAABB rect);
	_ObjectList object_list;




};