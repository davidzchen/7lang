-- Exercise(medium, 1): What if Lua didn't have a `for` loop? Using `if` and
-- `while`, write a function `for_loop(a, b, f)` that calls `f()` on each
-- integer from `a` to `b` (inclusive).

-- for loop implemented using if and while.
function for_loop(a, b, f)
  local i = a
  while i <= b do
    f(i)
  end
end
