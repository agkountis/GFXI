#ifndef BLADE_BOUNDING_BOX_H_
#define BLADE_BOUNDING_BOX_H_


#include "bounding_volume.h"
#include "math_utils.h"

namespace Blade
{
	/**
	* \brief Bounding Box class
	*/
	class BoundingBox : public BoundingVolume
	{

	private:
		Blade::Vec3d m_Size;// unused yet!
		//TO DO: Add all relevant members
	public:
		BoundingBox();
		BoundingBox(BoundingBox &) = delete;
		BoundingBox& operator=(BoundingBox&) = delete;
		~BoundingBox();

	};
}
#endif // BLADE_BOUNDING_BOX_H_