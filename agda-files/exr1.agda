{-# OPTIONS --no-unicode #-}

module exr1 where

data Bool : Set where
    ff : Bool
    tt : Bool

_ : Bool
_ = ff

not : Bool -> Bool
not ff = tt
not tt = ff

_&&_ : Bool -> Bool -> Bool
tt && tt = tt
ff && ff = ff
ff && tt = ff
tt && ff = ff

if_then_else_ : {A : Set} -> Bool -> A -> A -> A
if ff then t else e = e
if tt then t else e = t 

_ : Bool
_ = if tt
    then ff
    else tt

-- tupple of bools
record BoolTwoTuple : Set where
    field
        x' : Bool
        y' : Bool

open BoolTwoTuple public

_ : BoolTwoTuple
_ = record
  { x' = tt
  ; y' = tt
  }

&&-BoolTwoTuple : BoolTwoTuple -> Bool
&&-BoolTwoTuple record { x' = gosho; y' = pesho} = gosho && pesho


-- x : Zero
-- x = x
-- exits with error

--void type
data Zero : Set where

_ : Zero
_ = {!   !}

-- Zero suotvetstva na luja v logikata
zero-elim : {A : Set} -> Zero -> A
zero-elim ()

record One : Set where
    constructor <>

_ : One
_ = <>

-- One suotvetstva na trivialna istina
trivial : {A : Set} -> A -> One
trivial _ = <>

BoolEq : Bool -> Bool -> Set
BoolEq ff ff = One
BoolEq ff tt = Zero
BoolEq tt ff = Zero
BoolEq tt tt = One


-- x:  BoolEq tt tt
-- BoolEq tt tt = One
-- x : One
-- zatova izp. konstruktora na one
x : BoolEq tt tt
x = <>

-- _ : BoolEq tt ff
-- _ = {!   !} 

bla : Zero -> BoolEq tt ff
bla x = zero-elim x

-- dok che && e commut
&&-commut : (x : Bool) -> (y : Bool) -> BoolEq (x && y) (y && x)
&&-commut ff ff  = <>
&&-commut ff tt  = <>
&&-commut tt ff = <>
&&-commut tt tt = <>


