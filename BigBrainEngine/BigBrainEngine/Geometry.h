#pragma once
struct Shapes3D
{
		// Cube Attributes
		float Cube[216] =
		{
			 // positions			  // Normals  
			-0.5f, -0.5f, -0.5f,	  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,	  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,	  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,	  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,	  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,	  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,	  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,	  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,	  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,	  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,	  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,	  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f,  0.5f,	 -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,	 -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,	 -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,	 -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,	 -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,	 -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,	  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,	  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,	  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,	  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,	  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,	  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,	  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,	  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,	  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,	  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,	  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,	  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,	  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,	  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,	  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,	  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,	  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,	  0.0f,  1.0f,  0.0f
		};
};