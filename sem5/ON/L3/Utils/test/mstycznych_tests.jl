# Jakub Jaśków 268416
psilon = delta = 10^-3

@testset "TEST: convergence" begin
  f = x -> x^3 + 1
  df = x -> 3*x^2
  r = -1.
  res = mstycznych(f, df, 0.5, delta, epsilon, 10)
  x = res[1]
  fx = res[2]
  @test abs(fx) <= epsilon
  @test abs(r-x) <= delta
  @test res[4] == 0
end

@testset "TEST: inflection point" begin
  f = x -> x^3 + 1
  df = x -> 3*x^2
  res = mstycznych(f, df, 0.8, delta, epsilon, 10)
  @test res[4] == 2
end

@testset "TEST: periodicity" begin
  f = x -> x^3 - 2x - 2
  df = x -> 3x^2 - 2
  r = -1.7693
  res = mstycznych(f, df, 0., delta, epsilon, 100)
  x = res[1]
  fx = res[2]
  @test abs(fx) > epsilon
  @test abs(r-x) > delta
  @test res[4] == 1
end
