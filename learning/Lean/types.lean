#eval 1-2 --all numbers are naturals by default
#eval (1-2 : Int)
#check (1-2 : Int)

--defining natural numbers
def name := 3

--defining string
def greeting := "hello"
#check greeting --hel string is simple enough to lean to it can understand its type
--we need to eadd type to lean can undertsnad the type

def langName : String := "lean"
#eval String.append greeting (String.append " " langName)

--defining functions
def add1 (n : Nat) : Nat := n + 1987

#eval add1 7

--a maximum finder function
def maximum (n1 n2: Nat) : Nat :=
  if n1 < n2 then
    n2
  else n1

#eval maximum 5 6
#check (maximum)

--exercise 1. function that places its first argument between
--its second argument and third arguments
def joinStrings (str1 : String) (str2 : String) (str3 : String) : String :=
  String.append str2 (String.append " " (String.append str1 (String.append " " str3)))

#eval joinStrings "Hello" "World" "Lean"
#check (joinStrings)

--exercise 2. a function calculates volume of a rectangular prism
def volume (height width depth: Nat) : Nat :=
  height * width * depth

#eval volume 5 6 3
#check (volume)

--defining types
def Str : Type := String
def myName : Str := "ziya"
#check myName

--numbers have a difference
--classic Type definition does not work with nums
abbrev int : Type := Int
def numy : int := 5
#check numy

abbrev N : Type := Nat
def age : N := 98
#check age
