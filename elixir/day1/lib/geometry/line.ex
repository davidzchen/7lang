# Exercise(easy, 1): Express some geometry objects using tuples: a
# two-dimensional point, a line, a circle, a polygon, and a triangle.

# A line is a tuple containing two points: {{x1, y1}, {x2, y2}}
defmodule Geometry.Line
  import Dict
  import Geometry.Point

  def new_line({x1, y1}, {x2, y2}) do
    [
      point1: Point.new_point {x1, y1},
      point2: Point.new_point {x2, y2}
    ]
  end

  def length(line) do
    point1 = get(line, :point1)
    point2 = get(line, :point2)
    Line.distance(point1, point2)
  end

  def distance(point1, point2) do
    :math.sqrt(
        :math.pow((Point.x(point2) - Point.x(point1)), 2) +
        :math.pow((Point.y(point2) - Point.y(point1)), 2))
  end
end
