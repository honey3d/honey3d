local fullscreen = false

local a_func = function(action, data)
    if (action == 0) then return end
    fullscreen = not fullscreen
    honey.window.set_fullscreen(fullscreen)
end

local resize_func = function(width, height, data)
    local w, h = honey.window.get_size()
    print('resized!', w, h)
end

local mousemove = function(x, y)
    print(x, y)
end

honey.window.set_title('honey engine demo')

honey.input.key.bind(honey.input.key.a, a_func)
honey.input.key.bind(honey.input.key.escape, honey.exit)
honey.window.resize_bind(resize_func)
honey.input.mouse.set_mode( honey.input.mouse.mode.disabled )
honey.input.mouse.bind_movement(mousemove)


local focus_func = function(focus)
    print('focus:', focus)
end

honey.window.focus_bind(focus_func)
    

function honey.update(dt)
end

--function honey.draw()
--   print('draw!')
--end
