#ifndef BLADE_BOUNDING_SPHERE
#define BLADE_BOUNDING_SPHERE

#include "bounding_volume.h"
/**
* \brief Bounding Sphere class
*/
class BoundingSphere: public BoundingVolume
{

private:
	float m_Radius;//unused yet
	//TO DO: Add all relevant members
public:
	BoundingSphere();
	BoundingSphere(BoundingSphere&) = delete;
	BoundingSphere& operator=(BoundingSphere&) = delete;
	~BoundingSphere();

};

#endif //BLADE_BOUNDING_SPHERE