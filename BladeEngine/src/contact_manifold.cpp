#include "contact_manifold.h"

using namespace Blade;

void ContactManifold::AddEntry(const ManifoldEntry& manifoldEntry) noexcept
{
	m_ManifoldEntries.push_back(manifoldEntry);
}

const ManifoldEntry& ContactManifold::GetEntry(int index) const noexcept
{
	return m_ManifoldEntries[index];
}

const ManifoldEntry& ContactManifold::operator[](int index) const noexcept
{
	return m_ManifoldEntries[index];
}

const size_t ContactManifold::Size() const noexcept
{
	return m_ManifoldEntries.size();
}

void ContactManifold::Clear() noexcept
{
	m_ManifoldEntries.clear();
}
