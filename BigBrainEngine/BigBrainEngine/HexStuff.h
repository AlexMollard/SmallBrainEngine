#pragma once

// void CreateHexagon(Model* model, Material* mat);
// void CreateCell(int Q, int R);
// glm::vec2 AxialFlatToWorld(int q, int r);
//
// Grid Stuff
// std::vector<GameObject*> map;
// int GridSize = 10;
// float HexScale = .29f;
// int NumberOfSubTexturesAcross = 32;
// float randomNoiseNum = 0.0f;
//
// CreateHexagon(&hexModel, &planeMat);
//
// for (int i = 0; i < map.size(); i++)
// {
// delete map[i];
// }
// 
// map.clear();
//
// void CreateHexagon(Model* model, Material* mat)
// {
// 	for (int q = -GridSize; q <= GridSize; q++)
// 	{
// 		int r1 = glm::max(-GridSize, -q - GridSize);
// 		int r2 = glm::min(GridSize, -q + GridSize);
// 
// 		for (int r = r1; r <= r2; r++)
// 		{
// 			map.push_back(new GameObject(*model, *mat));
// 			CreateCell(q, r);
// 		}
// 	}
// }
// 
// void CreateCell(int Q, int R)
// {
// 	glm::vec2 NewUVPos(1.0f, 1.0f);
// 
// 	float posQ = AxialFlatToWorld(Q, R).y;
// 	float posR = AxialFlatToWorld(Q, R).x;
// 	float noise = glm::clamp(((glm::perlin(glm::vec2(posQ / 5.0f + randomNoiseNum, posR / 5.0f + randomNoiseNum)) + 1.0f) / 2.0f), 0.0f, 0.9f);
// 
// 	map.back()->SetPostition(glm::vec3(posQ, 0.0f, posR));
// 	map.back()->SetScale(glm::vec3(0.005f, noise / 20.0f, 0.005f));
// 
// 
// 	float horizontalOffset = glm::round(((noise - 1) * -1) * 16.0f);
// 
// 	float verticalOffset = 0.0f;
// 	if (noise < 0.35f)
// 	{
// 		map.back()->SetScale(glm::vec3(0.005f, 0.015f, 0.005f));
// 		verticalOffset = 8.0;
// 	}
// 	else if (noise < 0.45f)
// 	{
// 		verticalOffset = 7.0;
// 	}
// 	else if (noise < 0.75f)
// 	{
// 		verticalOffset = 5.0;
// 	}
// 	else
// 	{
// 		verticalOffset = 4.0;
// 	}
// 
// 	NewUVPos /= NumberOfSubTexturesAcross;
// 	NewUVPos += glm::vec2(horizontalOffset / NumberOfSubTexturesAcross, verticalOffset / NumberOfSubTexturesAcross);
// 
// 	map.back()->UvPos = NewUVPos;
// 
// 	gameObjectManager.AddObject(*map.back());
// }
// 
// glm::vec2 AxialFlatToWorld(int q, int r)
// {
// 	float x = HexScale * (3.0f / 2.0f * q);
// 	float y = HexScale * (glm::sqrt(3.0f) / 2.0f * q + (glm::sqrt(3.0f) * r));
// 
// 	return glm::vec2(x, y);
// }