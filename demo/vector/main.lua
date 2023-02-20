require 'common'

local window = honey.window
local nvg = honey.nvg


local vg

function honey.init()
	vg = nvg.CreateContext()
end


local time = 0
local frames = 0
function honey.update(dt)
	if window.getKey(window.win, window.KEY_ESCAPE) == window.PRESS then
		window.setShouldClose(honey.window.win, true)
	end
	
	time = time + dt
	frames = frames + 1
	if time > 5 then
		print('fps:', frames/5)
		frames = 0
		time = time - 5
	end
end


function honey.draw()
	nvg.BeginFrame(vg, 640, 480, 1.0)
	nvg.StrokeWidth(vg, 20)
	nvg.StrokeColor(vg, nvg.RGB(1, 0, 0))

	local w = 640
	local h = 480

	nvg.BeginPath(vg)
	nvg.MoveTo(vg, w*0.2, h*.5)
	nvg.LineTo(vg, w*0.4, h * (0.5 + 0.5*math.sin(math.pi * time)));
	nvg.LineTo(vg, w*0.6, h * (0.5 - 0.5*math.sin(math.pi * time)));
	nvg.LineTo(vg, w*0.8, h*.5)
	nvg.Stroke(vg)

	nvg.EndFrame(vg)
end


honey.run()
