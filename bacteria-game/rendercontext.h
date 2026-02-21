#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#include <vector>
#include <mutex>

namespace sf { class Drawable; };

class PrimitiveArray
{
public:
	~PrimitiveArray();
	void addPrimitive(sf::Drawable*);
	void removePrimitive(sf::Drawable*);
	std::vector<sf::Drawable*> primitives() const;

private:
	std::vector<sf::Drawable*>::const_iterator find(sf::Drawable*);
	bool contains(sf::Drawable* primitive);
	std::vector<sf::Drawable*> m_primitive_list;
};


class RenderContext
{
public:
	struct Access
	{
		Access(std::mutex& mutex, PrimitiveArray* context);
		PrimitiveArray* operator->();

	private:
		std::unique_lock<std::mutex> m_lock;
		PrimitiveArray* m_context;
	};

	Access acquire();

private:
	std::mutex m_mutex;
	PrimitiveArray m_context;
};


#endif // !RENDERCONTEXT_H
