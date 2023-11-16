# Jakub Jaśków 268416
include("Utils.jl")
using .Utils
epsilon = delta = 10^-3

@testset "TEST: 1" begin
  f = x -> atan(x)
  r = 0.
  delta = epsilon = 10^-10
  res = msiecznych(f, -1.5, 1., delta, epsilon, 10)
  x = res[1]
  fx = res[2]
  @test abs(fx) <= epsilon
  @test abs(r-x) <= delta
  @test res[4] == 0
end
@testset "TEST: 2" begin
  f = x -> atan(x)
  r = 0.
  res = msiecznych(f, 341000244450., 1120323240., delta, epsilon, 50)
  x = res[1]
  fx = res[2]
  @test abs(fx) > epsilon
  @test abs(r-x) > delta
  @test res[4] == 1
end