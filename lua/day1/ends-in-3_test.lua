dofile("ends-in-3.lua")

function test_ends_in_3()
  assert(ends_in_3(3) == true)
  assert(ends_in_3(13) == true)
  assert(ends_in_3(103) == true)
  assert(ends_in_3(4444443) == true)

  assert(ends_in_3(5) == false)
  assert(ends_in_3(0) == false)
  assert(ends_in_3(10) == false)
  assert(ends_in_3(33333334) == false)
end

test_ends_in_3()
