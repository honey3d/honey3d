local fullscreen = false
local cursor_mode = honey.input.mouse.mode.normal

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
honey.input.key.bind(
    honey.input.key.c,
    function(action)
        local next_mode
        if cursor_mode == honey.input.mouse.mode.normal then
            next_mode = honey.input.mouse.mode.disabled
        else
            next_mode = honey.input.mouse.mode.normal
        end
        
        if action == 1 then
            honey.input.mouse.set_mode(next_mode)
            cursor_mode = next_mode
        end
    end
)
honey.window.resize_bind(resize_func)
honey.input.mouse.set_mode( honey.input.mouse.mode.disabled )
honey.input.mouse.bind_movement(mousemove)

function demo_cglm()
    local array = honey.cglm.new_array_zero(3)
    honey.cglm.set_value(array, 0, 0)
    honey.cglm.set_value(array, 1, 5)
    honey.cglm.set_value(array, 2, 2)
    local x = honey.cglm.get_value(array, 0)
    local y = honey.cglm.get_value(array, 1)
    local z = honey.cglm.get_value(array, 2)

    print(x, y, z)
end
demo_cglm()

local focus_func = function(focus)
    print('focus:', focus)
end

honey.window.focus_bind(focus_func)
    

function honey.update(dt)
end

--function honey.draw()
--   print('draw!')
--end
