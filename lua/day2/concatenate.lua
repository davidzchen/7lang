-- Exercise(easy, 1): Write a function called `concatenate(a1, a2)` that takes
-- two arrays and returns a new array with all the elements of `a1` followed
-- by all the elements of `a2`.
function concatenate(a1, a2)
  local joined = {}
  for i, element in ipairs(a1) do
    joined[#joined + 1] = element
  end
  for i, element in ipairs(a2) do
    joined[#joined + 1] = element
  end
  return joined
end

-- Exercise(medium, 1): Change the global metatable you discovered in the Find
-- section earlier so that any time you try to add two arrays using the plus
-- operator (e.g. `a1 + a2`), Lua concatenates them together using your
-- `concatenate()` function.
setmetatable(_G, {
  __newindex = function(table, key, value)
    if type(value) == 'table' then
      setmetatable(value, { __add = concatenate })
    end
    rawset(_G, key, value)
  end
})

-- The above code only overrides the __add metamethod for tables declared as
-- global values. This function is used as a workaround for creating tables
-- declared as local with the __add metamethod overridden.
-- TODO(dzc): Find a way to override __add for local tables automatically
-- without this workaround.
function create_table(table)
  local addable_table = {}
  if table then
    addable_table = table
  end
  setmetatable(addable_table, {
    __add = concatenate
  })
  return addable_table
end
