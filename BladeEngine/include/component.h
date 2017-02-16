#ifndef BLADE_COMPONENT_H_
#define BLADE_COMPONENT_H_
#include <string>
#include "observer.h"

namespace Blade
{
	class Entity;

	class Component : public Observer
	{
	private:
		const std::string m_Type;

		Entity* p_Parent{ nullptr };

	public:
		Component(const std::string& type, Entity* parent);

		Component(const Component& other) = default;
		Component& operator=(const Component& other) = default;
		Component& operator=(Component&& other) noexcept = default;

		virtual ~Component();

		const std::string& GetType() const noexcept
		{
			return m_Type;
		}

		Entity* GetParent() const noexcept
		{
			return p_Parent;
		}

		virtual void Setup() noexcept = 0;

		virtual void Update(float dt, long time = 0) noexcept = 0;

		virtual void Teardown() noexcept = 0;

		void OnMessage(const MessageContainer& msg) override;
	};
}

#endif //BLADE_COMPONENT_H_
