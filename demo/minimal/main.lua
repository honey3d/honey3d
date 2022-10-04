print('hello, world!')
local canary = honey.util.gc_canary(function() print('collecting canary') end)
