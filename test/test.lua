local random = require'ottery'

local randomdata = {}
local dupes = 0

local num = 102400
local length = 1024

for i = 1, num do
	local data = random.hexstring(length)
	if randomdata[data] then
		dupes = dupes + 1
	end

	randomdata[data] = true
end

print(("We generated %d hex strings with a length of %d"):format(num, length))

if dupes > 0 then
	print("Duplicates was found :(")
else
	print("We're completely random!")
end
