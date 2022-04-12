#pragma once
#include "gameObject.h"
#include "reactableItem.h"

class Gun : GOComponent 
{
public:
	void Update();
	void Fire();
	void GunTypeSet(std::string projectile, std::string sound);
	void GunAttributeSet(const ReactAttribute reactAttr, const ItemAttribute bulletAttribute);
	void GetReactAttribute(ReactAttribute* reactAttr);
	void GetItemAttribute(ItemAttribute* itemattr);
	void SetCDTime(int time);
	int GetCDTime();
private:
	std::string m_projectile;
	std::string m_fireSound;
	ReactAttribute m_reactAttr;
	ItemAttribute m_attr;
	int m_fireCD;
	int m_cdTimer;
};