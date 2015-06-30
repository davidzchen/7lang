-- Exercise(medium, 2): Using Lua's built-in OO syntax, write a class called
-- `Queue` that implements a first-in, first-out (FIFO) queue as follows:
--
-- q = Queue:new() returns a new object
-- q:add(item) adds item past last currently in queue
-- q:remove() removes and returns the first item in the queue, or nil if the
-- queue is empty.

Queue = { }
Queue.__index = Queue

function Queue:new()
  local queue = {
    items = {},
    front = 1,
    back = 0,
    shift_threshold = 10
  }
  return setmetatable(queue, Queue)
end

function Queue:add(item)
  self.back = self.back + 1
  self.items[self.back] = item
end

function Queue:shift()
  if self.front <= self.shift_threshold then
    return
  end
  local size = self.back - self.front + 1
  for i = 0, size - 1 do
    self.items[i + 1] = self.items[self.front + i]
  end
  if self.back > size then
    for i = size + 1, self.back do
      self.items[i] = nil
    end
  end
  self.front = 1
  self.back = size
end

function Queue:items()
  local items = {}
  for i = self.front, self.back do
    items[#items + 1] = self.items[i]
  end
  return items
end

function Queue:size()
  return self.back - self.front + 1
end

function Queue:remove()
  local item = self.items[self.front]
  self.front = self.front + 1
  if self.front > self.shift_threshold then
    self:shift()
  end
  return item
end
