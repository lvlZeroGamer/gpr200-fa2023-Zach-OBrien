#include "procGen.h"

ew::MeshData createSphere(float radius, int numSegments)
{
	ew::MeshData data;

}

ew::MeshData createCylinder(float height, float radius, int numSegments)
{
	ew::MeshData data;
	ew::Vertex v;
	int topY = height / 2;
	int bottomY = -topY;
	float thetaStep = (2 * PI) / numSegments;

	//top center
	v.pos = ew::Vec3{ 0, topY, 0 };
	data.vertices.push_back(v);

	//top ring
	for (int i = 0 : i <= numSegments; i++)
	{
		float theta = i * thetaStep;

		v.pos.x = cos(theta) * radius;
		v.pos.z = sin(theta) * radius;
		v.pos.y = topY;

		data.vertices.push_back(v);
	}
	//bottom ring
	for (int i = 0 : i <= numSegments; i++)
	{
		float theta = i * thetaStep;

		v.pos.x = cos(theta) * radius;
		v.pos.z = sin(theta) * radius;
		v.pos.y = bottomY;

		data.vertices.push_back(v);
	}
	//bottom center
	v.pos = ew::Vec3{ 0, bottomY, 0 };
	data.vertices.push_back(v);
}

ew::MeshData createPlane(float width, float height, int subdivisions)
{
	ew::MeshData data;
	ew::Vertex v;
	int columns = subdivisions + 1;

	for (int row = 0; row <= subdivisions; row++)
	{
		for (int col = 0; col <= subdivisions; col++)
		{
			v.pos.x = width * (col / subdivisions);
			v.pos.z = -height * (row / subdivisions);
			v.normal = ew::Vec3{ 0, 1, 0 };
			v.uv = ew::Vec2(col / subdivisions, row / subdivisions);
			data.vertices.push_back(v);
		}

		for (int row = 0; row < subdivisions; row++)
		{
			for (int col = 0; col < subdivisions; col++)
			{
				int start = row * columns + col;

				data.indices.push_back(start);
				data.indices.push_back(start + 1);
				data.indices.push_back(start + columns + 1);

				data.indices.push_back(start);
				data.indices.push_back(start + columns + 1);
				data.indices.push_back(start + columns);
			}
		}
	}
	return data;
}
