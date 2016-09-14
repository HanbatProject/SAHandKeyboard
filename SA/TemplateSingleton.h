#pragma once

template < typename T >
class TemplateSingleton
{
protected:
	TemplateSingleton()
	{

	}
	virtual ~TemplateSingleton()
	{

	}

public:
	static T * getInstance()
	{
		if (m_pInstance == NULL)
			m_pInstance = new T;
		return m_pInstance;
	};

	static void destroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	};

private:
	static T * m_pInstance;
};

template <typename T> T * TemplateSingleton<T>::m_pInstance = 0;