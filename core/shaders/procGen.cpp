
#include "procGen.h"

namespace shaders {
	ew::MeshData createSphere(float radius, int numSegments)
	{
		ew::MeshData data;
		ew::Vertex v;
		float thetaStep = (2 * ew::PI) / numSegments;
		float phiStep = ew::PI / numSegments;

		for (int row = 0; row <= numSegments; row++)
		{
			float phi = row * phiStep;

			for (int col = 0; col <= numSegments; col++)
			{
				float theta = col * thetaStep;
				v.pos.x = radius * cos(theta) * sin(phi);
				v.pos.y = radius * cos(phi);
				v.pos.z = radius * sin(theta) * sin(phi);
				v.normal = ew::Normalize(v.pos);
				v.uv = ew::Vec2((float)col / numSegments, (float)row / numSegments);
				data.vertices.push_back(v);
			}
		}
		//top cap
		int poleStart = 0;
		int sideStart = numSegments + 1;
		for (int i = 0; i < numSegments; i++)
		{
			data.indices.push_back(sideStart + i);
			data.indices.push_back(poleStart + i);
			data.indices.push_back(sideStart + i + 1);
		}
		//bottom cap
		poleStart = (data.vertices.size() - 1) - numSegments;
		sideStart = (poleStart - 1) - numSegments;
		for (int i = 0; i < numSegments; i++)
		{
			data.indices.push_back(sideStart + i);
			data.indices.push_back(sideStart + i + 1);
			data.indices.push_back(poleStart + i);
		}
		//side
		int columns = numSegments + 1;
		for (int row = 1; row < numSegments - 1; row++)
		{
			for (int col = 0; col < numSegments; col++)
			{
				int start = row * columns + col;

				//triangle 1
				data.indices.push_back(start);
				data.indices.push_back(start + 1);
				data.indices.push_back(start + columns);

				//triangle 2
				data.indices.push_back(start + columns);
				data.indices.push_back(start + 1);
				data.indices.push_back(start + columns + 1);
			}
		}

		return data;
	}

	ew::MeshData createCylinder(float height, float radius, int numSegments)
	{
		ew::MeshData data;
		ew::Vertex v;
		float topY = height / 2;
		float bottomY = -topY;
		float thetaStep = (2 * ew::PI) / numSegments;

		//top center
		v.pos = ew::Vec3{ 0, topY, 0 };
		v.normal = ew::Vec3{ 0, 1, 0 };
		data.vertices.push_back(v);

		//top ring 1
		for (int i = 0; i <= numSegments; i++)
		{
			float theta = i * thetaStep;

			v.pos.x = cos(theta) * radius;
			v.pos.z = sin(theta) * radius;
			v.pos.y = topY;
			v.normal = ew::Vec3{ 0, 1, 0 };
			v.uv = ew::Vec2((cos(theta) * radius) * 0.5, (sin(theta) * radius) * 0.5);

			data.vertices.push_back(v);
		}

		//top ring 2
		for (int i = 0; i <= numSegments; i++)
		{
			float theta = i * thetaStep;

			v.pos.x = cos(theta) * radius;
			v.pos.z = sin(theta) * radius;
			v.pos.y = topY;
			v.normal = ew::Vec3{ cos(theta), 0, sin(theta) };
			v.uv = ew::Vec2((float)i / numSegments, 1);

			data.vertices.push_back(v);
		}

		//bottom ring 1
		for (int i = 0; i <= numSegments; i++)
		{
			float theta = i * thetaStep;

			v.pos.x = cos(theta) * radius;
			v.pos.z = sin(theta) * radius;
			v.pos.y = bottomY;
			v.normal = ew::Vec3{ cos(theta), 0, sin(theta) };
			v.uv = ew::Vec2((float)i / numSegments, 0);

			data.vertices.push_back(v);
		}

		//bottom ring 2
		for (int i = 0; i <= numSegments; i++)
		{
			float theta = i * thetaStep;

			v.pos.x = cos(theta) * radius;
			v.pos.z = sin(theta) * radius;
			v.pos.y = bottomY;
			v.normal = ew::Vec3{ 0, -1, 0 };
			v.uv = ew::Vec2((cos(theta) * radius) * 0.5, (sin(theta) * radius) * 0.5);

			data.vertices.push_back(v);
		}

		//bottom center
		v.pos = ew::Vec3{ 0, bottomY, 0 };
		v.normal = ew::Vec3{ 0, -1, 0 };
		data.vertices.push_back(v);

		//top cap
		int center = 0;
		int start = center + 1;
		for (int i = 0; i < numSegments; i++)
		{
			data.indices.push_back(start + i);
			data.indices.push_back(center);
			data.indices.push_back(start + i + 1);
		}

		//bottom cap
		center = data.vertices.size() - 1;
		start = center - 1;
		for (int i = 0; i < numSegments; i++)
		{

			data.indices.push_back(start - i);
			data.indices.push_back(center);
			data.indices.push_back(start - i - 1);
		}

		//side
		center = 0;
		int sideStart = numSegments + 2;
		int columns = numSegments + 1;

		for (int i = 0; i < columns; i++)
		{
			start = sideStart + i;

			//triangle 1
			data.indices.push_back(start);
			data.indices.push_back(start + 1);
			data.indices.push_back(start + columns);

			//triangle 2
			data.indices.push_back(start + columns);
			data.indices.push_back(start + 1);
			data.indices.push_back(start + columns + 1);
		}



		return data;
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
				v.pos.x = width * ((float)col / subdivisions);
				v.pos.z = -height * ((float)row / subdivisions);
				v.normal = ew::Vec3{ 0, 1, 0 };
				v.uv = ew::Vec2((float)col / subdivisions, (float)row / subdivisions);
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
}
