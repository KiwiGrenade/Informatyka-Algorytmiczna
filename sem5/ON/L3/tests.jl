# Jakub Jaśków

include("utils.jl")
using .utils
using Test

epsilon = delta = 10^-3

@testset "$(rpad("metoda bisekcji", 17))" begin
  # test pozytywny
  f = x -> x^3 - x
  r = 1.
  res = mbisekcji(f, 0.1, 5., delta, epsilon)
  x = res[1]
  fx = res[2]
  @test abs(fx) <= epsilon
  @test abs(r-x) <= delta
  @test res[4] == 0
  
  # bardzo płaska funkcja
  f = x -> 1/x - 0.05
  r = 20.
  res = mbisekcji(f, 10., 25., delta, epsilon)
  x = res[1]
  fx = res[2]
  @test abs(fx) <= epsilon
  @test abs(r-x) > delta
  @test res[4] == 0

  # a teraz bardzo stroma
  f = x -> ℯ^x - ℯ^5
  r = 5.
  res = mbisekcji(f, 4.5, 6., delta, epsilon)
  x = res[1]
  fx = res[2]
  @test abs(fx) > epsilon
  @test abs(r-x) <= delta
  @test res[4] == 0

  # funkcja ma te same znaki na końcach przedziału
  f = x -> x^2
  r = 0.
  res = mbisekcji(f, -1., 2., delta, epsilon)
  @test res[4] == 1
end

@testset "$(rpad("metoda Newtona", 17))" begin
  # miło sobie zbiegnie
  f = x -> x^3 + 1
  df = x -> 3*x^2
  r = -1.
  res = mstycznych(f, df, 0.5, delta, epsilon, 10)
  x = res[1]
  fx = res[2]
  @test abs(fx) <= epsilon
  @test abs(r-x) <= delta
  @test res[4] == 0

  # a teraz wpadnie w punkt przegięcia
  res = mstycznych(f, df, 0.8, delta, epsilon, 10)
  @test res[4] == 2

  # a teraz zacykli się
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

@testset "$(rpad("metoda siecznych", 17))" begin
  f = x -> atan(x)
  r = 0.
  delta = epsilon = 10^-10
  # nie udało mi się znaleźć fajnego przypadku zapętlania się albo rozbiegania
  # ale tu zdąży
  res = msiecznych(f, -1.5, 1., delta, epsilon, 10)
  x = res[1]
  fx = res[2]
  @test abs(fx) <= epsilon
  @test abs(r-x) <= delta
  @test res[4] == 0

  # a tu nie
  res = msiecznych(f, 341000244450., 1120323240., delta, epsilon, 50)
  x = res[1]
  fx = res[2]
  @test abs(fx) > epsilon
  @test abs(r-x) > delta
  @test res[4] == 1
end