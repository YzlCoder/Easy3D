#include "MeshGenerator.h"


namespace easym
{
	Mesh MeshGenerator::CreateBox(real width, real height, real depth)
	{
		Mesh mesh;
		mesh.vertices.resize(24);
		mesh.indices.resize(36);

		real halfW = width * 0.5f;
		real halfH = height * 0.5f;
		real halfD = depth * 0.5f;

		//forward z +

		//front
		mesh.vertices[0].pos = Vector3(-halfW, -halfH, -halfD);
		mesh.vertices[0].normal = Vector3(0.f, 0.f, -1.f);
		mesh.vertices[0].color = Vector4(1.f, 0.f, 0.f, 1.f);
		mesh.vertices[0].tex = Vector2(0.f, 1.f);
		mesh.vertices[1].pos = Vector3(-halfW, halfH, -halfD);
		mesh.vertices[1].normal = Vector3(0.f, 0.f, -1.f);
		mesh.vertices[1].color = Vector4(0.f, 0.f, 0.f, 1.f);
		mesh.vertices[1].tex = Vector2(0.f, 0.f);
		mesh.vertices[2].pos = Vector3(halfW, halfH, -halfD);
		mesh.vertices[2].normal = Vector3(0.f, 0.f, -1.f);
		mesh.vertices[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		mesh.vertices[2].tex = Vector2(1.f, 0.f);
		mesh.vertices[3].pos = Vector3(halfW, -halfH, -halfD);
		mesh.vertices[3].normal = Vector3(0.f, 0.f, -1.f);
		mesh.vertices[3].color = Vector4(0.f, 1.f, 0.f, 1.f);
		mesh.vertices[3].tex = Vector2(1.f, 1.f);

		//left
		mesh.vertices[4].pos = Vector3(-halfW, -halfH, halfD);
		mesh.vertices[4].normal = Vector3(-1.f, 0.f, 0.f);
		mesh.vertices[4].color = Vector4(0.f, 0.f, 1.f, 1.f);
		mesh.vertices[4].tex = Vector2(0.f, 1.f);
		mesh.vertices[5].pos = Vector3(-halfW, halfH, halfD);
		mesh.vertices[5].normal = Vector3(-1.f, 0.f, 0.f);
		mesh.vertices[5].color = Vector4(1.f, 1.f, 0.f, 1.f);
		mesh.vertices[5].tex = Vector2(0.f, 0.f);
		mesh.vertices[6].pos = Vector3(-halfW, halfH, -halfD);
		mesh.vertices[6].normal = Vector3(-1.f, 0.f, 0.f);
		mesh.vertices[6].color = Vector4(0.f, 0.f, 0.f, 1.f);
		mesh.vertices[6].tex = Vector2(1.f, 0.f);
		mesh.vertices[7].pos = Vector3(-halfW, -halfH, -halfD);
		mesh.vertices[7].normal = Vector3(-1.f, 0.f, 0.f);
		mesh.vertices[7].color = Vector4(1.f, 1.f, 1.f, 1.f);
		mesh.vertices[7].tex = Vector2(1.f, 1.f);

		//back
		mesh.vertices[8].pos = Vector3(halfW, -halfH, halfD);
		mesh.vertices[8].normal = Vector3(0.f, 0.f, 1.f);
		mesh.vertices[8].color = Vector4(1.f, 0.f, 1.f, 1.f);
		mesh.vertices[8].tex = Vector2(0.f, 1.f);
		mesh.vertices[9].pos = Vector3(halfW, halfH, halfD);
		mesh.vertices[9].normal = Vector3(0.f, 0.f, 1.f);
		mesh.vertices[9].color = Vector4(0.f, 1.f, 1.f, 1.f);
		mesh.vertices[9].tex = Vector2(0.f, 0.f);
		mesh.vertices[10].pos = Vector3(-halfW, halfH, halfD);
		mesh.vertices[10].normal = Vector3(0.f, 0.f, 1.f);
		mesh.vertices[10].color = Vector4(1.f, 1.f, 0.f, 1.f);
		mesh.vertices[10].tex = Vector2(1.f, 0.f);
		mesh.vertices[11].pos = Vector3(-halfW, -halfH, halfD);
		mesh.vertices[11].normal = Vector3(0.f, 0.f, 1.f);
		mesh.vertices[11].color = Vector4(0.f, 0.f, 1.f, 1.f);
		mesh.vertices[11].tex = Vector2(1.f, 1.f);

		//right
		mesh.vertices[12].pos = Vector3(halfW, -halfH, -halfD);
		mesh.vertices[12].normal = Vector3(1.f, 0.f, 0.f);
		mesh.vertices[12].color = Vector4(0.f, 1.f, 0.f, 1.f);
		mesh.vertices[12].tex = Vector2(0.f, 1.f);
		mesh.vertices[13].pos = Vector3(halfW, halfH, -halfD);
		mesh.vertices[13].normal = Vector3(1.f, 0.f, 0.f);
		mesh.vertices[13].color = Vector4(1.f, 0.f, 0.f, 1.f);
		mesh.vertices[13].tex = Vector2(0.f, 0.f);
		mesh.vertices[14].pos = Vector3(halfW, halfH, halfD);
		mesh.vertices[14].normal = Vector3(1.f, 0.f, 0.f);
		mesh.vertices[14].color = Vector4(0.f, 1.f, 1.f, 1.f);
		mesh.vertices[14].tex = Vector2(1.f, 0.f);
		mesh.vertices[15].pos = Vector3(halfW, -halfH, halfD);
		mesh.vertices[15].normal = Vector3(1.f, 0.f, 0.f);
		mesh.vertices[15].color = Vector4(1.f, 0.f, 1.f, 1.f);
		mesh.vertices[15].tex = Vector2(1.f, 1.f);

		//top
		mesh.vertices[16].pos = Vector3(-halfW, halfH, -halfD);
		mesh.vertices[16].normal = Vector3(0.f, 1.f, 0.f);
		mesh.vertices[16].color = Vector4(0.f, 0.f, 0.f, 1.f);
		mesh.vertices[16].tex = Vector2(0.f, 1.f);
		mesh.vertices[17].pos = Vector3(-halfW, halfH, halfD);
		mesh.vertices[17].normal = Vector3(0.f, 1.f, 0.f);
		mesh.vertices[17].color = Vector4(1.f, 1.f, 0.f, 1.f);
		mesh.vertices[17].tex = Vector2(0.f, 0.f);
		mesh.vertices[18].pos = Vector3(halfW, halfH, halfD);
		mesh.vertices[18].normal = Vector3(0.f, 1.f, 0.f);
		mesh.vertices[18].color = Vector4(0.f, 1.f, 1.f, 1.f);
		mesh.vertices[18].tex = Vector2(1.f, 0.f);
		mesh.vertices[19].pos = Vector3(halfW, halfH, -halfD);
		mesh.vertices[19].normal = Vector3(0.f, 1.f, 0.f);
		mesh.vertices[19].color = Vector4(1.f, 0.f, 0.f, 1.f);
		mesh.vertices[19].tex = Vector2(1.f, 1.f);

		//down
		mesh.vertices[20].pos = Vector3(-halfW, -halfH, halfD);
		mesh.vertices[20].normal = Vector3(0.f, -1.f, 0.f);
		mesh.vertices[20].color = Vector4(0.f, 0.f, 1.f, 1.f);
		mesh.vertices[20].tex = Vector2(0.f, 1.f);
		mesh.vertices[21].pos = Vector3(-halfW, -halfH, -halfD);
		mesh.vertices[21].normal = Vector3(0.f, -1.f, 0.f);
		mesh.vertices[21].color = Vector4(1.f, 1.f, 1.f, 1.f);
		mesh.vertices[21].tex = Vector2(0.f, 0.f);
		mesh.vertices[22].pos = Vector3(halfW, -halfH, -halfD);
		mesh.vertices[22].normal = Vector3(0.f, -1.f, 0.f);
		mesh.vertices[22].color = Vector4(0.f, 1.f, 0.f, 1.f);
		mesh.vertices[22].tex = Vector2(1.f, 0.f);
		mesh.vertices[23].pos = Vector3(halfW, -halfH, halfD);
		mesh.vertices[23].normal = Vector3(0.f, -1.f, 0.f);
		mesh.vertices[23].color = Vector4(1.f, 0.f, 1.f, 1.f);
		mesh.vertices[23].tex = Vector2(1.f, 1.f);

		mesh.indices[0] = 0;
		mesh.indices[1] = 1;
		mesh.indices[2] = 2;
		mesh.indices[3] = 0;
		mesh.indices[4] = 2;
		mesh.indices[5] = 3;

		mesh.indices[6] = 4;
		mesh.indices[7] = 5;
		mesh.indices[8] = 6;
		mesh.indices[9] = 4;
		mesh.indices[10] = 6;
		mesh.indices[11] = 7;

		mesh.indices[12] = 8;
		mesh.indices[13] = 9;
		mesh.indices[14] = 10;
		mesh.indices[15] = 8;
		mesh.indices[16] = 10;
		mesh.indices[17] = 11;

		mesh.indices[18] = 12;
		mesh.indices[19] = 13;
		mesh.indices[20] = 14;
		mesh.indices[21] = 12;
		mesh.indices[22] = 14;
		mesh.indices[23] = 15;

		mesh.indices[24] = 16;
		mesh.indices[25] = 17;
		mesh.indices[26] = 18;
		mesh.indices[27] = 16;
		mesh.indices[28] = 18;
		mesh.indices[29] = 19;

		mesh.indices[30] = 20;
		mesh.indices[31] = 21;
		mesh.indices[32] = 22;
		mesh.indices[33] = 20;
		mesh.indices[34] = 22;
		mesh.indices[35] = 23;

		return mesh;
	}
}
