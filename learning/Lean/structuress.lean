structure Point where
  x : Float
  y : Float
deriving Repr

def origin : Point := {x := 0.0, y := 0.0}

#eval origin

#eval origin.x
#check (Point.x)

def addPoints (p1 p2 : Point) : Point :=
  {x := p1.x + p2.x, y := p1.y + p2.y}

#eval addPoints {x := 1.0, y := 2.0} {x := 5.0, y := -1.0}

def distance (p1 p2 : Point) : Float :=
  Float.sqrt (((p2.x - p1.x) ^ 2.0) + ((p2.y - p1.y) ^ 2.0))

#eval distance {x := 1.0, y := 2.0} {x := 5.0, y := -1.0}

--changing x field of a Point with a new value has different meaning from what it means in C
--it means allocating a new Point which has x with the new value and fields have same values with the original fields
--lets name the function described above as zeroX. it would be like below:
def zeroX (p : Point) : Point :=
  {x := 0, y := p.y}
--so lean has a short way to do that
def zeroXX (p : Point) : Point :=
  {p with x := 0}

def fourAndThree : Point :=
  {x := 4.3, y := 3.4}

#eval fourAndThree
#eval zeroXX fourAndThree
#eval fourAndThree
