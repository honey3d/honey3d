local root = honey.node(nil,
			honey.glm.vec3{0,0,0},
			honey.glm.vec3{0,0,0},
			honey.glm.vec3{1,1,1})

local child = honey.node(root,
			 honey.glm.vec3{0,0,0},
			 honey.glm.vec3{0,0,0},
			 honey.glm.vec3{1,1,1})

local v = honey.glm.vec3{1, 2, 3}

local M = honey.glm.mat4()
M:set(1,3, 1)

print(M:mul(M))

print(v)
print(honey.glm.vec3{2, 0.001, 0})
print(honey.glm.vec4{100, 0, 0, 20.44})

v.dot(v, v)
