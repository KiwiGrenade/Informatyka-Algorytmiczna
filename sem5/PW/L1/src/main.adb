with Ada.Text_IO;
with Ada.Command_Line;

use Ada.Text_IO;
use Ada.Command_Line;


procedure Main is
   m : Integer := Integer'Value(Argument(1));
   n : Integer := Integer'Value(Argument(2));
   k : Integer := Integer'Value(Argument(3));
   horPass : constant String := "---";
   spacing : constant String := "    ";
   verPass : constant String := '|' & spacing;
   noVerPass : constant String := ' ' & spacing;
   emptySpace : constant String := "  ";
   --  procedure printBoard
   --    (m : Integer;
   --     n : Integer)
   --  is
   --  begin
   --     for y in 0 .. 2*(n-1) loop
   --        if (y rem 2 = 0) then
   --           for x in 0 .. (m-1) loop
   --              Put(emptySpace);
   --              if x < m-1 then
   --                 Put(horPass);
   --              else
   --                 New_Line;
   --              end if;
   --           end loop;
   --        else
   --           for x in 0 .. (m-1) loop
   --              Put(verPass);
   --              if x = m-1 then
   --                 New_Line;
   --              end if;
   --           end loop;
   --        end if;
   --     end loop;
   --  end printBoard;

begin
   -- Check input
   if(Argument_Count /= 3) then
      Put_Line("Wrong number of arguments!");
      return;
   end if;
   if(not (k < m * n)) then
      Put_Line("Wrong arugument! K is greater than m * n");
      return;
   end if;
   if((m > 10) or (n > 10)) then
      Put_Line("Wrong argument! m and n must be smaller or euqal to 10!");
      return;
   end if;


   --  printBoard(m, n);




   Put_Line("m = " & Integer'Image(k));
   Put_Line("n = " & Integer'Image(k));
   Put_Line("k = " & Integer'Image(k));
end Main;
