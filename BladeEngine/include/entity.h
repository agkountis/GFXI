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

	/*
	\brief Entity class of the engine
	\details An entity stores a collection of components, has a unique name and
	its own transform matrix.
	*/
	class Entity : public ObserverSubject, public Resource
	{
	private:
		/*
		\brief The vector of the components attached to the entity.
		*/
		std::vector<Component*> m_Components;

		/*
		\brief Name of the entity
		*/
		std::string m_Name;

		/*
		\brief Alive flag of the entity
		\details if is false the entity won't be updated.
		*/
		bool m_Alive;

		/*
		\brief Entity position in world coordinates
		*/
		Vec3f m_Position;

		/*
		\brief Entity orientation.
		*/
		Quatf m_Orientation;

		/*
		\brief Entity scale
		\details Not uniform scaling is permitted.
		*/
		Vec3f m_Scale{ 1.0f, 1.0f, 1.0f };

		/*
		\brief Transform matrix of the entity
		*/
		Mat4f m_Xform;

		/*
		\brief Pointer to the parent of the entity
		\details This can be used to create a parent child relationship between
		entities. This means that if, for example a child entity, will take in consideration
		the parent transform matrix.
		*/
		Entity* m_pParent;

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

		Entity* GetEntityFromHierarchy(const std::string& name) noexcept;

		void AddChild(Entity* entity) noexcept;

		size_t GetChildrenCount() const noexcept;

		const Mat4f& GetXform() const noexcept;

		void SetXform(const Mat4f& xform) noexcept;

		/*
		\brief Calculate the transformation matrix of the entity
		\details If the entity has a parent, the transformation matrix
		is multiplied by the transformation matrix of his parent.
		*/
		void CalculateXform() noexcept;

		/*
		\brief Return a component that is attached to the entity.
		*/
		Component* GetComponent(const std::string& type) const noexcept;

		/*
		\brief Return a list of components of the same type attached to the entity
		*/
		std::vector<Component*> GetComponents(const std::string& type) const noexcept;

		/*
		*\brief Attach a new component to the entity.
		*/
		void AddComponent(Component* component) noexcept;

		bool IsAlive() const noexcept;

		void SetAlive(bool state) noexcept;

		/*
		\brief Update the entity transformation matrix.
		*/
		virtual void Update(float dt, long time = 0) noexcept;

		bool Load(const std::wstring& fileName) noexcept override;
	};
}

#endif //BLADE_ENTITY_H_
