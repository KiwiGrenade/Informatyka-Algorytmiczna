with Ada.Text_IO; use Ada.Text_IO;
with Lib; use Lib;-- Include the lib package

procedure Test is

   procedure RunTests is
   begin
      -- Test IFactor function
      Put_Line("IFactor(5) = " & UInt64'Image(IFactor(5)));

      -- Test RFactor function
      Put_Line("RFactor(5) = " & UInt64'Image(RFactor(5)));

      -- Test IGCD function
      Put_Line("IGCD(24, 18) = " & UInt64'Image(IGCD(24, 18)));

      -- Test RGCD function
      Put_Line("RGCD(24, 18) = " & UInt64'Image(RGCD(24, 18)));

      -- Test RLDE function
      Put_Line("RLDE(56, 15, 3) = (" & Int64'Image(RLDE(56, 15, 3).X) & ", " & Int64'Image(RLDE(56, 15, 3).Y) & ")");
      Put_Line("RLDE(91, 35, 7) = (" & Int64'Image(RLDE(91, 35, 7).X) & ", " & Int64'Image(RLDE(91, 35, 7).Y) & ")");

      -- Test ILDE function
      Put_Line("ILDE(56, 15, 3) = (" & Int64'Image(ILDE(56, 15, 3).X) & ", " & Int64'Image(ILDE(56, 15, 3).Y) & ")");
      Put_Line("ILDE(91, 35, 7) = (" & Int64'Image(ILDE(91, 35, 7).X) & ", " & Int64'Image(ILDE(91, 35, 7).Y) & ")");
   end RunTests;

begin
   RunTests; -- Run the test procedure
end Test;
