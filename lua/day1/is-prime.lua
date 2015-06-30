-- Exercise(easy, 2): Write a funcvtion called `is_prime(num)` to test if a
-- number is prime (that is, it's divisible only by itself and 1).

-- Naive implementation of primality check.
function is_prime(num)
  if num <= 3 then
    return true
  end

  for i = 2, num - 1 do
    if num % i == 0 then
      return false
    end
  end
  return true
end
