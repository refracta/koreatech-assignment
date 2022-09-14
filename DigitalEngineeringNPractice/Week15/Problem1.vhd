library ieee;
use ieee.std_logic_1164.all;
entity Project is
port( clk, x, reset : in std_logic;
	y : out std_logic_vector(2 downto 0);
	state_out : out std_logic_vector(1 downto 0));
end Project;
architecture sample of Project is
type states is (s0, s1, s2, s3);
signal state : states;
begin
p1: process(reset, clk)
begin
if reset='1' then
	state <= s0;
elsif clk'event and clk='1' then
	case state is
	when s0 =>
	if x='1' then
	state <= s1;
	end if;
	when s1 =>
	if x='0' then
	state <= s2;
	end if;
	when s2 =>
	if x='1' then
	state <= s3;
	end if;
	when s3 =>
	if x='0' then
	state <= s0;
	end if;
	end case;
end if;
end process;
p2: process(state)
begin
case state is
	when s0 =>
	y <= "000";
	when s1 =>
	y <= "001";
	when s2 =>
	y <= "011";
	when s3 =>
	y <= "111";
end case;
case state is
	when s0 =>
	state_out <= "00";
	when s1 =>
	state_out <= "01";
	when s2 =>
	state_out <= "10";
	when s3 =>
	state_out <= "11";
end case;
end process;
end sample;