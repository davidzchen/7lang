-- Exercise(easy, 1): Write a function called `ends_in_3(num)` that returns
-- `true` if the final digit of `num` is 3, and `false` otherwise.

-- Returns true if num is divisible by 3.
function ends_in_3(num)
  return num % 10 == 3
end
