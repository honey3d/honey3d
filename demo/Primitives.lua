local Primitives = {}

function Primitives.plane(width, height)
   return honey.buildMesh{ position = { 0, 0, 0,
					width, 0, 0,
					0, height, 0,
					width, height, 0 },
			   normal = { 0, 0, 1,
				      0, 0, 1,
				      0, 0, 1,
				      0, 0, 1 },
			   uv = { 0, 0,
				  1, 0,
				  0, 1,
				  1, 1 },
			   faces = { 1, 2, 3,
				     4, 2, 1 } }
end

return Primitives
