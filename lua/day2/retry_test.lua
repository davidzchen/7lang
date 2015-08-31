-- Unit tests for retry.

dofile("retry.lua")

local function test_successful()
  counter = 0
  result = retry(6,
      function()
        if counter < 5 then
          counter = counter + 1
          coroutine.yield("Something bad happened.")
        end
        print("Succeeded")
      end)
  assert(result == true)
end

local function test_failure()
  result = retry(5, function() coroutine.yield("Something bad happened.") end)
  assert(result == false)
end

test_successful()
test_failure()
