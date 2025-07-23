--
-- DESCRIPTION
--
-- @COMPANY 
-- @AUTHOR 
-- @DATE 2025/07/23 14:15:53
--

local Screen = require "Screen"

---@type ControlPad_C
local M = UnLua.Class()

function M:Initialize()
    local msg = [[
        Hello World!
    ]]
    print(msg)
    Screen.Print(msg)
end

--function M:PreConstruct(IsDesignTime)
--end

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

return M
