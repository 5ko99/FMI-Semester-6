{-# OPTIONS --no-unicode #-}

module exr2 where

data Zero : Set where

-- kudravite skobi ostavqt argumenta expliciten
-- zero == nauglt
-- e=elim
naughtE : {A : Set} -> Zero -> A
naughtE ()

record One : Set where
  constructor <>

data Two : Set where
  ff tt : Two

-- data Either a b = Left a | Right b
-- disjoint union
-- |A + B| = |A| + |B|
data _+_ (A B : Set) : Set where
  -- inject left
  inl : A -> A + B
  inr : B -> A + B

-- swap :: Either a b -> Either b a
-- A || B -> B || A
+-swap : {A B : Set} -> A + B -> B + A
+-swap (inl x) = inr x
+-swap (inr x) = inl x

-- cartesian product
-- |A * B| == |A| * |B|
record _*_ (A B : Set) : Set where
  constructor _,_
  field
    fst : A
    snd : B

_ : One * Two
_ = <> , tt

-- record - samo edin konstruktor. data mozhe poveche

infixr 9 _*_

*-swap : {A B : Set} -> A * B -> B * A
*-swap (fst , snd) = snd , fst

data Nat : Set where
  zero : Nat
  suc : Nat -> Nat

_ : Nat
_ = suc(suc(suc zero))

{-# BUILTIN NATURAL Nat #-}

_ : Nat
_ = 5

_+N_ : Nat -> Nat -> Nat
zero +N m = m
suc n +N m = suc (n +N m)


data DrinkType : Set where
  milk : DrinkType
  beer : DrinkType

data  Drink : DrinkType -> Set where
  vereq : Drink milk
  ariana : Drink beer
  duvel : Drink beer


Alcohol : DrinkType -> Set
Alcohol beer = Nat -- kolko alkohol ima kato chislo
Alcohol milk = One -- nqma alkohol

alcohol : {dt : DrinkType} -> Drink dt -> Alcohol dt
alcohol vereq = <>
alcohol ariana = 4
alcohol duvel = 6

-- NatEq : Nat -> Nat -> Set
-- NatEq zero zero = One
-- NatEq zero (suc y) = Zero
-- NatEq (suc x) zero = Zero
-- NatEq (suc x) (suc y) = NatEq n m

data _==_ {A : Set} : A -> A -> Set where
  refl : (x : A) -> x == x

--+N-left-zero : (n : Nat) -> zero +N n == n
