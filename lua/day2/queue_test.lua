dofile("queue.lua")

function test_shift()
  q = Queue:new()
  assert(q:size() == 0)
  for i = 1, 20 do
    q:add(i)
    assert(q:size() == i)
  end
  assert(q:size() == 20)

  local back = q.back
  for i = 1, 9 do
    assert(q:remove() == i)
    assert(q:size() == 20 - i)
    assert(q.back == back)
    assert(q.front == i + 1)
  end

  assert(q:remove() == 10)
  assert(q:size() == 10)
  assert(q.front == 1)
  assert(q.back == 10)
  assert(q.items[q.front] == 11)
  assert(q.items[q.back] == 20)
end

function test_add_remove()
  q = Queue:new()
  assert(q:size() == 0)
  for i = 1, 20 do
    q:add(i)
    assert(q:size() == i)
  end
  assert(q:size() == 20)

  for i = 1, 20 do
    assert(q:remove() == i)
    assert(q:size() == 20 - i)
  end
  assert(q:size() == 0)
end

test_shift()
test_add_remove()
