for key, value in pairs(honey.input.key) do
   print(key, value)
end

local total_time = 0

function honey.update(dt)
   total_time = total_time + dt
   print(dt)
end

function honey.draw()
   print('draw!')
end
