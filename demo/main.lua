local v = honey.glm.vec3{1, 2, 3}

local M = honey.glm.mat3()
M:set(1,3, 1)

print(M:mulv(v))

print(v)
print(honey.glm.vec3{2, 0.001, 0})
print(honey.glm.vec4{100, 0, 0, 20.44})

v.dot(v, v)
