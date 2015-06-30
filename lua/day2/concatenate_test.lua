dofile("concatenate.lua")

local function array_equals(array1, array2)
  if #array1 ~= #array2 then
    return false
  end
  for i, value in ipairs(array1) do
    if array2[i] ~= value then
      return false
    end
  end
  return true
end

local function test_concatenate()
  assert(array_equals({1, 2, 3, 4, 5, 6, 7, 8},
                      concatenate({1, 2, 3, 4}, {5, 6, 7, 8})))
  assert(array_equals({5, 6, 7, 8}, concatenate({}, {5, 6, 7, 8})))
  assert(array_equals({1, 2, 3, 4}, concatenate({1, 2, 3, 4}, {})))
end

local function test_concatenate_operator()
  assert(1 + 2 == 3)

  local arr1 = create_table({1, 2, 3, 4})
  local arr2 = create_table({5, 6, 7, 8})
  local empty = create_table({})
  assert(array_equals({1, 2, 3, 4, 5, 6, 7, 8}, arr1 + arr2))
  assert(array_equals({5, 6, 7, 8}, empty + arr2))
  assert(array_equals({1, 2, 3, 4}, arr1 + empty))
end

test_concatenate()
test_concatenate_operator()
