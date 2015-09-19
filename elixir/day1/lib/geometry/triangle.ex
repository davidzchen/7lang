# Exercise(easy, 1): Express some geometry objects using tuples: a
# two-dimensional point, a line, a circle, a polygon, and a triangle.

# A triangle is represented by three points.
defmodule Geometry.Triangle
  import Dict
  import Geometry.Point
  import Geometry.Line

  def new_triangle(point1, point2, point3) do
    [
      vertices: [point1, point2, point3],
      sides: [
        Geometry.Line(point1, point2),
        Geometry.Line(point1, point3),
        Geometry.Line(point2, point3)
      ]
    ]
  end

  def circumference(triangle) do
    [side1, side2, side3] = get(triangle, :sides)
    Geometry.Line.length(side1) +
        Geometry.Line.length(side2) +
        Geometry.Line.length(side3)
  end

  # Calculation of area of triangle using Heron's Formula.
  def area(triangle) do
    [side1, side2, side3] = get(triangle, :sides)
    length1 = Geometry.Line.length(side1)
    length2 = Geometry.Line.length(side2)
    length3 = Geometry.Line.length(side3)
    s = (length1 + length2 + length3) / 2
    :math.sqrt(s * (s - length1) * (s - length2) * (s - length3))
  end
end
