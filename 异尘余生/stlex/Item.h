#pragma once
enum type { POSION=0, WEAPON=1, BODY=2, NECK = 3, LEG=4,FEET=5,HEAD=6,HAND=7 ,MISC=8,QUEST=9};
class CItem
{
protected:
	string m_name;
	int m_id;
	type m_type;
	int m_price;
	string m_discription;

public:
	CItem();
	string getName();
	int getId() { return m_id; }
	int getPrice() { return m_price; }
	type getType() { return m_type; }
	string getScrip() { return m_discription; }

	virtual ~CItem();
};

