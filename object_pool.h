#pragma once

#include <vector>

template <class T>
class ObjectPool
{
public:

	std::vector<T*> m_pool;

	void Create(unsigned int num_objects)
	{
		Deallocate();

		for (unsigned int i = 0; i < num_objects; i++)
		{
			T * t = new T();
			m_pool.push_back(t);
		}
	}

	void Destroy()
	{
		for (auto it : m_pool)
			it->Destroy();
	}

	void Deallocate()
	{
#if LOG
		SDL_Log("ObjectPool::Deallocating ");
#endif
		for (auto it : m_pool)
			delete it;
	}

	~ObjectPool()
	{
#if LOG
		SDL_Log("ObjectPool::~ObjectPool");
#endif
		Deallocate();
	}

	T* FirstAvailable()
	{
		for (auto it : m_pool)
			if (!(*it).m_enabled)
				return it;

		// if it reaches this point, there is no available object in the pool
		return NULL;
	}

	// select a random, enabled element in the object pool
	T* SelectRandom()
	{
		int offset = (rand() / (float)RAND_MAX) * m_pool.size();

		for (auto i = 0; i < m_pool.size(); i++)
		{
			int index = (i + offset) % m_pool.size();

			if (m_pool[index]->m_enabled)
				return m_pool[index];
		}

		return NULL;
	}

private:
};