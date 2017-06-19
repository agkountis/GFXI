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

	/**
	 * \brief Entity class of the engine
	 * \details An entity stores a collection of components, has a unique name and
	 * its own transform matrix.
	 */
	class Entity : public ObserverSubject, public Resource
	{
	private:
		/**
		 * \brief The vector of the components attached to the entity.
		 */
		std::vector<Component*> m_Components;

		/**
		 * \brief Name of the entity
		 */
		std::string m_Name;

		/**
		 * \brief Alive flag of the entity
		 * \details if is false the entity won't be updated.
		 */
		bool m_Alive;

		/**
		 *\brief Entity position in world coordinates
		 */
		Vec3f m_Position;

		/**
		 * \brief Entity orientation.
		 */
		Quatf m_Orientation;

		/**
		 * \brief Entity scale
		 * \details Not uniform scaling is permitted.
		 */
		Vec3f m_Scale{ 1.0f, 1.0f, 1.0f };

		/**
		 * \brief Transform matrix of the entity
		 */
		Mat4f m_Xform;

		/**
		 * \brief Pointer to the parent of the entity
		 * \details This can be used to create a parent child relationship between
		 * entities. This means that if, for example a child entity, will take in consideration
		 * the parent transform matrix.
		 */
		Entity* m_pParent;

		std::vector<Entity*> m_Children;


	public:
		explicit Entity(const std::string& name);

		~Entity();

		Entity(const Entity& other);

		Entity& operator=(const Entity& other);

		/**
		 * \brief Returns the Entity's name.
		 * \return The Entity's name.
		 */
		const std::string& GetName() const noexcept;

		/**
		 * \brief Returns the position of the Entity in local space.
		 * \return The position of the Entity in local space.
		 */
		const Vec3f& GetLocalPosition() const noexcept;

		/**
		 * \brief Returns the position of the Entity in world space.
		 * \return The position of the Entity in world space.
		 */
		Vec3f GetWorldPosition() noexcept;

		/**
		 * \brief Sets the position of the entity in the world.
		 * \param position The position to be set to the entity in world space coordinates.
		 */
		void SetPosition(const Vec3f& position) noexcept;

		/**
		 * \brief Returns the orientation of the Entiyty in quaternion form.
		 * \return The orientation of the Entity in quaternion form.
		 */
		const Quatf& GetOrientation() const noexcept;

		/**
		 * \brief Sets the orientation of the Entity.
		 * \param orientation The orientation of the entity in quaternion form.
		 */
		void SetOrientation(const Quatf& orientation) noexcept;

		/**
		 * \brief Sets the orientation of the Entity using axes and angle.
		 * \param axis The axes to rotate around.
		 * \param angle The angle of rotation in radians. 
		 */
		void SetOrientation(const Vec3f& axis, float angle) noexcept;

		/**
		 * \brief Returns the scale vector of the Entity.
		 * \return The scale vector of the Entity.
		 */
		const Vec3f& GetScale() const noexcept;

		/**
		 * \brief Sets the scaling vector of the Entity.
		 * \param scale The scaling vector to be set to the Entity.
		 */
		void SetScale(const Vec3f& scale) noexcept;

		/**
		 * \brief Returns the parent of the Entity.
		 * \return The parent of the Entity.
		 */
		Entity* GetParent() const noexcept;

		/**
		 * \brief Sets the entity specified as a parent.
		 * \param entity The entity to be set as the parent.
		 */
		void SetParent(Entity* entity) noexcept;

		const std::vector<Entity*>& GetChildren() const noexcept;

		/**
		 * \brief Returns the child Entity at the specified index in the vector.
		 * \param index An index for the children vector.
		 * \return The child of the specified index in the vector.
		 */
		Entity* GetChild(int index) const noexcept;

		/**
		 * \brief Returns the Entity with the specified name if it exists in the hierarchy.
		 * \param name The name of the Entity.
		 * \return The Entity if found in the hierarchy.
		 */
		Entity* GetEntityFromHierarchy(const std::string& name) noexcept;

		/**
		 * \brief Adds the specified Entity as child.
		 * \param entity The Entity to be added as a child.
		 */
		void AddChild(Entity* entity) noexcept;

		/**
		 * \brief Returns the number of children that the Entity has.
		 * \return The number of children.
		 */
		size_t GetChildrenCount() const noexcept;

		/**
		 * \brief Returns the Entity's transformation matrix.
		 * \return The Entity's transformation matrix.
		 */
		const Mat4f& GetXform() const noexcept;

		/**
		 * \brief Sets the specified transofrmation matrix to the Entity.
		 * \param xform The transformation matrix to be set to the Entity.
		 */
		void SetXform(const Mat4f& xform) noexcept;

		/**
		 * \brief Calculate the transformation matrix of the entity
		 * \details If the entity has a parent, the transformation matrix
		 * is multiplied by the transformation matrix of his parent.
		 */
		void CalculateXform() noexcept;

		/**
		 * \brief Return a component that is attached to the entity.
		 */
		Component* GetComponent(const std::string& type) const noexcept;

		/**
		 * \brief Remove one component from the owned vector.
		 * \details Do not delete the component, this method is designed to pass ownership the 
		 * component to another entity.
		 */
		void  Entity::RemoveComponent(const int id) noexcept;

		/**
		 * \brief Return a list of components of the same type attached to the entity
		 */
		std::vector<Component*> GetComponents(const std::string& type) const noexcept;

		/**
		 *\brief Attach a new component to the entity.
		 */
		void AddComponent(Component* component) noexcept;

		/**
		 * \brief Checks if the Entity is alive.
		 * \return TRUE if the Entity is alive, FALSE otherwise.
		 */
		bool IsAlive() const noexcept;

		/**
		 * \brief Sets the alive state of the Entity.
		 * \param state The alive state of the Entity.
		 */
		void SetAlive(bool state) noexcept;

		/**
		 * \brief Update the entity transformation matrix.
		 */
		virtual void Update(float dt, long time = 0) noexcept;

		/**
		 * \brief Loads an Entity or an Entity hierarchy from a file.
		 * \param fileName The file name of the file used to load an Entity or Entity hierarchy.
		 * \return TRUE if successful, FALSE otherwise.
		 */
		bool Load(const std::wstring& fileName) noexcept override;
	};
}

#endif //BLADE_ENTITY_H_
