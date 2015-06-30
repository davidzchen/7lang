-- Exercise(hard, 1): Write a function `reduce(max, init, f)` that calls a
-- function `f()` over the integers 1 to `max` like so:
--
-- function add(previous, next)
--   return previous + next
-- end
--
-- reduce(5, 0, add)  -- add the numbers from 1 to 5
--
-- This would result in `reduce()` calling `add()` 5 times with each
-- intermediate result, and return the final value of 15:
--
-- add(0, 1)  --> returns 1; feed this into the next call
-- add(1, 2)  --> returns 3
-- add(3, 3)  --> returns 6
-- add(6, 4)  --> returns 10
-- add(10, 5)  --> returns 15

-- Calls a function f() over the integers from 1 to max.
function reduce(max, init, f)
  local prev = 0
  for i = 1, max do
    prev = f(prev, i)
  end
  return prev
end
