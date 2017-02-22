#ifndef BLADE_SCENE_H_
#define BLADE_SCENE_H_
#include <vector>
#include "types.h"

namespace Blade
{
	class Entity;

	class Scene
	{
	private:
		std::vector<Entity*> m_Entities;

	public:
		Scene() = default;

		virtual ~Scene();


		Scene(const Scene& other) = default;
		Scene& operator=(const Scene& other) = default;

		virtual void Initialize() = 0;

		void AddEntity(Entity* object) noexcept;

		const std::vector<Entity*>& GetEntities() const noexcept
		{
			return m_Entities;
		}

		virtual void OnKeyDown(unsigned char key, int x, int y) noexcept = 0;

		virtual void OnKeyUp(unsigned char key, int x, int y) noexcept = 0;

		virtual void OnMouseMotion(int x, int y) noexcept = 0;

		virtual void OnMouseClick(int button, bool state, int x, int y) noexcept = 0;

		virtual void Update(float deltaTime, long time = 0) noexcept;

		virtual void Draw() const noexcept = 0;

		virtual void OnMessage(const MessageContainer& msg) const noexcept;
	};
}

#endif //BLADE_SCENE_H_
