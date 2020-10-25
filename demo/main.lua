for key, value in pairs(honey.input) do
   print(key, value)
end

local fullscreen = false

local a_func = function(action, data)
    fullscreen = not fullscreen
    honey.window.set_fullscreen(fullscreen)
end

honey.input.bind_key(honey.input.key.a, a_func)

function honey.update(dt)
end

--function honey.draw()
--   print('draw!')
--end
