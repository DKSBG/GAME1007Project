#include "gameObject.h"
#include "script.h"

void Ally::OnCollide(GameObject* go) 
{
	bool underAttack = true;
	Ally * item = go->GetComponent<Ally>();

	if (item != NULL && item->isDamageAlly != true)
		underAttack = false;

	if (underAttack)
		UnderAttack();
}

void Enemy::OnCollide(GameObject* go)
{
	bool underAttack = true;
	Enemy* item = go->GetComponent<Enemy>();
	if (item != NULL && item->isDamageAlly != true)
		underAttack = false;

	if (underAttack)
		UnderAttack();
}

void Third::OnCollide(GameObject* go)
{
	UnderAttack();
}
