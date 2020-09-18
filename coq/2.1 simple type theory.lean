/- declare some constants -/

constant m : nat        -- m is a natural number
constant n : nat
constants b1 b2 : bool  -- declare two constants at once

/- check their types -/

#check m            -- output: nat
#check n
#check n + 0        -- nat
#check m * (n + 0)  -- nat
#check b1           -- bool
#check b1 && b2     -- "&&" is boolean and
#check b1 || b2     -- boolean or
#check tt           -- boolean "true"

constant f : nat → nat 
constant f' : nat → nat 
constant p : nat × nat 
constant f'' : ℕ → ℕ 

#check f 
#check f''

constant F : (ℕ → ℕ ) → ℕ 

#check F 

#check (m, n).fst 


-- every expression has a type 
-- we can build more types on simple types 




