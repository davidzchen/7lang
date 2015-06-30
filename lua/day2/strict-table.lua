-- Exercise(easy, 2): Our strict table implementation doesn't provide a way to
-- delete items from the table. If we try the usual approach,
-- `treasure.gold = nil`, we will get a duplicate key error. Modify
-- `strict_write()` to allow deleting keys (by setting their values to `nil`).
--
-- Note that the strict table implementation here has also been modified to
-- use a private table in the table's metatable rather than a global private
-- table.

local function strict_read(table, key)
  local private_table = getmetatable(table).private_table
  if private_table[key] then
    return private_table[key]
  else
    error("Invalid key: " .. key)
  end
end

local function strict_write(table, key, value)
  local private_table = getmetatable(table).private_table
  if private_table[key] and value ~= nil then
    error("Duplicate key: " .. key)
  else
    private_table[key] = value
  end
end

function new()
  local table = {}
  setmetatable(table, {
    __index = strict_read,
    __newindex = strict_write,
    private_table = {}
  })
  return table
end

return {
  new = new
}
