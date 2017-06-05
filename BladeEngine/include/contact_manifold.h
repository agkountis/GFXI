#ifndef BLADE_CONTACT_MANIFOLD_H_
#define BLADE_CONTACT_MANIFOLD_H_
#include <vector>
#include "types.h"

namespace Blade
{
	class Collider;

	/*
	\brief ManifoldEntry stores the information about a contact
	\details Stores of the two colliders that are in contact, the contact normal 
	the time of the contact and the penetration. 
	*/
	struct ManifoldEntry
	{
		const Collider* collider1;
		const Collider* collider2;
		Vec3f			contactNormal;
		float t{ 0.0f };
		float penetration{ 0.0f };
	};

	/*
	\brief Gather all the contact detected.
	*/
	class ContactManifold
	{
	private:
		/*
		\brief Stores the the entries
		*/
		std::vector<ManifoldEntry> m_ManifoldEntries;

	public:
		/*
		\brief Add a new entry in the manifold
		\param manifoldEntry the new entry to add to the manifold
		*/
		void AddEntry(const ManifoldEntry& manifoldEntry) noexcept;
		
		/*
		\brief Getters of the ContactManifold
		*/
		const ManifoldEntry& GetEntry(const int index) const noexcept;
		const ManifoldEntry& operator[](const int index) const noexcept;

		/*
		\brief Returns the current size of the contact manifold
		\return Current size of the manifold
		*/
		const size_t Size() const noexcept;

		/*
		\brief Clear the manifold 
		*/
		void Clear() noexcept;
	};
}

#endif