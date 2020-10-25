local fullscreen = false

local a_func = function(action, data)
    if (action == 0) then return end
    fullscreen = not fullscreen
    honey.window.set_fullscreen(fullscreen)
end

local b_func = function(action, data)
    if (action == 0) then return end
    local w, h = honey.window.get_size()
    print(w, h)
end

for k,v in pairs(honey.window) do
    print(k, v)
end

honey.window.set_title('honey engine demo')

honey.input.bind_key(honey.input.key.a, a_func)
honey.input.bind_key(honey.input.key.b, b_func)

function honey.update(dt)
end

--function honey.draw()
--   print('draw!')
--end
