#ifndef BLADE_ENTITY_H_
#define BLADE_ENTITY_H_
#include <vector>
#include "component.h"
#include "types.h"
#include "math_utils.h"
#include "observer_subject.h"
#include "resource.h"
#include <functional>

namespace Blade
{
	class Entity : public ObserverSubject, public Resource
	{
	private:
		std::vector<Component*> m_Components;

		std::string m_Name;

		bool m_Alive;

		Vec3f m_Position;
		Quatf m_Orientation;
		Vec3f m_Scale{ 1.0f, 1.0f, 1.0f };

		Mat4f m_Xform;

		Entity* p_Parent;

		std::vector<Entity*> m_Children;

	public:
		explicit Entity(const std::string& name);

		~Entity();

		Entity(const Entity& other);

		Entity& operator=(const Entity& other);

		const std::string& GetName() const noexcept;

		const Vec3f& GetPosition() const noexcept;

		void SetPosition(const Vec3f& position) noexcept;

		const Quatf& GetOrientation() const noexcept;

		void SetOrientation(const Quatf& orientation) noexcept;

		void SetOrientation(const Vec3f& axis, float angle) noexcept;

		const Vec3f& GetScale() const noexcept;

		void SetScale(const Vec3f& scale) noexcept;

		Entity* GetParent() const noexcept;

		void SetParent(Entity* entity) noexcept;

		const std::vector<Entity*>& GetChildren() const noexcept;

		Entity* GetChild(int index) const noexcept;

		size_t GetChildrenCount() const noexcept;

		const Mat4f& GetXform() const noexcept;

		void SetXform(const Mat4f& xform) noexcept;

		void CalculateXform() noexcept;

		Component* GetComponent(const std::string& type) const noexcept;

		void AddComponent(Component* component) noexcept;

		bool IsAlive() const noexcept;

		void SetAlive(bool state) noexcept;

		virtual void Update(float dt, long time = 0) noexcept;

		bool Load(const std::wstring& fileName) noexcept override;
	};
}

#endif //BLADE_ENTITY_H_
