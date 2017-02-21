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

		static int m_Id;

	public:
		Component(const std::string& type, Entity* parent);

		Component(const Component& other) = delete;

		Component& operator=(const Component& other) = delete;

		virtual ~Component();

		const std::string& GetType() const noexcept;

		Entity* GetParent() const noexcept;

		static int GetId() noexcept;

		virtual void Setup() noexcept = 0;

		virtual void Update(float dt, long time = 0) noexcept = 0;

		virtual void Teardown() noexcept = 0;

		void OnMessage(const MessageContainer& msg) override;
	};
}

#endif //BLADE_COMPONENT_H_
