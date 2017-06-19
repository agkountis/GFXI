#ifndef BLADE_SCENE_H_
#define BLADE_SCENE_H_
#include <vector>
#include "types.h"

namespace Blade
{
	class Entity;

	/**
	 * \brief Represents a scene of the game
	 * \details For example main menu scene, game play scene etc.
	 */
	class Scene
	{
	private:

		/**
		\brief The collection of the entities present in this scene.
		*/
		std::vector<Entity*> m_pEntities;

		/**
		\brief The collection of the entities that need be removed the next frame.
		*/
		std::vector<Entity*> m_pNeedToBeRemovedEntities;

		/**
		\brief The collection of the entities that need be deleted the next frame.
		*/
		std::vector<Entity*> m_pNeedToBeDeletedEntities;

	public:
		Scene() = default;

		virtual ~Scene();

		Scene(const Scene& other) = delete;

		Scene& operator=(const Scene& other) = delete;

		/**
		\brief Initialize the scene
		*/
		virtual bool Initialize() = 0;

		/**
		\brief Adds a new entity to the scene
		\param object The entity pointer 
		*/
		void AddEntity(Entity* object) noexcept;

		/**
		\brief Remove entity
		\param name The name of the entity 
		\details Do not delete the entity, this is used to change ownership
		*/
		void RemoveEntity(const std::string&  name) noexcept;

		/**
		\brief Removes and deletes that entities that need to be removed or deleted
		*/
		void RemoveEntities() noexcept;


		/**
		* \brief Getters of the collections of entities that are currently in the scene.
		  \return Return the collection of the entities owned by the scene.
		*/
		const std::vector<Entity*>& GetEntities() const noexcept;
		

		/** 
		\brief Return an entity owned by the scene by name.
		\param name The name of the entity
		\return The pointer of the entity, nullptr if the entity is not inside the scene.
		*/
		Entity* GetEntityByName(const std::string& name) noexcept;

		/**
		\brief Defines how the scene should response when a key is pressed
		\param key the key pressed
		*/
		virtual void OnKeyDown(unsigned char key, int x, int y) noexcept = 0;

		/**
		\brief Defines how a scene should response when a key is released
		\param key the key pressed
		*/
		virtual void OnKeyUp(unsigned char key, int x, int y) noexcept = 0;

		/**
		\brief Defines how a scene should response when the mouse is moved
		\param x the x value of the cursor position
		\param y the y value of the cursor position
		*/
		virtual void OnMouseMotion(int x, int y) noexcept = 0;

		/**
		\brief Defines how the scene should response when a button is clicked
		*/
		virtual void OnMouseClick(int button, bool state, int x, int y) noexcept = 0;

		/**
		\brief Update the current scene.
		*/
		virtual void Update(float deltaTime, long time = 0) noexcept;

		/**
		\brief Draws the current scene on screen.
		*/
		virtual void Draw() const noexcept = 0;

		/**
		\brief Broadcast a messaged from the scene to all the entities stored.
		\param msg The message
		*/
		virtual void OnMessage(const MessageContainer<std::string>& msg) const noexcept;
	};
}

#endif //BLADE_SCENE_H_
