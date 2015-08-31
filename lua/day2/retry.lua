-- Exercise(hard, 1): Using coroutines, write a fault-tolerant function
-- retry(count, body) that works as follows:
--   * Call the body() function
--   * If body() yields a string with coroutine.yield(), consider this an error
--     message and restart body() from its beginning.
--   * Don't retry more than `count` times; if you exceed `count`, print an
--     error message and return.
--   * If `body()` returns without yielding a string, consider this a success.
--
-- Example usage:
--
--     retry(5,
--           function()
--             if math.random() > 0.2 then
--               coroutine.yield("Something bad happened.")
--             end
--             print("Succeeded")
--           end)
--
-- Most of the time, the inner function will fail; retry() should keep trying
-- until it's achieved success or tried five times.
--
-- Hint: you may need to create more than one coroutine.

function retry(count, body)
  local error_message = nil
  for i = 1, count do
    local co = coroutine.create(body)
    _, error_message = coroutine.resume(co)
    if not error_message then
      return true
    end
  end
  if error_message then
    print(error_message)
    return false
  end
  return true
end
