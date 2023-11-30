using Test
using Utils1
@testset "Utils1" begin
   testCaseList = ["ilorazyRoznicowe", "naturalna", "rysujNnfx", "warNewtona"]
   for testCase in testCaseList
      testCaseName = testCase * "_tests.jl"
      @testset "$testCase" begin
         include("$testCaseName")
      end
   end
end