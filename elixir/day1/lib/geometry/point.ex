# Exercise(easy, 1): Express some geometry objects using tuples: a
# two-dimensional point, a line, a circle, a polygon, and a triangle.

# Points are tuples {x, y}
defmodule Geometry.Point
  import Dict

  def new_point({x, y}), do: [x: x, y: y]
  def x(point), do: get(point, :x)
  def y(point), do: get(point, :y)
end
