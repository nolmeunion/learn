Inductive bool := 
 | true
 | false. 

Check true.

Definition negb (b:bool) : bool :=
  match b with
  | true => false
  | false => true
  end.

Check negb.

