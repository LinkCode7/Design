#include "EntityModule.h"
#include "Reactor.h"

PxShapeFormat PxShape::getFormat()
{
	m_format.setOwner(this);
	return m_format;
}

void PxShape::setFormat(const PxShapeFormat& format)
{
	assertWriteEnabled(1);

	m_format.setOwner(this);
	m_format = format;
}

void PxShape::setColor(int color)
{
	assertWriteEnabled(2);
	m_color = color;
}

PxFill PxShapeFormat::getFill()
{
	m_fill.setOwner(m_owner);
	return m_fill;
}

void PxShapeFormat::setIntValue(int value)
{
	assertWriteEnabled2(m_owner, 3);
	m_int = value;
}

int PxFill::getValue()
{
	return m_value;
}

void PxFill::setValue(int value)
{
	assertWriteEnabled2(m_owner, 0);
	m_value = value;
}
