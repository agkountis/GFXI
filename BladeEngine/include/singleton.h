#ifndef BLADE_SINGLETON_H_
#define BLADE_SINGLETON_H_

namespace Blade
{
	template<typename T>
	class Singleton
	{
	protected:
		Singleton() = default;

	public:
		virtual ~Singleton() = default;

		Singleton(const Singleton& other) = delete;

		Singleton& operator=(const Singleton& other) = delete;

		Singleton(Singleton&& other) = delete;

		Singleton&& operator=(Singleton&& other) = delete;

		static T& GetInstance() noexcept
		{
			static T instance;

			return instance;
		}
	};
}

#endif //BLADE_SINGLETON_H_
