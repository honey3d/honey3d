for key, value in pairs(honey.input) do
   print(key, value)
end

local total_time = 0

local a_func = function(action, data)
    print('a: ', action)
end

honey.input.bind_key(honey.input.key.a, a_func)
honey.input.bind_key()

function honey.update(dt)

end

--function honey.draw()
--   print('draw!')
--end
