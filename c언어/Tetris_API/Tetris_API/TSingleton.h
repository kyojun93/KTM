#pragma once

template <typename T>
class TSingleton
{
	friend T;
private:
	static T * m_pInstance;

private:
	TSingleton()
	{

	}

public:
	~TSingleton()
	{

	}

public:

	static T * GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new T;

		return m_pInstance;
	}
};

template <typename T>
T * TSingleton<T>::m_pInstance = NULL;
