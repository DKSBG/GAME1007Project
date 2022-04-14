#include "game.h"
#include "dataParser.h"
#include "audioPlayer.h"
#include "gun.h"

void Gun::Update() 
{
	m_cdTimer -= MainGame::deltaGameTime;
}

void Gun::Fire() 
{
 	if (m_cdTimer > 0)
		return;

	int base = m_piece / 2;
	for (int index = 0; index < m_piece; index++)
	{
		ItemAttribute attr = m_attr;
		GameObject* bulletObject = PrefabParser::GetInstance()->Parser(m_projectile);
		Transform* pBulletTransform = &bulletObject->transform;
		pBulletTransform->Clone(*this->transform);

		if (attr.vector.x > 0)
			attr.vector.x += base;
		else
			attr.vector.x += -base;
		attr.vector.y += index - base;

		ReactableItem* bulletScript = bulletObject->GetComponent<ReactableItem>();
		bulletScript->itemAttribute = attr;
		bulletScript->reactAttrbute = m_reactAttr;
	}
	AudioPlayer::GetInstance()->PlaySound(m_fireSound, 0);
	m_cdTimer = m_fireCD;
}

void Gun::GunTypeSet(std::string projectile, std::string sound) 
{
	m_projectile = projectile;
	m_fireSound = sound;
}

void Gun::GunAttributeSet(ReactAttribute reactAttr, ItemAttribute bulletAttribute) 
{
	m_attr = bulletAttribute;
	m_reactAttr = reactAttr;
}

void Gun::GetReactAttribute(ReactAttribute* reactAttr) 
{
	*reactAttr = m_reactAttr;
}

void Gun::GetItemAttribute(ItemAttribute* bulletAttribute)
{
	*bulletAttribute = m_attr;
}

void Gun::SetCDTime(int time) 
{
	m_fireCD = time;
}

void Gun::SetVector(const Vector2 vector) 
{
	m_attr.vector.x = vector.x;
	m_attr.vector.y = vector.y;
}

void Gun::SetSpeed(int speed) 
{
	m_attr.speed = speed;
}

void Gun::SetPiece(int piece)
{
	m_piece = piece;
}

int Gun::GetCDTime() 
{
	return m_fireCD;
}
