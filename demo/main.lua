for k, v in pairs(honey.shader) do
    print(k, v)
end

honey.input.key.bind(honey.input.key.escape, honey.exit)

function honey.update(dt)
end

--function honey.draw()
--   print('draw!')
--end
