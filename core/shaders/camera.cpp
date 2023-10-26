#include "camera.h"
namespace shaders {
	ew::Mat4 Camera::ViewMatrix()
	{
		ew::Vec3 up = ew::Vec3(0, 1, 0);
		return shaders::LookAt(position, target, up);
	}

	ew::Mat4 Camera::ProjectionMatrix()
	{
		if (orthographic)
		{
			return shaders::Perspective(orthoSize, aspectRatio, nearPlane, farPlane);
		}
		else
		{
			return shaders::Orthographic(fov, aspectRatio, nearPlane, farPlane);
		}
	}
}