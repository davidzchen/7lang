dofile("is-prime.lua")

function test_is_prime()
  assert(is_prime(1) == true)
  assert(is_prime(2) == true)
  assert(is_prime(3) == true)
  assert(is_prime(4) == false)
  assert(is_prime(5) == true)
  assert(is_prime(6) == false)
  assert(is_prime(7) == true)
  assert(is_prime(8) == false)
  assert(is_prime(9) == false)
  assert(is_prime(10) == false)
  assert(is_prime(11) == true)
  assert(is_prime(12) == false)

  print("Tests pass.")
end

test_is_prime()
