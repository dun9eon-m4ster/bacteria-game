#include "rendercontext.h"
#include "SFML/Graphics/Drawable.hpp"

#include <iostream>

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

PrimitiveArray::~PrimitiveArray()
{
	for (auto it = m_primitive_list.begin(); it != m_primitive_list.end(); ++it)
	{
		delete (*it);
	}
	m_primitive_list.clear();
}

void PrimitiveArray::addPrimitive(sf::Drawable* primitive)
{
	if (contains(primitive))
	{
		std::cout << __PRETTY_FUNCTION__ << " - primitive already present" << std::endl;
		return;
	}

	m_primitive_list.push_back(primitive);
}

void PrimitiveArray::removePrimitive(sf::Drawable* primitive)
{
	if (!contains(primitive))
	{
		std::cout << __PRETTY_FUNCTION__ << " - primitive does not present" << std::endl;
		return;
	}

	m_primitive_list.erase(find(primitive));
}
std::vector<sf::Drawable*> PrimitiveArray::primitives() const
{
	return m_primitive_list;
}

std::vector<sf::Drawable*>::const_iterator PrimitiveArray::find(sf::Drawable* primitive)
{
	return std::find(m_primitive_list.cbegin(), m_primitive_list.cend(), primitive);
}

bool PrimitiveArray::contains(sf::Drawable* primitive)
{
	return find(primitive) != m_primitive_list.cend();
}

inline RenderContext::Access::Access(std::mutex& mutex, PrimitiveArray* context)
	: m_lock(mutex),
	m_context(context)
{
}

PrimitiveArray* RenderContext::Access::operator->()
{
	return m_context;
}

RenderContext::Access RenderContext::acquire()
{
	return Access(m_mutex, &m_context);
}
