for key, value in pairs(honey.input) do
   print(key, value)
end

local total_time = 0

function honey.update(dt)
   if honey.input.is_down(honey.input.key.a) then
      print('a pressed!')
   end
end

--function honey.draw()
--   print('draw!')
--end
