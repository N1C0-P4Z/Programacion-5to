{-# LANGUAGE FlexibleInstances #-}

-- 1
data Mes = Enero | Febrero | Marzo | Abril | Mayo | Junio | Julio | Agosto | Septiembre | Octubre | Noviembre | Diciembre deriving (Show)

vacaciones :: Mes -> Bool
vacaciones Enero = False
vacaciones Febrero = False
vacaciones Julio = False
vacaciones Diciembre = False
vacaciones otherwise = True

-- 2
data Forma = Circulo Float | Rectangulo Float Float | Triangulo Float Float Float deriving (Show)

perimetro :: Forma -> Float
perimetro (Circulo rad) = 3.14 * 2 * rad
perimetro (Rectangulo a1 a2) = 2 * (a1 + a2)
perimetro (Triangulo l1 l2 l3) = l1 + l2 + l3

-- 4

escalar :: Float -> Forma -> Forma
escalar n (Circulo rad) = Circulo (rad * n)
escalar n (Rectangulo a1 a2) = Rectangulo (n * a1) (n * a2)
escalar n (Triangulo l1 l2 l3) = Triangulo (n * l1) (n * l2) (n * l3)

-- 5
data Dinero = Pesos Float | Dolares Float | Cheque String Dinero deriving (Show)

conversion :: Dinero -> Dinero
conversion (Pesos a) = Dolares $ a / 1300
conversion (Dolares a) = Pesos $ a * 1300

-- 6
cheques :: Dinero -> Dinero
cheques (Cheque legajo platita) = Cheque legajo platita

-- 7

data Nat = Zero | Succ Nat deriving (Show)

nat2int :: Nat -> Int
nat2int Zero = 0
nat2int (Succ n) = 1 + nat2int n

-- 8
data List a = Nil | Cons a (List a) deriving (Show)

sumar :: List Int -> Int
sumar Nil = 0
sumar (Cons a as) = a + sumar as

-- 9

-- 11

data Expr = Literal Int | Suma Expr Expr | Resta Expr Expr deriving (Show)

-- para el 8
foldExpr :: (r -> r -> r) -> (r -> r -> r) -> (Int -> r) -> Expr -> r
foldExpr s r l (Literal n) = l n
foldExpr s r l (Suma e1 e2) = s (foldExpr s r l e1) (foldExpr s r l e2)
foldExpr s r l (Resta e1 e2) = r (foldExpr s r l e1) (foldExpr s r l e2)

existe :: Int -> Expr -> Bool
existe n (Literal m) = n == m
existe n (Suma e1 e2) = existe n e1 || existe n e2
existe n (Resta e1 e2) = existe n e1 || existe n e2

fib' :: Int -> Int
fib' 0 = 0
fib' 1 = 1
fib' x = fib' (x - 1) + fib' (x - 2)

-- practica Folds
-- r deberia ser List b
mapList :: (a -> b) -> List a -> List b
mapList f la = foldList (\a lb -> Cons (f a) lb) Nil la

-- si estan la en los 2 lados, se puede sacar
-- (usar Foldlist :: (a -> r -> r) -> r -> List a -> r)

foldList :: (a -> r -> r) -> r -> List a -> r
foldList f b Nil = b
foldList f b (Cons a l) = f a (foldList f b l)

-- 5
-- data List a = Nil | Cons a (List a)
natSize :: List a -> Nat
natSize = foldList (\_ n -> Succ n) Zero

-- 6
dup :: List a -> List a
dup = foldList (\x y -> Cons x (Cons x y)) Nil

-- 7
zipdup :: List a -> List (a, a)
zipdup = foldList (\x y -> Cons (x, x) y) Nil

-- 8
concatList :: List a -> List a -> List a
concatList i d = foldList Cons d i

flatenExpr :: Expr -> List Int
flatenExpr = foldExpr concatList concatList (\x -> Cons x Nil)

-- 9

maxNumber :: Expr -> Int
maxNumber e = foldExpr (\x y -> if x > y then x else y) (\x y -> if x > y then x else y) (\x -> x) e
