# Exercise(easy, 1): Express some geometry objects using tuples: a
# two-dimensional point, a line, a circle, a polygon, and a triangle.

# A circle is a point representing the center and a radius: {{x, y}, r}
defmodule Geometry.Circle
  import Dict
  import Geometry.Point

  def new_circle({x, y}, radius) do
    [
      center: Point.new_point {x, y},
      radius: radius
    ]
  end

  def circumference(circle) do
    radius = get(circle, :radius)
    2 * radius * :math.pi
  end

  def area(circle) do
    radius = get(circle, :radius)
    :math.pow(radius, 2) * :math.pi
  end
end
