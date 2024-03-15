-- main.adb
with Ada.Text_IO;
with Test_Lib;

procedure Main is
begin
   -- Run all tests from Test_Lib
   Test_Lib.RunAllTests;
end Main;
