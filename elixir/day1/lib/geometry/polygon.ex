# Exercise(easy, 1): Express some geometry objects using tuples: a
# two-dimensional point, a line, a circle, a polygon, and a triangle.

# A polygon can be represented as a list of points.
defmodule Geometry.Polygon
  import Dict
  import Geometry.Point
  import Geometry.Line

  def new_polygon(points) do
    # TODO(dzc): Validate that the list of points comprise a valid polygon,
    # create Geometry.Line objects for sides.
    [vertices: points, sides: sides]
  end

  def area(polygon) do
    # TODO(dzc): Implement area of irregular polygon, which is a generalization
    # of area of a regular polygon. Also, consider detecting whether the polygon
    # is regular, and have an optimized implementation if the polygon is
    # regular.
  end

  # Compute circumference by recursively adding the lengths of the sides.
  def circumference(polygon) do
    circumference(get(polygon, :sides))
  end
  def circumference([]), do: 0
  def circumference([head | tail]) do
    Geometry.Line.length(head) + circumference(tail)
  end
end
