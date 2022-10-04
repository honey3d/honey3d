local Texture = {}
local gl = honey.gl
setmetatable(Texture, {__index=_G})
setfenv(1, Texture)


--===== loading =====--

function Load(filename)
	local texture = gl.GenTextures()
	gl.BindTexture(gl.TEXTURE_2D, texture)
	
	gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.REPEAT)
	gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.REPEAT)
	
	gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR)
	gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR)
	
	local image, width, height = honey.image.load(filename, 3)
	gl.TexImage2D(
	        gl.TEXTURE_2D, 0,
	        gl.RGB, width, height,
	        gl.RGB, gl.UNSIGNED_BYTE,
	        image
	)
	gl.GenerateMipmap(gl.TEXTURE_2D)
	honey.image.destroy(image)

	return texture
end


--===== fin =====--

return Texture
