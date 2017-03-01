#ifndef BLADE_BOUNDING_CYLINDER_H_
#define BLADE_BOUNDING_CYLINDER_H_

#include "bounding_volume.h"
/**
* \brief Bounding Cylinder class
*/
class BoundingCylinder : public BoundingVolume
{
private:
	float m_Height;
	float m_Radius;
//TO DO: Add all relevant members
public:
	BoundingCylinder();
	BoundingCylinder(BoundingCylinder&) = delete;
	BoundingCylinder& operator=(BoundingCylinder) = delete;
	~BoundingCylinder();

};

#endif // BLADE_BOUNDING_CYLINDER_H_