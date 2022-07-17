#ifndef ENTITY_MODULE_H
#define ENTITY_MODULE_H

class PxShape;

class PxObjectOwner
{
public:
	void setOwner(PxShape* owner) { m_owner = owner; }
	PxShape* getOwner() { return m_owner; }

protected:
	PxShape* m_owner;
};

// 图形填充
class PxFill : public PxObjectOwner
{
public:
	int getValue();
	void setValue(int value);

	int m_public; // fill.m_public = 0;

private:
	int m_value = 100;
};

// 图形格式化对象
class PxShapeFormat : public PxObjectOwner
{
public:

	PxFill getFill();
	void setIntValue(int value);
private:
	PxFill m_fill;
	int m_int;
};


// 图形
class PxShape
{
public:
	PxShapeFormat getFormat();
	void setFormat(const PxShapeFormat& format);

	void setColor(int color);

private:
	int m_color = 1001;
	PxShapeFormat m_format;
};

#endif // !ENTITY_MODULE_H