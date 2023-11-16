# Jakub Jaśków 268416
epsilon = delta = 10^-3

@testset "Test positive" begin
  f = x -> x^3 - x
  r = 1.
  res = mbisekcji(f, 0.1, 5., delta, epsilon)
  x = res[1]
  fx = res[2]
  @test abs(fx) <= epsilon
  @test abs(r-x) <= delta
  @test res[4] == 0
end

@testset "TEST: flat function" begin
  f = x -> 1/x - 0.05
  r = 20.
  res = mbisekcji(f, 10., 25., delta, epsilon)
  x = res[1]
  fx = res[2]
  @test abs(fx) <= epsilon
  @test abs(r-x) > delta
  @test res[4] == 0
end

@testset "TEST: steep function" begin
  f = x -> ℯ^x - ℯ^5
  r = 5.
  res = mbisekcji(f, 4.5, 6., delta, epsilon)
  x = res[1]
  fx = res[2]
  @test abs(fx) > epsilon
  @test abs(r-x) <= delta
  @test res[4] == 0
end

@testset "TEST: same sign at interval ends" begin
  f = x -> x^2
  r = 0.
  res = mbisekcji(f, -1., 2., delta, epsilon)
  @test res[4] == 1
end