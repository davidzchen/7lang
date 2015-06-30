-- Exercise(easy, 3): Create a program to print the first `n` prime numbers
-- that end in 3.
--
-- Invoke this script on the command line as follows:
--
-- $ lua n-primes.lua NUM_PRIMES

dofile("ends-in-3.lua")
dofile("is-prime.lua")

-- Prints the first n primes that end in 3
function n_primes(n)
  local count = 0
  local i = 1
  local primes = {}
  while count < n do
    if is_prime(i) and ends_in_3(i) then
      primes[#primes + 1] = i
      count = count + 1
    end
    i = i + 1
  end
  return primes
end

function main()
  local n = tonumber(arg[1])
  local primes = n_primes(n)
  for i, prime in ipairs(primes) do
    print(prime)
  end
end

main()
