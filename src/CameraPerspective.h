// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution)
		, m_pos(pos)
		, m_dir(dir)
		, m_up(up)

	{
		//determine axis and normalize the positions
		m_xAxis = m_zAxis.cross(m_up);
		m_xAxis = normalize(m_xAxis);
		
		m_yAxis = m_zAxis.cross(m_xAxis);
		m_yAxis = normalize(m_yAxis);
		
		m_zAxis = dir;
		m_zAxis = normalize(m_zAxis);

		m_aspect = static_cast<float>(resolution.width) / resolution.height;
		m_focus = 1.0f / tanf(angle * Pif / 360);	
	}
	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray& ray) override {

		//shifts to center of pixel
		float x2 = 0.5f;	
		float y2 = 0.5f;	

		//calculate screen position coordinates
		float coorx = 2 * (x + x2) / getResolution().width - 1;
		float coory = 2 * (y + y2) / getResolution().height - 1;

		//generate ray 
		ray.org = m_pos;
		ray.dir = normalize(m_aspect * coorx * m_xAxis + coory * m_yAxis + m_focus * m_zAxis);
		ray.t = std::numeric_limits<float>::infinity();
		
		return true;
	}


private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;
};

